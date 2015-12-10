#ifndef TERNARY_EXPRESSION_NODE_H
#define TERNARY_EXPRESSION_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
#include "VariableDeclarationNode.h"
#include "StatementNode.h"
#include "ParameterNode.h"
#include "ExpressionNode.h"

#include <map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

class TernaryExpressionNode : public ExpressionNode {
protected:
	ExpressionNode* condition;
	ExpressionNode* ifTrue;
	ExpressionNode* ifFalse;

public:

	TernaryExpressionNode(ExpressionNode* condition, ExpressionNode* ifTrue, ExpressionNode* ifFalse);

	virtual pair<string, string> evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);

	virtual ~TernaryExpressionNode();
};

inline TernaryExpressionNode::TernaryExpressionNode(ExpressionNode* condition, ExpressionNode* ifTrue, ExpressionNode* ifFalse) {
	this->condition = condition;
	this->ifTrue	= ifTrue;
	this->ifFalse	= ifFalse;
}

inline pair<string, string> TernaryExpressionNode::evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) { 
	pair<string,string> retVal;

	// evaluates the condition.
	auto conditionExp = condition->evaluate(out, symbolTable, numTabs, temp);

	// evaluates the true and false nodes, not allowing the modification of any variables.
	std::ofstream ofs;
	std::map<string, string> st = symbolTable;
	int nt = numTabs, t = temp;
	auto ifTrueExp    = ifTrue->evaluate (ofs, st, nt, t);
	auto ifFalseExp   = ifFalse->evaluate (ofs, st, nt, t);

	// asserts types are equal, and gets the type for the temp variable. //TODO


	string tempVarName = "temp" + to_string(temp);
	out << naughtToC[ifTrueExp.second] << " " << tempVarName << ";" << endl;
	temp++;
	TABS(out, numTabs);
	// creates an if statent;
	out << "if (" << conditionExp.first << ") {" << endl;
	TABS(out, numTabs + 1);
	ifTrueExp = ifTrue->evaluate (out, symbolTable, numTabs + 1, temp);
	out << " " << tempVarName << " = " << ifTrueExp.first << ";" << endl;
	TABS(out, numTabs);
	out << "} else { " << endl;
	TABS(out, numTabs +1);
	out << " " << tempVarName << " = " << ifFalseExp.first << ";" << endl;
	TABS(out, numTabs);
	out << "}" << endl;
	TABS(out, numTabs);
	retVal.first = tempVarName;
	retVal.second = ifTrueExp.second;
	temp++;
	return retVal;
}

inline TernaryExpressionNode::~TernaryExpressionNode() {
	delete condition;
	delete ifTrue;
	delete ifFalse;
}

#endif //TERNARY_EXPRESSION_NODE_H