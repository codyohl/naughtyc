#ifndef FUNC_DEC_NODE_H
#define FUNC_DEC_NODE_H

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

/* The Top level Node of an AST. */
class FunctionDeclarationNode : public Node {
protected:
string name;
bool isSFunction;
vector<ParameterNode*> parameterList;

public:
	FunctionDeclarationNode(string* id, bool isSFunction, vector<ParameterNode*>* params);

	~FunctionDeclarationNode();

	virtual void printNode(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);

	void compile(map<string,string> &symbolTable);
};

inline FunctionDeclarationNode::FunctionDeclarationNode(string* id, bool isSFunction, vector<ParameterNode*>* params) {
	this->name = *id;
	this->isSFunction = isSFunction;
	this->parameterList = *params;
	delete params;
	delete id;
}

inline void FunctionDeclarationNode::printNode(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) {
	compile(symbolTable);
	
	string retType = isSFunction?  naughtToC["string"] : naughtToC["int"];

	out << retType << " " << name << "(";

	for (unsigned int i = 0; i < parameterList.size(); i++) {
		parameterList[i]->printNode(out, symbolTable, numTabs, temp);
		if (i != parameterList.size()-1)
			out << ", ";
	}
	out << ");" << endl;

}

/* runs compile time checks on the node */
inline void FunctionDeclarationNode::compile(map<string,string> &symbolTable) {
	// if (!validateName(name))
	// 	err("Invalid name for function: " + name);
	if (symbolTable.count(name)) {
		err("Multiple function declarations found: " + name);
	}
	symbolTable[name] = isSFunction? "string" : "int";
}

inline FunctionDeclarationNode::~FunctionDeclarationNode() {
	for (auto p : parameterList)
		delete p;
}

#endif //FUNC_DEC_NODE_H