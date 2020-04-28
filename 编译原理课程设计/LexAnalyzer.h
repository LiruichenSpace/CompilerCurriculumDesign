#pragma once
#include <fstream>
#include<string>
#include "Token.h"
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
	int** matrix;//��άָ��
	char currChar;
	std::ifstream istream;
};

