// successful search only
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <chrono>
#include <tuple>
#include "kf.h"
#include "bst.h"
#include "bst_node.h"

#define MAX 9999999

// Helper function to calculate the sum of frequencies from index i to j
int sum(std::vector<kf> kfs, int i, int j)
{
    int s = 0;
    for (int k = i; k <= j; k++)
        s += kfs[k].getFreq();
    return s;
}

// bottom up DP for filling in cost and root matrix
// returns root matrix and optimal cost for bst
tuple<int,vector<vector<int>>> optimalBST(vector<kf> kfs)
{
    // initialize cost and root matrix
    int n = kfs.size();
    vector<vector<int>> cost(n+1);
    vector<vector<int>> root(n+1);
    for(int i = 0; i < n+1; i++){
        cost[i].resize(n+1);
        root[i].resize(n+1);
    }

    for (int i = 0; i <= n; i++)
    {
        // fill diagonal with 0
        cost[i][i] = 0;
        // fill with freq of key
        if (i < n)
        {
            cost[i][i + 1] = kfs[i].getFreq();
            root[i][i + 1] = i + 1;
        }
        root[i][i] = i;
    }

    // fill in cost and root matrix by diagonals (top left to bottom right)
    for (int d = 1; d <= kfs.size(); d++) // based on number of diagonal
    {
        for (int i = 0; i < kfs.size() - d + 1; i++)
        {
            int j = i + d;
            int min = MAX;
            if (d != 1)
            {
                for (int r = i; r < j; r++)
                {
                    int c = cost[i][r] + cost[r + 1][j];
                    if (c < min)
                    {
                        min = c;
                        root[i][j] = r;
                    }
                }
                cost[i][j] = min + sum(kfs, i, j - 1);
            }
        }
    }
    return make_tuple(cost[0][n], root);
}

// for sorting
struct less_than_freq
{
    inline bool operator() (const kf& struct1, const kf& struct2)
    {
        return (struct1.getFreq() > struct2.getFreq());
    }
};

void add(std::vector<kf> kfs, std::string key, int freq){
    kfs.push_back(kf(key,freq));
    std::sort(kfs.begin(),kfs.end(),less_than_freq());
    optimalBST(kfs);
}

// Default freq is 1 if no freq is provided
void updateFreq(std::vector<kf> kfs, std::string key, int freq = 1){
    auto i = std::find(kfs.begin(),kfs.end(), key);
    if(i != kfs.end()){
        i->changeFreq(freq);
    }
    optimalBST(kfs);
}

void updateKey(std::vector<kf> kfs, std::string key){
    auto i = std::find(kfs.begin(),kfs.end(), key);
    if(i != kfs.end()){
        i->changeKey(key);
    }
}
//recursive call for each node
BSTNode* buildBSTRecursive(int i, int j, vector<kf> kfs, vector<vector<int>> table){
    if(i > j || i < 0 || j > kfs.size()){
        return NULL;
    }
    int root = table[i][j];
    BSTNode* node = new BSTNode(kfs[root].getKey(), kfs[root].getFreq());
    node->left = buildBSTRecursive(i, root-1, kfs, table);
    node->right = buildBSTRecursive(root+1, j, kfs, table);
    return node;
}

//build optimal bst from root matrix
BST* buildOptimalBST(vector<kf> kfs, vector<vector<int>> table)
{
    int n = kfs.size();
    int root = table[0][n];
    BST* bst = new BST(kfs[root].getKey(), kfs[root].getFreq());
    bst->root->left = buildBSTRecursive(0, root -1, kfs, table);
    bst->root->right = buildBSTRecursive(root+1, n, kfs, table);
    return bst;
}


int main()
{
    // store keys and Freqs together
    // kf is class for holding key and freq same time
    auto start = chrono::high_resolution_clock::now();
    vector<kf> kfs;
    kfs.push_back(kf("A", 25));
    kfs.push_back(kf("B", 20));
    kfs.push_back(kf("C", 5));
    kfs.push_back(kf("D", 20));
    kfs.push_back(kf("E", 30));

    // kfs.push_back(kf("A", 213));
    // kfs.push_back(kf("B", 20));
    // kfs.push_back(kf("C", 547));
    // kfs.push_back(kf("D", 100));
    // kfs.push_back(kf("E", 120));

    tuple<int, vector<vector<int>>> result = optimalBST(kfs);
    vector<vector<int>> root = get<1>(result);
    int cost = get<0>(result);
    BST* optimal_tree = buildOptimalBST(kfs, root);

    cout << "Search Cost of Optimal BST is " << cost  << endl;


    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken to find and build optimal BST is " << duration.count() << "ms" << endl;
    cout << "Printing BST: " << endl;
    optimal_tree->print();

    // to do:

    // implement adding keys based on user input
    // show based on freq of input(change freq of key)
    // should have faster time
    // remove keys
    // print optimal bst structure

    return 0;
}