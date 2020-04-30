#pragma once
#include <fstream>
#include<string>
#include<unordered_map>
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
	std::unordered_map<std::string, int> cricicalMap;
	std::ifstream istream;
};
/*
Token��������type���ձ�
	cricicalMap["INTEGER"] = 1;
	cricicalMap["RETURN"] = 2;
	cricicalMap["BEGIN"] = 3;
	cricicalMap["VAR"] = 4;
	cricicalMap["OF"] = 5;
	cricicalMap["WRITE"] = 6;
	cricicalMap["ELSE"] = 7;
	cricicalMap["ENDWH"] = 8;
	cricicalMap["ID"] = 9;
	cricicalMap["ARRAY"] = 10;
	cricicalMap["CHAR"] = 11;
	cricicalMap["INTC"] = 12;
	cricicalMap["DO"] = 13;
	cricicalMap["PROCEDURE"] = 14;
	cricicalMap["RECORD"] = 15;
	cricicalMap["END"] = 16;
	cricicalMap["TYPE"] = 17;
	cricicalMap["READ"] = 18;
	cricicalMap["PROGRAM"] = 19;
	cricicalMap["IF"] = 20;
	cricicalMap["FI"] = 21;
	cricicalMap["WHILE"] = 22;
	cricicalMap["THEN"] = 23;
	cricicalMap["="] = 24;
	cricicalMap[";"] = 25;
	cricicalMap["<"] = 26;
	cricicalMap["]"] = 27;
	cricicalMap["*"] = 28;
	cricicalMap[".."] = 29;
	cricicalMap["."] = 30;
	cricicalMap["-"] = 31;
	cricicalMap["("] = 32;
	cricicalMap[","] = 33;
	cricicalMap[")"] = 34;
	cricicalMap["+"] = 35;
	cricicalMap[":="] = 36;
	cricicalMap["/"] = 37;
	cricicalMap["["] = 38;
*/

