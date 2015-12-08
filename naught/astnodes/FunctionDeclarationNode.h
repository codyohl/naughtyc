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
	// if (funcdecs) {
	// 	for( auto item : funcdecs)
	// 		delete item;
	// 	delete funcdecs;
	// }

	// if (funcdefs) {
	// 	for( auto item : funcdefs)
	// 		delete item;
	// 	delete funcdefs;
	// }

	// if (vardecs) {
	// 	for( auto item : vardecs)
	// 		delete item;
	// 	delete vardecs;
	// }
}

#endif //FUNC_DEC_NODE_H