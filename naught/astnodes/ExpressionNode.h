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

class ExpressionNode {
protected:

public:
	/* returns a pair, where the first item is the name of the temp variable if created, 
	 * and the second is the type of the expression. will also print to file if needed. */
	virtual pair<string, string> evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);

	virtual ~ExpressionNode();
};

inline pair<string, string> ExpressionNode::evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) { 
	pair<string, string> p;
	return p;
}

inline ExpressionNode::~ExpressionNode() { }

#endif //EXPRESSION_NODE_H