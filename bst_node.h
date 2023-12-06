#ifndef BSTNODE_H
#define BSTNODE_H
#include <stdlib.h>
#include <string>
using namespace std;

class BSTNode
{
public:
    string key;
    int freq;
    BSTNode *left;
    BSTNode *right;
    BSTNode(string key);
    BSTNode(string key, int freq);
    ~BSTNode();
};

#endif