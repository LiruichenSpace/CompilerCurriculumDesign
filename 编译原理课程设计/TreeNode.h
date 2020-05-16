#pragma once
#include"Token.h"
class TreeNode
{
public:
	TreeNode() {
		typeID = -1;
		is_leaf = false;
		children = std::vector<TreeNode*>();
	}
	TreeNode(int type) {
		typeID = type;
		is_leaf = false;
		children = std::vector<TreeNode*>();
	}
	TreeNode(Token t) {
		typeID = t.type;
		is_leaf = true;
		strVal = t.strValue;
		children = std::vector<TreeNode*>();
	}
	std::string strVal;
	int typeID;
	std::vector<TreeNode*> children;
	bool is_leaf;
};

