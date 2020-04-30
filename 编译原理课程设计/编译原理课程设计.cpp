// 编译原理课程设计.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<string>
#include"LexAnalyzer.h"
#include"SyntexAnalyzer.h"
#include"Utils.h"

#define DEBUG

int main(int argc,char* argv[])
{
	if (argc < 2)//判断参数调用方式
	{
		std::cout<<"程序调用参数错误，调用方式:<programename> <sourcefilename>"<<std::endl;
		return -1;
	}
#ifdef DEBUG
	Utils::log("调用正确");
#endif // DEBUG
	std::string sourcePath = argv[1];
	if (Utils::checkFileReadable(sourcePath)) {//判断文件存在可读
		std::cout << "源程序不存在或不可读，编译失败" << std::endl;
		return -1;
	}
#ifdef DEBUG
	Utils::log("文件存在可读，创建词法分析器");
#endif // DEBUG
	LexAnalyzer lexer(sourcePath);
	Token token;
	do {
		token = lexer.getNextToken();
		if (token.type != -1)
			std::cout << "type: " << token.type << " value: " << token.strValue << std::endl;
		else
			std::cout << "文件读取完毕，词法分析结束" << std::endl;
	} while (token.type != -1);
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
