#ifndef TERM_NODE_H
#define TERM_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
#include "VariableDeclarationNode.h"
#include "StatementNode.h"
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

using namespace std;

class TermNode : public ExpressionNode {
protected:

public:

	virtual pair<string, string> evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);

	virtual ~TermNode();
};

inline pair<string, string> TermNode::evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) { 
	pair<string,string> node;
	return node;
}

inline TermNode::~TermNode() { }

#endif //TERM_NODE_H