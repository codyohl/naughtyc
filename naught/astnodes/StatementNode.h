#ifndef STATEMENT_NODE_H
#define STATEMENT_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
#include "ParameterNode.h"
#include "ExpressionNode.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>

using namespace std;

class StatementNode : public Node {
protected:
ExpressionNode* expression;
bool isReturnStatement;

public:
	StatementNode(bool isReturnStatement, ExpressionNode* expr);

	~StatementNode();

	virtual void printNode(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);
};

inline StatementNode::StatementNode(bool isReturnStatement, ExpressionNode* expr) {
	this->expression = expr;
	this->isReturnStatement = isReturnStatement;
}

inline void StatementNode::printNode(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) {
	
	pair<string,string> p = expression->evaluate(out,symbolTable,numTabs,temp);

	if (isReturnStatement)
		out << "return " << p.first << ";" << endl;
	TABS(out, numTabs);
}

inline StatementNode::~StatementNode() {
	delete expression;
}

#endif //STATEMENT_NODE_H