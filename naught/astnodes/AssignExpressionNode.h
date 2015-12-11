#ifndef ASSIGN_EXPRESSION_NODE_H
#define ASSIGN_EXPRESSION_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
#include "VariableDeclarationNode.h"
#include "StatementNode.h"
#include "ParameterNode.h"
#include "ExpressionNode.h"
#include "TermNode.h"

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

class AssignExpressionNode : public ExpressionNode {
protected:
	TermNode* t;
	ExpressionNode* e;

public:

	AssignExpressionNode(TermNode* t, ExpressionNode* e);

	virtual pair<string, string> evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);

	virtual ~AssignExpressionNode();
};

inline AssignExpressionNode::AssignExpressionNode(TermNode* t, ExpressionNode* e) {
	this->t = t;
	this->e = e;
}

inline pair<string, string> AssignExpressionNode::evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) { 

	auto termP = t->evaluate(out, symbolTable, numTabs, temp);
	auto exprP = e->evaluate(out, symbolTable, numTabs, temp);

	if ((!termP.second.compare("string") || !exprP.second.compare("string")) && termP.second.compare(exprP.second))
		err("Invalid string type assignment: " + termP.second + " to " + exprP.second);
	else if (termP.second.compare(exprP.second))
		wrn("Coersion of types: " + termP.second + " to " + exprP.second + " for variable " + termP.first);

	out << termP.first << " = " << exprP.first << ";" << endl;
	TABS(out, numTabs);

	return termP;
}

inline AssignExpressionNode::~AssignExpressionNode() {
	delete t;
	delete e;
}

#endif //ASSIGN_EXPRESSION_NODE_H