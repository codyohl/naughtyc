#ifndef EXPRESSION_NODE_H
#define EXPRESSION_NODE_H

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

	auto rightExp = right->evaluate(out, symbolTable, numTabs, temp);
	auto leftExp  = left->evaluate (out, symbolTable, numTabs, temp);

	stringstream ss;
	ss << "temp" << temp;
	retVal.first() = ss.str();
	retVal.second() = leftExp.second();
	// check that the types are compatible here
	TAB(out,numTabs);
	out << retVal.second() << " temp" << temp << " = " << leftExp.first() << op << rightExp.first() << ";" << endl;
	temp++;
	return retVal;
}

inline BinaryExpressionNode::~ExpressionNode() {
	delete left;
	delete right;
}

#endif //EXPRESSION_NODE_H