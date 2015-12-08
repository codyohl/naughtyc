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
	BlockNode block;

public:
	FunctionDefinitionNode(string* id, bool isSFunction, vector<ParameterNode*>* params, BlockNode* block) ;

	void printNode(ofstream &out, map<string,string> &symbolTable, int numTabs);

	void compile(map<string,string> &symbolTable);
};

inline FunctionDefinitionNode::FunctionDefinitionNode(string* id, bool isSFunction, vector<ParameterNode*>* params, BlockNode* block) 
						  : FunctionDeclarationNode(id, isSFunction, params) {
	this->block = *block;
	delete block;
}

inline void FunctionDefinitionNode::printNode(ofstream &out, map<string,string> &symbolTable, int numTabs) {
	compile(symbolTable);
	
	string retType = isSFunction?  naughtToC["string"] : naughtToC["int"];

	out << retType << " " << name << "(";

	for (unsigned int i = 0; i < parameterList.size(); i++) {
		parameterList[i]->printNode(out, symbolTable, numTabs);
		if (i != parameterList.size()-1)
			out << ", ";
	}
	out << ") {" << endl;

	out << name << " FunctionDefinitionNode (w block) " << endl;
	out << "}" << endl;
}

/* runs compile time checks on the node */
inline void FunctionDefinitionNode::compile(map<string,string> &symbolTable) {
	symbolTable[name] = isSFunction? naughtToC["string"] : naughtToC["int"];
	// can possible run other checks here.
}

#endif //FUNC_DEF_NODE_H