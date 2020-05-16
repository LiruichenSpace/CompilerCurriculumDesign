#pragma once
#include<string>
class Token
{
public:
	Token() {
		type = -1;
		sourceLine = -1;
		strValue = "";
	}
	virtual ~Token() {}
	int type;
	int sourceLine;
	std::string  strValue;
};

