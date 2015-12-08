#ifndef BLOCK_NODE_H
#define BLOCK_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
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

class BlockNode : public Node {
protected:
vector<string*> varDecList;
vector<string*> stmtList;

public:
	BlockNode();//vector<string*>* variabledecs, vector<string*>* statements);

	~BlockNode();

	virtual void printNode(ofstream &out, map<string,string> &symbolTable, int numTabs);
};

inline BlockNode::BlockNode(){//vector<string*>* variabledecs, vector<string*>* statements) {
	// this->varDecList = *variabledecs;
	// this->stmtList = *statements;
}

inline void BlockNode::printNode(ofstream &out, map<string,string> &symbolTable, int numTabs) {
	
	out << "Block node" << endl;
}

inline BlockNode::~BlockNode() {
	for (auto p : varDecList)
		delete p;
	for (auto p : stmtList)
		delete p;
}

#endif //BLOCK_NODE_H