#pragma once
#include<vector>
#include<queue>
#include"Token.h"
#include"TreeNode.h"
#include"LexAnalyzer.h"
/**
 * @brief ”Ô∑®∑÷Œˆ∆˜¿‡
 * @see Token.h
 */
class SyntexAnalyzer
{
public:
	SyntexAnalyzer(LexAnalyzer* L);
	virtual ~SyntexAnalyzer();
	void analyExpression();//LL(1)
	void initAllTab();
	void showTab(std::vector<std::vector<int>>& A);
	void printAST();
	TreeNode* getAST();
private:
	void deleteTree();
	void printAST(TreeNode* root);
	void initVector(std::vector<std::vector<int>>& v, std::string filename);
	void deleteTree(TreeNode* root);
	TreeNode* root;
public:
	std::vector<std::vector<int>> tableLL;
	std::vector<std::vector<int>> tablePro;
	std::vector<TreeNode *> analyStack;   
	std::vector<int> exprStack;
	std::queue<Token> tokenQueue;
	LexAnalyzer *lexA;
};

/*
INTEGER
RETURN
BEGIN
VAR
OF
WRITE
ELSE
ENDWH
ID
ARRAY
CHAR
INTC
DO
PROCEDURE
RECORD
END
TYPE
READ
PROGRAM
IF
FI
WHILE
THEN
=
;
<
]
*
..
.
-
(
,
)
+
:=
/
[
Program
ProgramHead
ProgramName
DeclarePart
TypeDec
TypeDeclaration
TypeDecList
TypeDecMore
TypeId
TypeName
BaseType
StructureType
ArrayType
Low
Top
RecType
FieldDecList
FieldDecMore
IdList
IdMore
VarDec
VarDeclaration
VarDecList
VarDecMore
VarIdList
VarIdMore
ProcDec
ProcDeclaration
ProcDecMore
ProcName
ParamList
ParamDecList
ParamMore
Param
FormList
FidMore
ProcDecPart
ProcBody
ProgramBody
StmList
StmMore
Stm
AssCall
AssignmentRest
ConditionalStm
LoopStm
InputStm
Invar
OutputStm
ReturnStm
CallStmRest
ActParamList
ActParamMore
RelExp
OtherRelE
Exp
OtherTerm
Term
OtherFactor
Factor
Variable
VariMore
FieldVar
FieldVarMore
CmpOp
AddOp
MultOp
*/
