#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>

using namespace std;

class Node {
  public:
    // signature of the node method that will print the node  (overridden by sub nodes.)
    virtual void printNode(ofstream &out, map<string, string> &symbolTable, int numTabs);
    // virtual destructor.
    virtual ~Node();
};

inline void Node::printNode(ofstream &out, map<string, string> &symbolTable, int numTabs) {
  out << " Basic Node ";
}

inline Node::~Node() {}

#endif //NODE_H