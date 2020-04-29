#pragma once
#include<string>
/*
公用工具方法类，尽量使用共有静态部分，只增加静态方法
*/
class Utils
{
public:
	Utils();
	~Utils();
	static bool checkFileReadable(std::string sourceFile);
	static void log(std::string message, std::string Tag="test");
};

