#include "pch.h"
#include<fstream>
#include<iostream>
#include <iomanip>
#include<stack>
#include"Utils.h"
#include "SyntexAnalyzer.h"

#define  VT  5 //���� ��ֵΪ���ռ�����Ŀ
SyntexAnalyzer::SyntexAnalyzer()
{
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
	v = *(new std::vector<int>());
	while ((!v_istream.eof()) && (curC != EOF))
	{
		if (curC == '\n') {
			v1.push_back(v);
			v = *(new std::vector<int>());
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
	int test[6] = { 5, 6,5, 7, 5,10 };
	//int�������� �������� ���ɾ�� end

	//��ʱ��������
	int  tabLLX, tabLLY, proExp;
	int i;
	std::vector<int>::iterator it;
	//��ʱ�������� end

	//��ʼ������ջ�Լ�����ջ
	analyStack.push_back(10); //#��ջ
	analyStack.push_back(0);//0�Ų���ʽ��ջ
	//ѭ����ȡ������   Ӧ��ʹ��getNextToken()��ȡ������  ͬ�����޸� �ֶ�����56575
	for (i = 0; i < 6; i++) {
		exprStack.push_back(test[i]);
	}
	//��ʼ������ջ�Լ�����ջ end


	std::cout << "��ǰ����ջ" << std::setw(15) << "||  ��ǰ����ջ" << std::endl;
	for (i = 0; i < analyStack.size(); i++) {
		std::cout << analyStack[i] << std::setw(3);
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
		if (analyStack.size() == 1) {
			if (exprStack.size() == 1) {//���1����ջ�ѿգ�������Ҳ�գ����﷨�����ɹ�
				std::cout << "�﷨�����ɹ�" << std::endl;
			}
			else {//���2����ջ�ѿգ����������գ�������������
				std::cout << "���������ִ���" << std::endl;
			}
			return;
		}
		std::cout << "��" << temp + 1 << "��ִ��" << std::endl;
		//���3��
		//����ջջ��Ԫ���Ƿ��ռ��� ��ΪС��ĳ����VT VTΪ���ռ������� �˴�Ϊ5
		//��ջ�����������ĵ�ǰ����ȥ�鵱ǰ���������õ�ֵ�ǲ���ʽ��ţ���Ѷ�Ӧ�Ĳ���ʽ�Ҳ�����ѹ��ջ�У������õ�ֵΪ���� ��Ϣ���򱨴�
		if (analyStack.back() < VT) {//��ǰջ���Ƿ��ռ��� ���
			if (tableLL[analyStack.back()][exprStack.front() - VT] != -1) {//���õ�����ʽ���  ע���ռ�����ż�ȥVT
				tabLLX = analyStack.back();
				tabLLY = exprStack.front() - VT;
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
				if (tablePro[proExp][0] == 10) {
					std::cout << "����ʽ��һ��ֵΪ10����Ϊ#����ӡ����ջ��ջ" << std::endl;

					analyStack.pop_back();
				}
				else {
					std::cout << "����ʽ��һ��ֵ����10��#��  ��������" << std::endl;
					analyStack.pop_back();//��ջ
					for (i = tablePro[proExp].size() - 1; i >= 0; i--) {
						analyStack.push_back(tablePro[proExp][i]);//����ѹ��
					}
				}
			}
			else {//������Ϣ����
				std::cout << "error  ������" << std::endl;
			}
		}
		//���4��
		else if (analyStack.back() >= VT) {//��ǰջ���ǵ�ǰջ�����ռ��� �����Ƿ�����������ͷ����ƥ�䣬���ƥ�� �ɹ���ȥ��ջ��Ԫ��,������һ�����ʣ���ƥ�䲻�ɹ����򱨴�
			if (analyStack.back() == exprStack.front()) {  //���߶��Ƿ��ռ��� ���Ƿ�ƥ��
				//�ɹ� ���Ե�ջһ��
				analyStack.pop_back();
				it = exprStack.begin();
				exprStack.erase(it);

			}
			else {
				std::cout << "error  ����ƥ��ʧ��" << std::endl;
			}
		}


		for (i = 0; i < analyStack.size(); i++) {
			std::cout << analyStack[i] << std::setw(3);
		}
		std::cout << "|||";
		for (i = 0; i < exprStack.size(); i++) {
			std::cout << exprStack[i] << std::setw(3);
		}
		std::cout << std::endl;
		std::cout << std::endl;

		temp++;
	}

}