#include "pch.h"
#include<string>
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

}

void LexAnalyzer::initMatrix() {

}

void LexAnalyzer::deleteMatrix() {

}

void LexAnalyzer::initStream(std::string sourceFile)
{
}

void LexAnalyzer::deleteStream()
{
}

int LexAnalyzer::getDfaNextStatus(int currStatus)
{

	return 0;
}

bool LexAnalyzer::isEndStatus(int currStatus)
{
	return false;
}
