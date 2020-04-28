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
	int** matrix;//二维指针
	char currChar;
	std::ifstream istream;
};

