#pragma once
#include <fstream>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include "Token.h"
/**
 * @brief 词法分析器类
 * @see Token.h
 * 维护DFA状态转移表，通过源文件路径初始化，调用getNextToken()方法获得下一个Token对象
 * 源代码文件打开时间与对象生命周期相同
 */
class LexAnalyzer
{
public:
	LexAnalyzer();
	LexAnalyzer(std::string sourceFile);
	virtual ~LexAnalyzer();
	Token getNextToken();
	bool streamValiable();
	//初始化流对象
	void initStream(std::string sourceFile);
private:
	//去除下一单词前无效字符
	void trimStreamHead();
	void initMatrix();
	void deleteMatrix();
	//删除流对象
	void deleteStream();
	int getDfaNextStatus(int currStatus);
	bool isEndStatus(int currStatus);
	bool isValidChar();
private:
	int matrix[11][128];//状态转移矩阵
	bool endStatusFlag[11];
	char currChar;
	std::unordered_map<std::string, int> cricicalMap;
	std::unordered_set<char> validChars;
	std::ifstream istream;
};
/*
Token类型与其type对照表：
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

