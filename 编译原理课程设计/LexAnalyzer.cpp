#include "pch.h"
#include "LexAnalyzer.h"


LexAnalyzer::LexAnalyzer(std::string sourceFile)
{
	initMatrix();
}


LexAnalyzer::~LexAnalyzer()
{
	deleteMatrix();
}

Token LexAnalyzer::getNextToken() {
	trimStreamHead();
	//DFAÂß¼­
	Token token;

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
