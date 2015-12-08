#ifndef FUNC_DEC_NODE_H
#define FUNC_DEC_NODE_H

// include possible sub-nodes
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
class FunctionDeclarationNode {
private:


public:
	FunctionDeclarationNode();

	~FunctionDeclarationNode();

	void printNode(ofstream &out, map<string,string> &symbolTable, int numTabs);
};

inline FunctionDeclarationNode::FunctionDeclarationNode() {

}

inline void FunctionDeclarationNode::printNode(ofstream &out, map<string,string> &symbolTable, int numTabs) {
	
}

inline FunctionDeclarationNode::~FunctionDeclarationNode() {

}

#endif //FUNC_DEC_NODE_H