#ifndef VAR_DEC_NODE_H
#define VAR_DEC_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
#include <map>
#include <string>
#include <cstring>

using namespace std;

/* The Top level Node of an AST. */
class VariableDeclarationNode : public Node {
protected:


public:
	VariableDeclarationNode();

	~VariableDeclarationNode();

	void printNode(ofstream &out, map<string,string> &symbolTable, int numTabs);

	void compile(map<string,string> &symbolTable);
};

inline VariableDeclarationNode::VariableDeclarationNode() {

}

inline void VariableDeclarationNode::printNode(ofstream &out, map<string,string> &symbolTable, int numTabs) {
	compile(symbolTable);

	out << "Variable Declaration node" << endl;
}

inline VariableDeclarationNode::~VariableDeclarationNode() {
}

/* runs compile time checks on the node */
inline void VariableDeclarationNode::compile(map<string,string> &symbolTable) {
	// if (!validateName(name))
	// 	err("Invalid name for function: %s", name);
	// if (symbolTable.count(name)) {
	// 	 cout << "Error: " << "Multiple variable declarations found: " << name;
	// 	 exit(2);
	// }

	// add our name to the symbol table.
}

#endif //VAR_DEC_NODE_H