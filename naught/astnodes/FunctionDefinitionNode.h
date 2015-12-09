#ifndef FUNC_DEF_NODE_H
#define FUNC_DEF_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
#include "FunctionDeclarationNode.h"
#include "BlockNode.h"
#include <map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

/* The Top level Node of an AST. */
class FunctionDefinitionNode : public FunctionDeclarationNode {
protected:
	BlockNode* block;

public:
	FunctionDefinitionNode(string* id, bool isSFunction, vector<ParameterNode*>* params, BlockNode* block) ;

	void printNode(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);

	void compile(map<string,string> &symbolTable);

	~FunctionDefinitionNode();
};

inline FunctionDefinitionNode::FunctionDefinitionNode(string* id, bool isSFunction, vector<ParameterNode*>* params, BlockNode* block) 
						  : FunctionDeclarationNode(id, isSFunction, params) {
	this->block = block;
}

inline void FunctionDefinitionNode::printNode(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) {
	compile(symbolTable);
	// gets return type.
	string retType = isSFunction?  naughtToC["string"] : naughtToC["int"];

	TABS(out, numTabs);
	out << retType << " " << name << "(";

	for (unsigned int i = 0; i < parameterList.size(); i++) {
		parameterList[i]->printNode(out, symbolTable, numTabs, temp);
		if (i != parameterList.size()-1)
			out << ", ";
	}
	// now, prints the definition block.
	out << ") {" << endl;
	block->printNode(out, symbolTable, numTabs + 1, temp);
	out << "}" << endl;
}

/* runs compile time checks on the node */
inline void FunctionDefinitionNode::compile(map<string,string> &symbolTable) {
	symbolTable[name] = isSFunction? naughtToC["string"] : naughtToC["int"];
	// can possible run other checks here.
}

inline FunctionDefinitionNode::~FunctionDefinitionNode() {
	delete block;
}

#endif //FUNC_DEF_NODE_H