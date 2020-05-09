#include "pch.h"
#include<fstream>
#include<iostream>
#include "SyntexAnalyzer.h"

SyntexAnalyzer::SyntexAnalyzer(std::string sourcePath, std::string matrixPath, std::string tablePath):lexanalyzer(sourcePath)
{
	initMatrix(matrixPath);
	initTable(tablePath);
	characterStack.push_back(38);
}

SyntexAnalyzer::~SyntexAnalyzer()
{
}

bool SyntexAnalyzer::analyze()
{
	int curr,temp,pos;
	Token token = lexanalyzer.getNextToken();
	while (!characterStack.empty()&&token.type!=-1) {

		std::cout << "stacktop:";
		for (auto it : characterStack) {
			std::cout << " " << it;
		}
		std::cout<<"   tokentype:" << token.type<<"   tokenvalue:"<<token.strValue<<"     action:";
		curr = characterStack.back(); characterStack.pop_back();
		if (curr < 38) {
			if (token.type != curr)return false;
			token = lexanalyzer.getNextToken();
			std::cout << "匹配" << std::endl;
		}
		else {
			temp = curr - 38;
			pos = matrix[temp][token.type];
			if (pos == -1) {
				std::cout << "错误" << std::endl;
				return false;
			}
			else {
				for (int i = table[pos].size() - 1; i >= 0; i--) {
					characterStack.push_back(table[pos][i]);
				}
			}
			std::cout << "展开" << std::endl;
		}
	}
	if (characterStack.empty() && token.type == -1)return true;
	else return false;
}

void SyntexAnalyzer::initMatrix(std::string matrixPath)
{
	std::ifstream istream;
	istream.open(matrixPath);
	if (!istream.is_open()) {
		std::cout << "转移矩阵文件读取错误！" << std::endl;
		exit(-1);
	}
	for (int i = 0; i < 67; i++) {
		for (int j = 0; j < 38; j++) {
			istream >> matrix[i][j];
		}
	}	
	istream.close();
}

void SyntexAnalyzer::initTable(std::string tablePath)
{
	std::ifstream istream;
	istream.open(tablePath);
	if (!istream.is_open()) {
		std::cout << "产生式文件读取错误！" << std::endl;
		exit(-1);
	}
	int count,temp;
	std::vector<int> v;
	istream >> count;
	while (count != -1) {
		v = std::vector<int>();
		while (count) {
			istream >> temp;
			v.push_back(temp);
			count--;
		}
		table.push_back(v);
		istream >> count;
	}
	istream.close();
}
