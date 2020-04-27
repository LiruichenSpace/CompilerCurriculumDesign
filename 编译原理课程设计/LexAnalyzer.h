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
	void trimStreamHead();
	void initMatrix();
	void deleteMatrix();
	void initStream(std::string sourceFile);
	void deleteStream();
private:
	int** matrix;//¶þÎ¬Ö¸Õë
	char currChar;
	std::ifstream istream;
};

