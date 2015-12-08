#ifndef FUNC_DEC_NODE_H
#define FUNC_DEC_NODE_H

// include possible sub-nodes

using namespace std;

/* The Top level Node of an AST. */
class FunctionDeclarationNode {
private:


public:
	FunctionDeclarationNode();

	~FunctionDeclarationNode();

	printNode();
};

inline FunctionDeclarationNode::FunctionDeclarationNode() {
	
}

inline void FunctionDeclarationNode::printNode(ofstream* out) {
	// add the #includes.
	//out << "#include <stdio.h>"     << endl;
	//out << "#include <stdlib.h>"    << endl;
	//out << "#include <nstdlib.h>"   << endl;
	out << endl << endl;

	//TODO: create the symbol table, add all nstdlib function declarations.
	map<string, string>* symbolTable = new map<string, string>();

	int numTabs = 0;

	// prints each item into the file.
	for (auto f : funcdecs) {
		f->printNode(out, symbolTable, numTabs)
	}
	out << endl;
	for (auto f : vardecs) {
		f->printNode(out, symbolTable, numTabs)
	}
	out << endl;
	for (auto f : funcdefs) {
		f->printNode(out, symbolTable, numTabs)
	}
	out << endl;

	delete symbolTable;
}

inline FunctionDeclarationNode::~FunctionDeclarationNode() {
	if (funcdecs) {
		for( auto item : funcdecs)
			delete item;
		delete funcdecs;
	}

	if (funcdefs) {
		for( auto item : funcdefs)
			delete item;
		delete funcdefs;
	}

	if (vardecs) {
		for( auto item : vardecs)
			delete item;
		delete vardecs;
	}
}

#endif //FUNC_DEC_NODE_H