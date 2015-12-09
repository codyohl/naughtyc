#ifndef TERM_UNARY_NODE_H
#define TERM_UNARY_NODE_H

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

class TermUnaryNode : public TermNode {
protected:
	string unary;
	TermNode* term;

public:

	TermUnaryNode(string* unary, TermNode* term);

	virtual pair<string, string> evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);

	virtual ~TermUnaryNode();
};

inline TermUnaryNode::TermUnaryNode(string* unary, TermNode* term) {
	this->unary = *unary;
	this->term = term;
	delete unary;
}

inline pair<string, string> TermUnaryNode::evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) { 
	auto pair = term->evaluate(out, symbolTable, numTabs, temp);

	map<string,string> typesFormatStr = {
		{"string", "%s"},
		{"int", "%d"},
		{"pointer", "%p"}
	};	

	if (!unary.compare("print")) {
		out << "printf(\"" << typesFormatStr[pair.second] << "\", " << pair.first << ");" << endl;
		TABS(out, numTabs);
		return pair;
	}
	else if (!unary.compare("@")) {
		pair.second = "int";
		out << naughtToC[pair.second] << " temp" << temp << " = *" << pair.first << endl;
		TABS(out, numTabs);
		pair.first = "temp" + to_string(temp);
		temp++;
		return pair;
	}
	else if (!unary.compare("&")) {
		pair.second = "pointer";
		out << naughtToC[pair.second] << " temp" << temp << " = &" << pair.first << endl;
		TABS(out, numTabs);
		pair.first = "temp" + to_string(temp);
		temp++;
		return pair;
	}
	cout << "Wrong unary operator: " << unary;
	exit(2);
}

inline TermUnaryNode::~TermUnaryNode() {
	
}

#endif //TERM_UNARY_NODE_H