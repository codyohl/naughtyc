#ifndef MODULE_NODE_H
#define MODULE_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
#include "FunctionDeclarationNode.h"
#include "FunctionDefinitionNode.h"
#include "VariableDeclarationNode.h"
#include <string>
#include <cstring>
#include <map>

using namespace std;

/* The Top level Node of an AST. */
class ModuleNode : public Node {
protected:
	vector<FunctionDeclarationNode*> funcdecs;
	vector<FunctionDefinitionNode*>  funcdefs;
	vector<VariableDeclarationNode*> vardecs;

public:
	ModuleNode(vector<FunctionDeclarationNode*>* functionDecs, 
			vector<VariableDeclarationNode*>* variableDecs,
			vector<FunctionDefinitionNode*>* functionDefs);

	~ModuleNode();

	void printNode(ofstream &out, int &temp);
};

inline ModuleNode::ModuleNode(vector<FunctionDeclarationNode*>* functionDecs, 
			vector<VariableDeclarationNode*>* variableDecs,
			vector<FunctionDefinitionNode*>* functionDefs) {
	funcdecs = *functionDecs;
	funcdefs = *functionDefs;
	vardecs  = *variableDecs;

	delete functionDecs;
	delete functionDefs;
	delete variableDecs;
}

inline void ModuleNode::printNode(ofstream &out, int &temp) {
	// add the #includes.
	out << "#include <stdio.h>"     << endl;
	out << "#include <stdlib.h>"    << endl;
	// out << "#include \"nstdlib.h\""   << endl;
	out << "#include <nstdlib.h>"   << endl;
	out << "#include <inttypes.h>"  << endl;
	out << endl << endl;

	//TODO: create the symbol table, add all nstdlib function declarations.
	map<string, string> symbolTable = {
		{"nstrlen", "string"}
	};	

	int numTabs = 0;

	// prints each item into the file.
	for (auto f : funcdecs) {
		f->printNode(out, symbolTable, numTabs, temp);
	}
	for (auto f : vardecs) {
		f->printNode(out, symbolTable, numTabs, temp);
	}
	for (auto f : funcdefs) {
		f->printNode(out, symbolTable, numTabs, temp);
	}
	out << endl;
}

inline ModuleNode::~ModuleNode() {
	for (auto p : funcdecs)
		delete p;
	for (auto p : funcdefs)
		delete p;
	for (auto p : vardecs)
		delete p;
}

#endif //MODULE_NODE_H