#include "pch.h"
#include<string>
#include<stack>
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

/**
 * @brief 返回下一个Token，如果出错或者读到文件尾，返回的token类型为-1
 * 注意，可能会无法区分文件读到头或者出现错误
 */
Token LexAnalyzer::getNextToken() {
	//去除前导无效字符
	trimStreamHead();
	if (currChar==EOF)return Token();//如果已经读到了文件尾，则可以直接返回终结token
	//处理输入文件可能为空或者滤去前导后为空
	//DFA逻辑
	Token token;
	int currStatus = 0,nextStatus;
	std::string str;
	bool flag=true;
	while (flag) {
		nextStatus = getDfaNextStatus(currStatus);//需要已经读入一个字符
		if (nextStatus == -1) {//如果接下来没有转移去的状态，则结束。不继续向下读，保护currChar
			flag = false;
		}
		else {//若被接受则去读下一个字符
			str.push_back(currChar);//当前字符可被接受，继续进行
			currStatus = nextStatus;
			currChar = istream.get();//读取下一个字符
			if (currChar == EOF) {//文件结束,取消下一轮循环,此时应相当于Token加入了“#”，可以考虑直接返回特殊标志
				flag = false;
			}//由于EOF不会带来转移，到达EOF后重复调用也会获得无效Token
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
	stack<char> noteStack;//临时存储注释符号

	if (istream.is_open()) {
		char c = istream.get();
		while ((c == " ") || (c == "\n") || (c == "\t")) {
			c = istream.get();
		}
		//设置为上一个
		istream.seekg(-1, ios::cur);
	}
	else {
		//TODO
		cout << "文件流打开失败！" << endl;
		exit(0);
	}
}

/**
 * @brief 初始化状态转移矩阵
 * 实现DFA的一部分
 */
void LexAnalyzer::initMatrix() {
	int i, j;
	for (i = 0; i < 11; i++) {
		for (j = 0; j < 128; j++) {
			matrix[i][j] = -1;
		}
	}
	for (int i = 0; i < 10; i++) {//设定终结状态标志
		if (i == 0 || i == 4 || i == 9)endStatusFlag[i] = false;
		else endStatusFlag[i] = true;
	}
	//S一行  状态0+
	for (j = 0; j < 128; j++) {
		//大小写字母 [65,90]  [97,122]
		if ((j >= 65 && j <= 90) || (j >= 97 && j <= 122)) {
			matrix[0][j] = 6;
		}
		//0-9   [48,57]
		else if ((j >= 48 && j <= 57)) {
			if (j == 48) {
				matrix[0][j] = 8;
			}
			else {
				matrix[0][j] = 7;
			}
		}
		//单字符
		else if (j > 31) {
			if (j == 46) {// .
				matrix[0][j] = 2;
			}
			else if (j == 58) {// =
				matrix[0][j] = 4;
			}
			else if (j == 39) {//'
				matrix[0][j] = 9;
			}
			//除过. : =  '
			else {
				matrix[0][j] = 1;
			}
		}
	}
	//状态1* 全部-1

	//状态2*  只修改"."
	matrix[2][46] = 3;
	//状态3*  全部-1

	//状态4  只修改“=”
	matrix[4][58] = 5;
	//状态5* 全部-1

	 //状态6* 只改letter和num
	for (j = 0; j < 128; j++) {
		if ((j >= 65 && j <= 90) || (j >= 97 && j <= 122) || (j >= 48 && j <= 57)) {
			matrix[6][j] = 6;
		}
	}
	//状态7* 只改D
	for (j = 0; j < 128; j++) {
		if ((j >= 48 && j <= 57)) {
			matrix[7][j] = 7;
		}
	}
	//状态9 
	for (j = 0; j < 128; j++) {
		if ((j >= 65 && j <= 90) || (j >= 97 && j <= 122) || (j >= 48 && j <= 57)) {
			matrix[9][j] = 9;
		}
		else if (j == 39) {
			matrix[9][j] = 10;
		}
	}
}

/**
 * @brief 暂且保留，用于释放矩阵可能占据的堆区内存
 */
void LexAnalyzer::deleteMatrix() {

}

/**
 * @brief 对输入流进行初始化，读入文件
 * @param sourceFile 源程序文件的路径，不对文件是否可以读取进行判断
 * 判断文件可读性需要交给外层调用来检查
 */
void LexAnalyzer::initStream(std::string sourceFile)
{
	istream = istream.open(sourceFile);
	if (!istream.is_open()) {
		std::cout << "文件流初始化错误！" << endl;
		exit(1);
	}*/
}

/**
 * @brief 关闭文件，对流进行关闭处理
 * 有可能用来扩展功能
 */
void LexAnalyzer::deleteStream()
{
	if ((istream != NULL) && (istream.is_open()) {
		istream.close();
	}
}

/**
 * @brief 根据当前字符和状态获取状态机的下一个状态
 * @return 如果有可用状态则返回状态，否则返回-1，即不接受当前字符
 * 当前实现仅为查表操作，如果当前状态已经为-1则仍会返回-1
 */
int LexAnalyzer::getDfaNextStatus(int currStatus)
{
	if (currStatus != -1) {
		return matrix[currStatus][currChar];
	}
	else return -1;
}

/**
 * @brief 判断该状态是否是终止状态
 * 通过查找标志数组实现，如果为终结状态则可以组装Token
 */
bool LexAnalyzer::isEndStatus(int currStatus)
{
	return endStatusFlag[currStatus];
}
