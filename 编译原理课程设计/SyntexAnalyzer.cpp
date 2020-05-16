#include "pch.h"
#include<fstream>
#include<iostream>
#include <iomanip>
#include<stack>
#include"Utils.h"
#include "SyntexAnalyzer.h"

#define  VT  38 //���� ��ֵΪ���ռ�����Ŀ
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
*��filenameָ�����ļ���ʼ��vector
*/
void SyntexAnalyzer::initVector(std::vector<std::vector<int>>& v1, std::string filename) {
	std::ifstream v_istream;
	v_istream.open(filename);
	if (!v_istream.is_open()) {
		Utils::error("��ʼ��vector�ļ�����ʧ��");
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
			//cout << "��һ��" << endl;
		}
		v_istream >> curInt;
		v.push_back(curInt);//ѹ��
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
	//��ʼ��exp_out
	initVector(tablePro, exp_filename);
	//��ʼ��������
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
		std::cout << std::endl << "�����﷨�����������" << std::endl;
		printAST(root);
	}
	else {
		std::cout << std::endl << "����ʧ�ܣ��޷����ɳ����﷨��" << std::endl;
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
	//������
	/*******************
	**���������������ϱ䶯���� ���������ò���   ��Щ�ط���������δ��� �Ⱥ������� ����д���Ūʵ�鱨��
	**��ppt��������Ϊ��������  �ֶ����ɷ�����Ͳ���ʽ   ���Խ������
	**���⣺#��Ҫ�ٿ�����δ���   ��Ҫ������Դ��������token����������   ������������
	********************/
	/*
		ʵ��˼��  �����ʷ�������ת��һ��token���� ÿ�ε���getNextToken()���һ��token
		ʹ��token�е�type��ֵ��Ϊ����
		��ppt������������Ϊi + i * i    ����getNextToken���token.typeΪ5 6 5 7 5
		��Ϊ���� �˴�ʹ��int�������token       #ʹ������10���� �޸Ĵ�����
	*/
	//int�������� �������� ���ɾ�� 
	int test[6] = { 18, 8,16, 8, 23 };
	//int�������� �������� ���ɾ�� end

	//��ʱ��������
	int  tabLLX, tabLLY, proExp;
	int i;
	std::vector<int>::iterator it;
	//��ʱ�������� end

	//��ʼ������ջ�Լ�����ջ
	root = new TreeNode(38);
	analyStack.push_back(root);//0�ŷ��ռ�����ջ
	//ѭ����ȡ������   Ӧ��ʹ��getNextToken()��ȡ������  ͬ�����޸� �ֶ�����56575
	Token t = lexA->getNextToken();
	while (t.type != -1) {
		tokenQueue.push(t);
		std::cout << "�ַ�ֵ��" << t.strValue 
			<< "  ����ID��" << t.type 
			<< "  Դ�����кţ�" << t.sourceLine << std::endl;
		exprStack.push_back(t.type);
		t = lexA->getNextToken();
	}
	//��ʼ������ջ�Լ�����ջ end


	std::cout << "��ǰ����ջ" << std::setw(15) << "||  ��ǰ����ջ" << std::endl;
	for (i = 0; i < analyStack.size(); i++) {
		std::cout << analyStack[i]->typeID<< std::setw(3);
	}
	std::cout << "|||";
	for (i = 0; i < exprStack.size(); i++) {
		std::cout << exprStack[i] << std::setw(3);
	}
	std::cout << std::endl;

	int temp = 0;
	//��ʼ�ֳ������������  
	//������ջ�յ�ʱ��ֹͣ
	while (1) {
		if (analyStack.size() == 0) {
			if (exprStack.size() == 0) {//���1����ջ�ѿգ�������Ҳ�գ����﷨�����ɹ�
				std::cout << "�﷨�����ɹ�" << std::endl;
			}
			else {//���2����ջ�ѿգ����������գ�������������
				std::cout << "���������ִ���" << std::endl;
				deleteTree();
			}
			return;
		}
		std::cout << "��" << temp + 1 << "��ִ��" << std::endl;
		//���3��
		//����ջջ��Ԫ���Ƿ��ռ��� ��ΪС��ĳ����VT VTΪ���ռ������� �˴�Ϊ5
		//��ջ�����������ĵ�ǰ����ȥ�鵱ǰ���������õ�ֵ�ǲ���ʽ��ţ���Ѷ�Ӧ�Ĳ���ʽ�Ҳ�����ѹ��ջ�У������õ�ֵΪ���� ��Ϣ���򱨴�
		if (analyStack.back()->typeID >= VT) {//��ǰջ���Ƿ��ռ��� ���
			if (tableLL[analyStack.back()->typeID - VT][exprStack.front()] != -1) {//���õ�����ʽ���  ע���ռ�����ż�ȥVT
				tabLLX = analyStack.back()->typeID - VT;
				tabLLY = exprStack.front();
				proExp = tableLL[tabLLX][tabLLY];
				std::cout << "X" << tabLLX << "Y" << tabLLY << std::endl;
				std::cout << "����ʽ���" << proExp << std::endl;
				//��ӡ����ʽ
				std::cout << "����ʽ���� ";
				for (i = 0; i < tablePro[proExp].size(); i++) {
					std::cout << tablePro[proExp][i] << "  ";
				}
				std::cout << std::endl;
				//������ʽ�Ҳ�����ѹ�����ջ
				TreeNode* temp = analyStack.back();
				analyStack.pop_back();//��ջ
				for (i = 0; i < tablePro[proExp].size(); i++) {
					temp->children.push_back(new TreeNode(tablePro[proExp][i]));
					if (temp->children.back()->typeID == -1) {
						temp->children.back()->is_leaf = true;
						temp->children.back()->strVal = "��";
					}
				}
				if (tablePro[proExp][0] == -1) {
					std::cout << "����ʽ�Ƴ��� ��ӡ����ջ��ջ" << std::endl;
				}
				else {
					std::cout << "����ʽ�ǿ�   ��������" << std::endl;	
					for (i = temp->children.size() - 1; i >= 0; i--) {
						analyStack.push_back(temp->children[i]);//����ѹ��
					}
				}
			}
			else {//������Ϣ����
				std::cout << "error  ������" << std::endl;
				deleteTree();
				exit(-1);
			}
		}
		//���4��
		else if (analyStack.back()->typeID < VT) {//��ǰջ���ǵ�ǰջ�����ռ��� �����Ƿ�����������ͷ����ƥ�䣬���ƥ�� �ɹ���ȥ��ջ��Ԫ��,������һ�����ʣ���ƥ�䲻�ɹ����򱨴�
			if (analyStack.back()->typeID == exprStack.front()) {  //���߶��Ƿ��ռ��� ���Ƿ�ƥ��
				//�ɹ� ���Ե�ջһ��
				analyStack.back()->strVal = tokenQueue.front().strValue;
				analyStack.back()->is_leaf = true;
				tokenQueue.pop();
				analyStack.pop_back();
				it = exprStack.begin();
				exprStack.erase(it);
			}
			else {
				std::cout << "error  ����ƥ��ʧ��" << std::endl;
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