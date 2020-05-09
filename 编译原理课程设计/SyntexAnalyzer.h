#pragma once
#include<vector>
#include<stack>
#include"Token.h"
#include"LexAnalyzer.h"
/**
 * @brief ”Ô∑®∑÷Œˆ∆˜¿‡
 * @see Token.h
 */
class SyntexAnalyzer
{
public:
	SyntexAnalyzer(std::string sourcePath, std::string matrixPath, std::string tablePath);
	virtual ~SyntexAnalyzer();
	bool analyze();
private:
	void initMatrix(std::string matrixPath);
	void initTable(std::string tablePath);
private:
	int matrix[67][38];
	std::vector<std::vector<int>> table;
	LexAnalyzer lexanalyzer;
	std::vector<int> characterStack;
};

