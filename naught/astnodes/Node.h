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

    // Node();
    // virtual ~Node();

    // signature of the node method that will 
    virtual void printNode(ofstream &out, map<string, string> &symbol_table, int numTabs);

    // method used to print the node, for debugging.
    friend std::ostream& operator<< (std::ostream &out, const Node &node);
};

// inline Node::Node() { }
// inline Node::~Node() { }

friend std::ostream& operator<< (std::ostream &out, const Node &node) {
  return out << "Node { }";
}

#endif //NODE_H