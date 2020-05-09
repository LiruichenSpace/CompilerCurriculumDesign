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
	SyntexAnalyzer();
	virtual ~SyntexAnalyzer();
	void analyExpression();//LL(1)
	void initAllTab();
	void showTab(std::vector<std::vector<int>>& A);
public:
	std::vector<std::vector<int>> tableLL;
	std::vector<std::vector<int>> tablePro;
	std::vector<int> analyStack;   
	std::vector<int> exprStack;
};

