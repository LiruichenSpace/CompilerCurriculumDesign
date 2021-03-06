#include "pch.h"
#include<fstream>
#include<iostream>
#include <iomanip>
#include<stack>
#include"Utils.h"
#include "SyntexAnalyzer.h"

#define  VT  38 //常数 数值为非终极符数目
SyntexAnalyzer::SyntexAnalyzer(LexAnalyzer* L)
{
	lexA = L;
	initAllTab();
	root = nullptr;
}

SyntexAnalyzer::~SyntexAnalyzer()
{
}

/*
*由filename指定的文件初始化vector
*/
void SyntexAnalyzer::initVector(std::vector<std::vector<int>>& v1, std::string filename) {
	std::ifstream v_istream;
	v_istream.open(filename);
	if (!v_istream.is_open()) {
		Utils::error("初始化vector文件流打开失败");
	}
	int curInt = -1;
	char curC = '0';
	std::vector<int> v;
	//v = *(new std::vector<int>());
	while ((!v_istream.eof()) && (curC != EOF))
	{
		if (curC == '\n') {
			v1.push_back(v);
			v.clear();
			//v = *(new std::vector<int>());
			//cout << "新一行" << endl;
		}
		v_istream >> curInt;
		v.push_back(curInt);//压入
		//cout << curInt << endl;
		curC = v_istream.get();
		v_istream.seekg(-1, std::ios::cur);
	}
	v1.push_back(v);
}
void SyntexAnalyzer::deleteTree(TreeNode * root)
{
	if (root == nullptr)return;
	else {
		for (TreeNode* child: root->children) {
			deleteTree(child);
		}
		delete root;
		root = nullptr;
	}
}
void  SyntexAnalyzer::initAllTab() {
	std::string exp_filename = "./exp_out.txt";
	std::string matrix_filename = "./Matrix.txt";
	//初始化exp_out
	initVector(tablePro, exp_filename);
	//初始化分析表
	initVector(tableLL, matrix_filename);
}



void SyntexAnalyzer::showTab(std::vector< std::vector<int> >& A) {
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			std::cout << A[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void SyntexAnalyzer::printAST()
{
	if (root) {
		std::cout << std::endl << "抽象语法树先序遍历：" << std::endl;
		printAST(root);
	}
	else {
		std::cout << std::endl << "分析失败，无法生成抽象语法树" << std::endl;
	}
	
}

void SyntexAnalyzer::deleteTree()
{
	deleteTree(root);
	root = nullptr;
}

void SyntexAnalyzer::printAST(TreeNode* root)
{
	if (root) {
		std::cout << root->typeID;
		if (root->is_leaf) {
			std::cout << ":" << root->strVal;
		}
		std::cout << std::endl;
		for (int i = 0; i < root->children.size();i++) {
			printAST(root->children[i]);
		}
	}
}

TreeNode * SyntexAnalyzer::getAST()
{
	return root;
}

void SyntexAnalyzer::analyExpression() {
	//测试用
	/*******************
	**由于驱动程序本质上变动不大 故自行设置测试   有些地方拿捏不来如何处理 等后面讨论 我先写完好弄实验报告
	**以ppt的例子作为测试用例  手动生成分析表和产生式   测试结果正常
	**问题：#需要再考虑如何处理   需要将整个源程序生成token序列来分析   错误处理需完善
	********************/
	/*
		实现思想  经过词法分析后转成一个token序列 每次调用getNextToken()获得一个token
		使用token中的type数值作为单词
		以ppt举例：输入流为i + i * i    调用getNextToken获得token.type为5 6 5 7 5
		作为测试 此处使用int数组代替token       #使用数字10代替 修改待商议
	*/
	//int数组声明 仅测试用 后可删除 
	int test[6] = { 18, 8,16, 8, 23 };
	//int数组声明 仅测试用 后可删除 end

	//临时变量声明
	int  tabLLX, tabLLY, proExp;
	int i;
	std::vector<int>::iterator it;
	//临时变量声明 end

	//初始化分析栈以及输入栈
	root = new TreeNode(38);
	analyStack.push_back(root);//0号非终极符入栈
	//循环读取输入流   应该使用getNextToken()获取输入流  同上做修改 手动输入56575
	Token t = lexA->getNextToken();
	while (t.type != -1) {
		tokenQueue.push(t);
		std::cout << "字符值：" << t.strValue 
			<< "  类型ID：" << t.type 
			<< "  源代码行号：" << t.sourceLine << std::endl;
		exprStack.push_back(t.type);
		t = lexA->getNextToken();
	}
	//初始化分析栈以及输入栈 end


	std::cout << "当前分析栈" << std::setw(15) << "||  当前输入栈" << std::endl;
	for (i = 0; i < analyStack.size(); i++) {
		std::cout << analyStack[i]->typeID<< std::setw(3);
	}
	std::cout << "|||";
	for (i = 0; i < exprStack.size(); i++) {
		std::cout << exprStack[i] << std::setw(3);
	}
	std::cout << std::endl;

	int temp = 0;
	//开始分成四种情况分析  
	//当分析栈空的时候停止
	while (1) {
		if (analyStack.size() == 0) {
			if (exprStack.size() == 0) {//情况1：若栈已空，输入流也空，则语法分析成功
				std::cout << "语法分析成功" << std::endl;
			}
			else {//情况2：若栈已空，输入流不空，则输入流报错
				std::cout << "输入流出现错误" << std::endl;
				deleteTree();
			}
			return;
		}
		std::cout << "第" << temp + 1 << "次执行" << std::endl;
		//情况3：
		//分析栈栈顶元素是非终极符 即为小于某常数VT VT为非终极符个数 此处为5
		//用栈顶和输入流的当前单词去查当前矩阵，如果查得的值是产生式编号，则把对应的产生式右部逆序压入栈中；如果查得的值为错误 信息，则报错
		if (analyStack.back()->typeID >= VT) {//当前栈顶是非终极符 查表
			if (tableLL[analyStack.back()->typeID - VT][exprStack.front()] != -1) {//查表得到产生式编号  注意终极符编号减去VT
				tabLLX = analyStack.back()->typeID - VT;
				tabLLY = exprStack.front();
				proExp = tableLL[tabLLX][tabLLY];
				std::cout << "X" << tabLLX << "Y" << tabLLY << std::endl;
				std::cout << "产生式序号" << proExp << std::endl;
				//打印产生式
				std::cout << "产生式内容 ";
				for (i = 0; i < tablePro[proExp].size(); i++) {
					std::cout << tablePro[proExp][i] << "  ";
				}
				std::cout << std::endl;
				//将产生式右部逆序压入分析栈
				TreeNode* temp = analyStack.back();
				analyStack.pop_back();//弹栈
				for (i = 0; i < tablePro[proExp].size(); i++) {
					temp->children.push_back(new TreeNode(tablePro[proExp][i]));
					if (temp->children.back()->typeID == -1) {
						temp->children.back()->is_leaf = true;
						temp->children.back()->strVal = "空";
					}
				}
				if (tablePro[proExp][0] == -1) {
					std::cout << "产生式推出空 打印分析栈弹栈" << std::endl;
				}
				else {
					std::cout << "产生式非空   正常处理" << std::endl;	
					for (i = temp->children.size() - 1; i >= 0; i--) {
						analyStack.push_back(temp->children[i]);//逆序压入
					}
				}
			}
			else {//错误信息处理
				std::cout << "error  查表错误" << std::endl;
				deleteTree();
				exit(-1);
			}
		}
		//情况4：
		else if (analyStack.back()->typeID < VT) {//当前栈顶是当前栈顶是终极符 看其是否与输入流的头符相匹配，如果匹配 成功，去掉栈顶元素,并读下一个单词；若匹配不成功，则报错
			if (analyStack.back()->typeID == exprStack.front()) {  //两者都是非终极符 看是否匹配
				//成功 各自弹栈一个
				analyStack.back()->strVal = tokenQueue.front().strValue;
				analyStack.back()->is_leaf = true;
				tokenQueue.pop();
				analyStack.pop_back();
				it = exprStack.begin();
				exprStack.erase(it);
			}
			else {
				std::cout << "error  单词匹配失败" << std::endl;
				deleteTree();
				exit(-1);
			}
		}
		for (i = 0; i < analyStack.size(); i++) {
			std::cout << analyStack[i]->typeID<< std::setw(3);
		}
		std::cout << "|||";
		for (i = 0; i < exprStack.size(); i++) {
			std::cout << exprStack[i]  << std::setw(3);
		}
		std::cout << std::endl;
		std::cout << std::endl;
		temp++;
	}

}