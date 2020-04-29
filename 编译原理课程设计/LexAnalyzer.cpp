#include "pch.h"
#include<string>
#include<stack>
#include "LexAnalyzer.h"


LexAnalyzer::LexAnalyzer(std::string sourceFile)
{
	initMatrix();
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
		token.strValue = str;
		if (currStatus != 4) {//�ж�������Ǳ�ʶ����ֱ����д����
			token.type = currStatus;
		}
		else {
			//Ϊ��ʶ�����ж��Ƿ�Ϊ������
		}
	}//����Ϊ��ʼtoken��typeΪ-1�����ʹ���
	//��������£�tokenӦ��ֻ�����ļ������ʱ��Ż᷵��-1���Դ�Ϊ�ս�
	return token;
}

void LexAnalyzer::trimStreamHead() {
	stack<char> noteStack;//��ʱ�洢ע�ͷ���

	if (istream.is_open()) {
		char c = istream.get();
		while ((c == " ") || (c == "\n") || (c == "\t")) {
			c = istream.get();
		}
		//����Ϊ��һ��
		istream.seekg(-1, ios::cur);
	}
	else {
		//TODO
		cout << "�ļ�����ʧ�ܣ�" << endl;
		exit(0);
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
			else if (j == 58) {// =
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
	matrix[4][58] = 5;
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
	istream = istream.open(sourceFile);
	if (!istream.is_open()) {
		std::cout << "�ļ�����ʼ������" << endl;
		exit(1);
	}*/
}

/**
 * @brief �ر��ļ����������йرմ���
 * �п���������չ����
 */
void LexAnalyzer::deleteStream()
{
	if ((istream != NULL) && (istream.is_open()) {
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
