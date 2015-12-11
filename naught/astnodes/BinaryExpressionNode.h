#ifndef BINARY_EXPRESSION_NODE_H
#define BINARY_EXPRESSION_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
#include "VariableDeclarationNode.h"
#include "StatementNode.h"
#include "ParameterNode.h"

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

class BinaryExpressionNode : public ExpressionNode {
protected:
	ExpressionNode* left;
	ExpressionNode* right;
	string op;

public:

	BinaryExpressionNode(string* op, ExpressionNode* left, ExpressionNode* right);

	virtual pair<string, string> evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);

	virtual ~BinaryExpressionNode();
};

inline BinaryExpressionNode::BinaryExpressionNode(string* op, ExpressionNode* left, ExpressionNode* right) {
	this->op = *op;
	this->left = left;
	this->right = right;

	delete op;
}

inline pair<string, string> BinaryExpressionNode::evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) { 
	pair<string,string> retVal;

	auto leftExp  = left->evaluate (out, symbolTable, numTabs, temp);
	auto rightExp = right->evaluate(out, symbolTable, numTabs, temp);

	retVal.first = "temp" + to_string(temp++);
	retVal.second = leftExp.second;

	if(!leftExp.second.compare("string") && !right.second.compare("string")) {
		out << naughtToC[retVal.second] << " " << retVal.first << " = nstr_add(" << leftExp.first << ", " << rightExp.first << ");" << endl;
	} else {
		out << naughtToC[retVal.second] << " " << retVal.first << " = " << leftExp.first << op << rightExp.first << ";" << endl;
	}
	
	TABS(out,numTabs);
	return retVal;
}

inline BinaryExpressionNode::~BinaryExpressionNode() {
	delete left;
	delete right;
}

#endif //BINARY_EXPRESSION_NODE_H