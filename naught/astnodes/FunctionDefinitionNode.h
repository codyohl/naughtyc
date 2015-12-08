#ifndef FUNC_DEF_NODE_H
#define FUNC_DEF_NODE_H

// include possible sub-nodes
#include <map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

/* The Top level Node of an AST. */
class FunctionDefinitionNode {
private:


public:
	FunctionDefinitionNode();

	~FunctionDefinitionNode();

	void printNode(ofstream &out, map<string,string> &symbolTable, int numTabs);
};

inline FunctionDefinitionNode::FunctionDefinitionNode() {

}

inline void FunctionDefinitionNode::printNode(ofstream &out, map<string,string> &symbolTable, int numTabs) {
	out << "FunctionDefinitionNode" << endl;
}

inline FunctionDefinitionNode::~FunctionDefinitionNode() {
	
}

#endif //FUNC_DEF_NODE_H