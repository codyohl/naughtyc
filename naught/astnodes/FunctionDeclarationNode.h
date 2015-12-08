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

inline void FunctionDeclarationNode::printNode(ofstream* out, map<string,string> symbolTable, int numTabs) {
	
}

inline FunctionDeclarationNode::~FunctionDeclarationNode() {
	
}

#endif //FUNC_DEC_NODE_H