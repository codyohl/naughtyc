#ifndef PARAM_NODE_H
#define PARAM_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"

#include <map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>

using namespace std;

/* The Top level Node of an AST. */
class ParameterNode : public Node {
protected:
string name;
string type;

public:
	ParameterNode(string* t, string* n);

	~ParameterNode();

	virtual void printNode(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);
};

inline ParameterNode::ParameterNode(string* t, string* n) {
	this->name = *n;
	this->type = *t;

	delete n;
	delete t;
}

inline void ParameterNode::printNode(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) {
	// prints the type then the name.
	out << naughtToC[type] << " " << name; 

}

inline ParameterNode::~ParameterNode() {

}

#endif //PARAM_NODE_H