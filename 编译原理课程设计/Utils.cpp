#include "pch.h"
#include <io.h>
#include <iostream>
#include "Utils.h"

#define F_Exist 0
#define F_Readable 2

Utils::Utils()
{
}


Utils::~Utils()
{
}

/*
 * �ж�Դ�����ļ��Ƿ�����ҿɶ� 
 */
bool Utils::checkFileReadable(std::string sourceFile)
{
	return _access(sourceFile.c_str(),F_Exist)&&_access(sourceFile.c_str(), F_Readable);
}

void Utils::log(std::string message, std::string Tag)
{
	std::cout << "log: " << Tag << ":" << message << std::endl;
}
