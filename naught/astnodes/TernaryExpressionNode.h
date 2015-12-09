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

	auto conditionExp = condition->evaluate(out, symbolTable, numTabs, temp);
	auto ifTrueExp    = ifTrue->evaluate (out, symbolTable, numTabs, temp);
	auto ifFalseExp   = ifFalse->evaluate (out, symbolTable, numTabs, temp);
	
	// create an if statement
	out << ifTrueExp.second << " temp" << temp << ";" << endl;
	TABS(out, numTabs);
	out << "if (" << conditionExp.first << ") {" << endl;
	TABS(out, numTabs + 1);
	out << " temp" << temp << " = " << ifTrueExp.first << ";" << endl;
	TABS(out, numTabs);
	out << "} else { " << endl;
	TABS(out, numTabs+1);
	out << " temp" << temp << " = " << ifFalseExp.first << ";" << endl;
	TABS(out, numTabs);
	out << "}" << endl;
	TABS(out, numTabs);
	retVal.first = "temp" + to_string(temp);
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