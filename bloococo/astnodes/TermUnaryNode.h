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
		{"string", "\045s\\n"},
		{"int", "\045d\\n"},
		{"pointer", "\045p\\n"},
	};	

	if (!unary.compare("print")) {
		// shouldn't be an lvalue. also assumes int if no type info is found (from func call)
		string formatStr = typesFormatStr.count(pair.second) ? typesFormatStr[pair.second] : "\045d\\n";
		out << "printf(\"" << formatStr << "\", " << pair.first << ");" << endl;
		TABS(out, numTabs);
		return pair;
	}
	else if (!unary.compare("@")) {
		if (pair.second.compare("pointer"))
			err("Invalid dereference of non-pointer type: " + pair.second);

		pair.second = "int";
		//out << naughtToC[pair.second] << " temp" << temp << " = *" << pair.first << endl;
		//out << "*";
		//TABS(out, numTabs);
		//pair.first = "temp" + to_string(temp);
		//temp++;

		// I convinced myself that basically, this is just a one time dereference so we simply dereference the result of the previous expression.
		// this doesnt create a temp because that wouldn't work if it was meant to be an lvalue. (it would simply copy, and a reassign would fail)
		pair.first = "*(" + pair.first + ")";
		return pair;
	}
	else if (!unary.compare("&")) {
		if (!pair.second.compare("string"))
			err("Can't take address of string type: " + pair.first);
		// since no lvalue for address, just create a temp.
		pair.second = "pointer";
		out << naughtToC[pair.second] << " temp" << temp << " = &(" << pair.first << ");" << endl;
		TABS(out, numTabs);
		pair.first = "temp" + to_string(temp);
		temp++;
		return pair;
	}
	err("Wrong unary operator: " + unary);
	exit(2);
}

inline TermUnaryNode::~TermUnaryNode() {
	
}

#endif //TERM_UNARY_NODE_H