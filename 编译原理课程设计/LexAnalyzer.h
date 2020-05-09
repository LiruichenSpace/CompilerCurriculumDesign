#pragma once
#include <fstream>
#include<string>
#include<unordered_map>
#include<unordered_set>
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
	LexAnalyzer();
	LexAnalyzer(std::string sourceFile);
	virtual ~LexAnalyzer();
	Token getNextToken();
	bool streamValiable();
	//��ʼ��������
	void initStream(std::string sourceFile);
private:
	//ȥ����һ����ǰ��Ч�ַ�
	void trimStreamHead();
	void initMatrix();
	void deleteMatrix();
	//ɾ��������
	void deleteStream();
	int getDfaNextStatus(int currStatus);
	bool isEndStatus(int currStatus);
	bool isValidChar();
private:
	int matrix[11][128];//״̬ת�ƾ���
	bool endStatusFlag[11];
	char currChar;
	std::unordered_map<std::string, int> cricicalMap;
	std::unordered_set<char> validChars;
	std::ifstream istream;
};
/*
Token��������type���ձ�
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
*/

