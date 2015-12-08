#ifndef VAR_DEC_NODE_H
#define VAR_DEC_NODE_H

// include possible sub-nodes

using namespace std;

/* The Top level Node of an AST. */
class VariableDeclarationNode {
private:


public:
	VariableDeclarationNode();

	~VariableDeclarationNode();

	printNode();
};

inline VariableDeclarationNode::VariableDeclarationNode() {

}

inline void VariableDeclarationNode::printNode(ofstream* out, map<string,string> symbolTable, int numTabs) {
	out << "Variable Declaration NOde" << endl;
}

inline VariableDeclarationNode::~VariableDeclarationNode() {
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

#endif //VAR_DEC_NODE_H