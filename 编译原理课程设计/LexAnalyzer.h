#pragma once
#include <fstream>
#include<string>
#include "Token.h"
/**
 * @brief �ʷ���������
 * @see Token.h
 * ά��DFA״̬ת�Ʊ�ͨ��Դ�ļ�·����ʼ��������getNextToken()���������һ��Token����
 * Դ�����ļ���ʱ�����������������ͬ
 */
class LexAnalyzer
{
public:
	LexAnalyzer(std::string sourceFile);
	virtual ~LexAnalyzer();
	Token getNextToken();
private:
	//ȥ����һ����ǰ��Ч�ַ�
	void trimStreamHead();
	void initMatrix();
	void deleteMatrix();
	//��ʼ��������
	void initStream(std::string sourceFile);
	//ɾ��������
	void deleteStream();
	int getDfaNextStatus(int currStatus);
	bool isEndStatus(int currStatus);
private:
	int matrix[11][128];//״̬ת�ƾ���
	bool endStatusFlag[11];
	char currChar;
	std::ifstream istream;
};

