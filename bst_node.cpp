#include "bst_node.h"

BSTNode::BSTNode(string key)
{
    this->key = key;
    this->freq = 0;
    this->left = NULL;
    this->right = NULL;
}

BSTNode::BSTNode(string key, int freq)
{
    this->key = key;
    this->freq = freq;
    this->left = NULL;
    this->right = NULL;
}

BSTNode::~BSTNode()
{
    delete left;
    delete right;
}