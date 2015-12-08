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

class TermLiteralNode : public ExpressionNode {
protected:
	string literal;
	string type;

public:

	TermLiteralNode(string* literal, string* type);

	virtual pair<string, string> evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);

	virtual ~TermLiteralNode();
};

inline TermLiteralNode::TermLiteralNode(string* literal, string* type) {
	this->literal = *literal;
	this->type = *type;
	delete literal;
	delete type;
}

inline pair<string, string> TermLiteralNode::evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) { 
	pair<string,string> retVal;
	retVal.first() = literal;
	retVal.second() = type;

	return retVal;
}

inline TermLiteralNode::~ExpressionNode() {
	
}

#endif //EXPRESSION_NODE_H