#pragma once
#include<string>
class Token
{
public:
	Token() {
		type = -1;
		strValue = "";
	}
	virtual ~Token() {}
	int type;
	std::string  strValue;
};

