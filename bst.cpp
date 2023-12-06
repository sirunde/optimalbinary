#include "bst.h"

BST::BST(string key)
{
    root = new BSTNode(key);
}

BST::BST(string key, int freq)
{
    root = new BSTNode(key, freq);
}

BST::~BST()
{
    delete root;
}

void BST::print(BSTNode* node, const string& padding, bool isLeft)
{
    if(node == NULL)
    {
        return;
    }
    cout << padding;
    cout << (isLeft ? "L--" : "R--");
    cout << "(" << node->key  << "," << node->freq << ")" << endl;
    print(node->left, padding+ (isLeft ? "|  " : "   "), true);
    print(node->right, padding+(isLeft ? "|  " : "   "), false);
}
