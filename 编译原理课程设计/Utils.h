#pragma once
#include<string>
/*
���ù��߷����࣬����ʹ�ù��о�̬���֣�ֻ���Ӿ�̬����
*/
class Utils
{
public:
	Utils();
	~Utils();
	static bool checkFileReadable(std::string sourceFile);
	static void log(std::string message, std::string Tag="test");
};

