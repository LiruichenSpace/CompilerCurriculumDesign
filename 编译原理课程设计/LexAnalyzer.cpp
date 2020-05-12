#include "pch.h"
#include<iostream>
#include<string>
#include"Utils.h"
#include "LexAnalyzer.h"


LexAnalyzer::LexAnalyzer()
{
	initMatrix();
	cricicalMap["INTEGER"] = 0;
	cricicalMap["RETURN"] = 1;
	cricicalMap["BEGIN"] = 2;
	cricicalMap["VAR"] = 3;
	cricicalMap["OF"] = 4;
	cricicalMap["WRITE"] = 5;
	cricicalMap["ELSE"] = 6;
	cricicalMap["ENDWH"] = 7;
	cricicalMap["ID"] = 8;
	cricicalMap["ARRAY"] = 9;
	cricicalMap["CHAR"] = 10;
	cricicalMap["INTC"] = 11;
	cricicalMap["DO"] = 12;
	cricicalMap["PROCEDURE"] = 13;
	cricicalMap["RECORD"] = 14;
	cricicalMap["END"] = 15;
	cricicalMap["TYPE"] = 16;
	cricicalMap["READ"] = 17;
	cricicalMap["PROGRAM"] = 18;
	cricicalMap["IF"] = 19;
	cricicalMap["FI"] = 20;
	cricicalMap["WHILE"] = 21;
	cricicalMap["THEN"] = 22;
	cricicalMap["="] = 23;
	cricicalMap[";"] = 24;
	cricicalMap["<"] = 25;
	cricicalMap["]"] = 26;
	cricicalMap["*"] = 27;
	cricicalMap[".."] = 28;
	cricicalMap["."] = 29;
	cricicalMap["-"] = 30;
	cricicalMap["("] = 31;
	cricicalMap[","] = 32;
	cricicalMap[")"] = 33;
	cricicalMap["+"] = 34;
	cricicalMap[":="] = 35;
	cricicalMap["/"] = 36;
	cricicalMap["["] = 37;
}

LexAnalyzer::LexAnalyzer(std::string sourceFile):LexAnalyzer()//����ԭ��C++�����ڹ��캯���е��ù��캯��
															//��Ҫ�ڳ�ʼ���б��е���
{
	initStream(sourceFile);
}


LexAnalyzer::~LexAnalyzer()
{
	deleteMatrix();
	deleteStream();
}

/**
 * @brief ������һ��Token�����������߶����ļ�β�����ص�token����Ϊ-1
 * ע�⣬���ܻ��޷������ļ�����ͷ���߳��ִ���
 */
Token LexAnalyzer::getNextToken() {
	//ȥ��ǰ����Ч�ַ�
	trimStreamHead();
	if (currChar==EOF)return Token();//����Ѿ��������ļ�β�������ֱ�ӷ����ս�token
	//���������ļ�����Ϊ�ջ�����ȥǰ����Ϊ��
	//DFA�߼�
	Token token;
	int currStatus = 0,nextStatus;
	std::string str;
	bool flag=true;
	while (flag) {
		if (!isValidChar())Utils::error("��⵽�Ƿ��ַ����ʷ�����ʧ��");
		nextStatus = getDfaNextStatus(currStatus);//��Ҫ�Ѿ�����һ���ַ�
		if (nextStatus == -1) {//���������û��ת��ȥ��״̬������������������¶�������currChar
			flag = false;
		}
		else {//����������ȥ����һ���ַ�
			str.push_back(currChar);//��ǰ�ַ��ɱ����ܣ���������
			currStatus = nextStatus;
			currChar = istream.get();//��ȡ��һ���ַ�
			if (currChar == EOF) {//�ļ�����,ȡ����һ��ѭ��,��ʱӦ�൱��Token�����ˡ�#�������Կ���ֱ�ӷ��������־
				flag = false;
			}//����EOF�������ת�ƣ�����EOF���ظ�����Ҳ������ЧToken
		}
	}
	if (isEndStatus(currStatus)) {//�����ǰ״̬Ϊ��ֹ״̬��������tokenֵ����������
		if (currStatus == 6) {
			if (cricicalMap.find(str) != cricicalMap.end()){
				token.type = cricicalMap[str];
			}
			else {
				token.type = 8;
			}
		}
		else if (currStatus == 7 || currStatus == 8) {
			token.type = 11;
		}
		else {
			token.type = cricicalMap[str];
		}
		token.strValue = str;
	}//����Ϊ��ʼtoken��typeΪ-1�����ʹ���
	//��������£�tokenӦ��ֻ�����ļ������ʱ��Ż᷵��-1���Դ�Ϊ�ս�
	return token;
}
bool LexAnalyzer::streamValiable()
{
	if (istream.is_open())return true;
	else return false;
}
void LexAnalyzer::trimStreamHead(){
	if (istream.is_open()){
		while ((currChar == ' ') || (currChar == '\n') || (currChar == '\t') || (currChar == '{') || (currChar == '}')) {
			if (currChar == '{') {
				while ((currChar != '}') && (currChar != EOF)) {
					currChar = istream.get();
				}
				if (currChar == EOF) {
					Utils::error("ע�Ͳ�ƥ��!");
				}
			}
			else if (currChar == '}'){
				Utils::error("ע�Ͳ�ƥ�䣡");
			}
			currChar = istream.get();
		}
	}
	else {
		Utils::error("�ļ�����ʧ�ܣ�");
	}
}

/**
 * @brief ��ʼ��״̬ת�ƾ���
 * ʵ��DFA��һ����
 */
void LexAnalyzer::initMatrix() {
	int i, j;
	for (i = 0; i < 11; i++) {
		for (j = 0; j < 128; j++) {
			matrix[i][j] = -1;
		}
	}
	for (int i = 0; i < 10; i++) {//�趨�ս�״̬��־
		if (i == 0 || i == 4 || i == 9)endStatusFlag[i] = false;
		else endStatusFlag[i] = true;
	}
	//Sһ��  ״̬0+
	for (j = 0; j < 128; j++) {
		//��Сд��ĸ [65,90]  [97,122]
		if ((j >= 65 && j <= 90) || (j >= 97 && j <= 122)) {
			matrix[0][j] = 6;
		}
		//0-9   [48,57]
		else if ((j >= 48 && j <= 57)) {
			if (j == 48) {
				matrix[0][j] = 8;
			}
			else {
				matrix[0][j] = 7;
			}
		}
		//���ַ�
		else if (j > 31) {
			if (j == 46) {// .
				matrix[0][j] = 2;
			}
			else if (j == 58) {//:
				matrix[0][j] = 4;
			}
			else if (j == 39) {//'
				matrix[0][j] = 9;
			}
			//����. : =  '
			else {
				matrix[0][j] = 1;
			}
		}
	}
	//״̬1* ȫ��-1

	//״̬2*  ֻ�޸�"."
	matrix[2][46] = 3;
	//״̬3*  ȫ��-1

	//״̬4  ֻ�޸ġ�=��
	matrix[4][61] = 5;
	//״̬5* ȫ��-1

	 //״̬6* ֻ��letter��num
	for (j = 0; j < 128; j++) {
		if ((j >= 65 && j <= 90) || (j >= 97 && j <= 122) || (j >= 48 && j <= 57)) {
			matrix[6][j] = 6;
		}
	}
	//״̬7* ֻ��D
	for (j = 0; j < 128; j++) {
		if ((j >= 48 && j <= 57)) {
			matrix[7][j] = 7;
		}
	}
	//״̬9 
	for (j = 0; j < 128; j++) {
		if ((j >= 65 && j <= 90) || (j >= 97 && j <= 122) || (j >= 48 && j <= 57)) {
			matrix[9][j] = 9;
		}
		else if (j == 39) {
			matrix[9][j] = 10;
		}
	}
}

/**
 * @brief ���ұ����������ͷž������ռ�ݵĶ����ڴ�
 */
void LexAnalyzer::deleteMatrix() {

}

/**
 * @brief �����������г�ʼ���������ļ�
 * @param sourceFile Դ�����ļ���·���������ļ��Ƿ���Զ�ȡ�����ж�
 * �ж��ļ��ɶ�����Ҫ���������������
 */
void LexAnalyzer::initStream(std::string sourceFile)
{
	istream.open(sourceFile);
	if (!istream.is_open()) {
		std::cout << "�ļ�����ʼ������" << std::endl;
		exit(1);
	}
	currChar = istream.get();
}

/**
 * @brief �ر��ļ����������йرմ���
 * �п���������չ����
 */
void LexAnalyzer::deleteStream()
{
	if (istream.is_open()) {
		istream.close();
	}
}

/**
 * @brief ���ݵ�ǰ�ַ���״̬��ȡ״̬������һ��״̬
 * @return ����п���״̬�򷵻�״̬�����򷵻�-1���������ܵ�ǰ�ַ�
 * ��ǰʵ�ֽ�Ϊ�������������ǰ״̬�Ѿ�Ϊ-1���Ի᷵��-1
 */
int LexAnalyzer::getDfaNextStatus(int currStatus)
{
	if (currStatus != -1) {
		return matrix[currStatus][currChar];
	}
	else return -1;
}

/**
 * @brief �жϸ�״̬�Ƿ�����ֹ״̬
 * ͨ�����ұ�־����ʵ�֣����Ϊ�ս�״̬�������װToken
 */
bool LexAnalyzer::isEndStatus(int currStatus)
{
	return endStatusFlag[currStatus];
}

bool LexAnalyzer::isValidChar()
{
	if ((currChar >= 'a'&&currChar <= 'z') || (currChar >= 'A'&&currChar <= 'Z')
		|| (currChar >= '0'&&currChar <= '9')
		|| currChar == '<'
		|| currChar == '='
		|| currChar == '+'
		|| currChar == '-'
		|| currChar == '*'
		|| currChar == '/'
		|| currChar == ':'
		|| currChar == '.'
		|| currChar == ';'
		|| currChar == '['
		|| currChar == ']'
		|| currChar == '{'
		|| currChar == '}'
		|| currChar == '('
		|| currChar == ')'
		|| currChar == EOF
		|| currChar == ' '
		|| currChar == '\n'
		|| currChar == '\t')return true;
	else return false;
}

