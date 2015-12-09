#ifndef TERM_ID_NODE_H
#define TERM_ID_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
#include "VariableDeclarationNode.h"
#include "ExpressionNode.h"
#include "StatementNode.h"
#include "ParameterNode.h"
#include "TermNode.h"

#include <map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>

using namespace std;

class TermIDNode : public TermNode {
protected:
	string id;

public:

	TermIDNode(string* id);

	virtual pair<string, string> evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);

	virtual ~TermIDNode();
};

inline TermIDNode::TermIDNode(string* id) {
	this->id = *id;
	delete id;
}

inline pair<string, string> TermIDNode::evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) { 
	pair<string,string> retVal;
	retVal.first = id;
	retVal.second = symbolTable[id];

	return retVal;
}

inline TermIDNode::~TermIDNode() {
	
}

#endif //TERM_ID_NODE_H