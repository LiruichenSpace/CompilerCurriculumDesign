#pragma once
#include <fstream>
#include<string>
#include<unordered_map>
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
	LexAnalyzer(std::string sourceFile);
	virtual ~LexAnalyzer();
	Token getNextToken();
private:
	//去除下一单词前无效字符
	void trimStreamHead();
	void initMatrix();
	void deleteMatrix();
	//初始化流对象
	void initStream(std::string sourceFile);
	//删除流对象
	void deleteStream();
	int getDfaNextStatus(int currStatus);
	bool isEndStatus(int currStatus);
private:
	int matrix[11][128];//状态转移矩阵
	bool endStatusFlag[11];
	char currChar;
	std::unordered_map<std::string, int> cricicalMap;
	std::ifstream istream;
};
/*
Token类型与其type对照表：
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

