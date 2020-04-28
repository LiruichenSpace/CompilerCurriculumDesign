#pragma once
#include <fstream>
#include<string>
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
	std::ifstream istream;
};

