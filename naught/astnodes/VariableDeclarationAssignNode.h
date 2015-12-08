#ifndef VARIABLE_DECL_ASSIGN_NODE_H
#define VARIABLE_DECL_ASSIGN_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
#include "ParameterNode.h"
//#include "ExpressionNode.h"
#include "StatementNode.h"
#include "VariableDeclarationNode.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>

using namespace std;

class VariableDeclarationAssignNode : public VariableDeclarationNode {
protected:
	//ExpressionNode* assignExpr; in subclass 

public:
	VariableDeclarationAssignNode();//string* t, string* n, bool ext, ExpressionNode* expr) : VariableDeclarationNode(t, n, ext);

	~VariableDeclarationAssignNode();

	virtual void printNode(ofstream &out, map<string,string> &symbolTable, int numTabs);
};

inline VariableDeclarationAssignNode::VariableDeclarationAssignNode() {//string* t, string* n, bool ext, ExpressionNode* expr) : VariableDeclarationNode(t, n, ext) {
	// this->assignExpr = expr;
}

inline void VariableDeclarationAssignNode::printNode(ofstream &out, map<string,string> &symbolTable, int numTabs) {
	
	out << "VariableDeclarationAssignNode";
}

inline VariableDeclarationAssignNode::~VariableDeclarationAssignNode() {
	//delete assignExpr;
}

#endif //VARIABLE_DECL_ASSIGN_NODE_H