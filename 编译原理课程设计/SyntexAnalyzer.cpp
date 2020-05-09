#include "pch.h"
#include<fstream>
#include<iostream>
#include <iomanip>
#include<stack>
#include "SyntexAnalyzer.h"

#define  VT  5 //���� ��ֵΪ���ռ�����Ŀ
SyntexAnalyzer::SyntexAnalyzer()
{
}

SyntexAnalyzer::~SyntexAnalyzer()
{
}

void  SyntexAnalyzer::initAllTab() {//�ֶ�����  ��Ϊ������ tableLL��tablePro�����滻�ɴ��ļ���ȡ����vector  �˺�������
	std::vector<int> B;
	//----�������
	B.push_back(0);
	B.push_back(-1);
	B.push_back(-1);
	B.push_back(0);
	B.push_back(-1);
	B.push_back(-1);
	tableLL.push_back(B);
	B.clear();

	B.push_back(-1);
	B.push_back(1);
	B.push_back(-1);
	B.push_back(-1);
	B.push_back(2);
	B.push_back(2);
	tableLL.push_back(B);
	B.clear();

	B.push_back(3);
	B.push_back(-1);
	B.push_back(-1);
	B.push_back(3);
	B.push_back(-1);
	B.push_back(-1);
	tableLL.push_back(B);
	B.clear();

	B.push_back(-1);
	B.push_back(5);
	B.push_back(4);
	B.push_back(-1);
	B.push_back(5);
	B.push_back(5);
	tableLL.push_back(B);
	B.clear();

	B.push_back(6);
	B.push_back(-1);
	B.push_back(-1);
	B.push_back(7);
	B.push_back(-1);
	B.push_back(-1);
	tableLL.push_back(B);
	B.clear();
	//--------�����ʽ
	B.push_back(2);
	B.push_back(1);
	tablePro.push_back(B);
	B.clear();

	B.push_back(6);
	B.push_back(2);
	B.push_back(1);
	tablePro.push_back(B);
	B.clear();

	B.push_back(10);
	tablePro.push_back(B);
	B.clear();

	B.push_back(4);
	B.push_back(3);
	tablePro.push_back(B);
	B.clear();

	B.push_back(7);
	B.push_back(4);
	B.push_back(3);
	tablePro.push_back(B);
	B.clear();

	B.push_back(10);
	tablePro.push_back(B);
	B.clear();

	B.push_back(5);
	tablePro.push_back(B);
	B.clear();

	B.push_back(8);
	B.push_back(0);
	B.push_back(9);
	tablePro.push_back(B);
	B.clear();
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