#ifndef TERM_LITERAL_NODE_H
#define TERM_LITERAL_NODE_H

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

class TermLiteralNode : public TermNode {
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
	if(type.compare("string")) {
		out << type << " temp" << temp << " = nstr_new(" << literal << ");" << endl;
		TABS(out, numTabs);
		retVal.first = "temp" + to_string(temp++);
	} else {
		retVal.first = literal;
	}

	retVal.second = type;

	return retVal;
}

inline TermLiteralNode::~TermLiteralNode() {
	
}

#endif //TERM_LITERAL_NODE_H