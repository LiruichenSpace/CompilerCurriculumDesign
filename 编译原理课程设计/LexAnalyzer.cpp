#include "pch.h"
#include<string>
#include "LexAnalyzer.h"


LexAnalyzer::LexAnalyzer(std::string sourceFile)
{
	initMatrix();
	initStream(sourceFile);
}


LexAnalyzer::~LexAnalyzer()
{
	deleteMatrix();
	deleteStream();
}

Token LexAnalyzer::getNextToken() {
	//去除前导无效字符
	trimStreamHead();
	//DFA逻辑
	Token token;
	int currStatus = 0,nextStatus;
	std::string str;
	bool flag=true;
	while (flag) {
		nextStatus = getDfaNextStatus(currStatus);//需要已经读入一个字符
		if (nextStatus == -1) {//如果接下来没有转移去的状态，则结束
			flag = false;
		}
		else {
			str.push_back(currChar);//当前字符可被接受，继续进行
			currStatus = nextStatus;
		}
		if(!istream.eof())istream >> currChar;//读取下一个字符
		else {//文件结束,取消下一轮循环,此时应相当于Token加入了“#”，可以考虑直接返回特殊标志
			flag = false;
		}
	}
	if (isEndStatus(currStatus)) {//如果当前状态为终止状态，则填入token值并正常返回
		token.strValue = str;
		if (currStatus != 4) {//判断如果不是标识符则直接填写类型
			token.type = currStatus;
		}
		else {
			//为标识符，判断是否为保留字
		}
	}//否则为初始token，type为-1，类型错误
	//理想情况下，token应该只会在文件读完的时候才会返回-1，以此为终结
	return token;
}

void LexAnalyzer::trimStreamHead() {

}

void LexAnalyzer::initMatrix() {

}

void LexAnalyzer::deleteMatrix() {

}

void LexAnalyzer::initStream(std::string sourceFile)
{
}

void LexAnalyzer::deleteStream()
{
}

int LexAnalyzer::getDfaNextStatus(int currStatus)
{

	return 0;
}

bool LexAnalyzer::isEndStatus(int currStatus)
{
	return false;
}
