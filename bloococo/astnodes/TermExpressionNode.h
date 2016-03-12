#ifndef TERM_EXPRESSION_NODE_H
#define TERM_EXPRESSION_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
#include "VariableDeclarationNode.h"
#include "StatementNode.h"
#include "TermNode.h"
#include "ExpressionNode.h"
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

class TermExpressionNode : public TermNode {
protected:
	ExpressionNode* expr;

public:

	TermExpressionNode(ExpressionNode* ex);

	virtual pair<string, string> evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);

	virtual ~TermExpressionNode();
};

inline TermExpressionNode::TermExpressionNode(ExpressionNode* ex) {
	this->expr = ex;
}

inline pair<string, string> TermExpressionNode::evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) { 
	
	auto retVal = expr->evaluate(out, symbolTable, numTabs, temp);

	return retVal;
}

inline TermExpressionNode::~TermExpressionNode() {
	delete expr;
}

#endif //TERM_EXPRESSION_NODE_H