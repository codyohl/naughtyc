#ifndef TERM_FUNCTION_CALL_NODE_H
#define TERM_FUNCTION_CALL_NODE_H

// include possible sub-nodes
#include "Types.h"
#include "Node.h"
#include "VariableDeclarationNode.h"
#include "ExpressionNode.h"
#include "StatementNode.h"
#include "ParameterNode.h"
#include "TermNode.h"
#include "TermFunctionCallNode.h"

#include <map>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>

using namespace std;

class TermFunctionCallNode : public TermNode {
protected:
	string functionName;
	vector<ExpressionNode*> argList;

public:

	TermFunctionCallNode(string* f, vector<ExpressionNode*>* a);

	virtual pair<string, string> evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp);

	virtual ~TermFunctionCallNode();
};

inline TermFunctionCallNode::TermFunctionCallNode(string* f, vector<ExpressionNode*>* a) {
	this->functionName = *f;
	this->argList = *a;
	delete f;
	delete a;
}

inline pair<string, string> TermFunctionCallNode::evaluate(ofstream &out, map<string,string> &symbolTable, int numTabs, int &temp) { 
	pair<string,string> retVal;
	// gets the type if it exists in the symbol table, otherwise assume int.
	retVal.second = symbolTable.count(functionName) ? symbolTable[functionName] : "int";

	string args = "";
	for (unsigned int i = 0; i < argList.size(); i++) {
		auto p = argList[i]->evaluate(out, symbolTable, numTabs, temp);
		args += p.first;
		if (i != argList.size() -1)
			args += ", ";
	}
	retVal.first = "temp" + to_string(temp);
	out << retVal.second << " " << retVal.first << " = " << functionName << "(" << args << ");" << endl;
	TABS(out, numTabs);
	
	temp++;
	return retVal;
}

inline TermFunctionCallNode::~TermFunctionCallNode() {
	
}

#endif //TERM_FUNCTION_CALL_NODE_H