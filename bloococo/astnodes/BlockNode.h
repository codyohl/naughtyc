#ifndef BLOCK_NODE_H
#define BLOCK_NODE_H

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

class BlockNode : public Node {
protected:
vector<VariableDeclarationNode*> varDecList;
vector<StatementNode*> stmtList;

public:
	BlockNode(vector<VariableDeclarationNode*>* variabledecs, vector<StatementNode*>* statements);

	~BlockNode();

	virtual void printNode(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);
};

inline BlockNode::BlockNode(vector<VariableDeclarationNode*>* variabledecs, vector<StatementNode*>* statements) {
	this->varDecList = *variabledecs;
	this->stmtList = *statements;

	delete variabledecs;
	delete statements;
}

inline void BlockNode::printNode(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) {
	for( auto v : varDecList ) {
		TABS(out, numTabs);
		v->printNode(out, symbolTable, numTabs, temp);
		out << endl;
	}
	for( auto s : stmtList ) {
		TABS(out, numTabs);
		s->printNode(out, symbolTable, numTabs, temp);
		out << endl;
	}
}

inline BlockNode::~BlockNode() {
	for (auto p : varDecList)
		delete p;
	for (auto p : stmtList)
		delete p;
}

#endif //BLOCK_NODE_H