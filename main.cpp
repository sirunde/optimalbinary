// successful search only
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <chrono>
#include <tuple>
#include <random>
#include <numeric>

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
            root[i][i + 1] = i; //root table is 0 indexed always
        }
        root[i][i] = 0;
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
                        root[i][j] = r; //0 indexed
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
        return (struct1.getKey() < struct2.getKey());
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
    if(i >= j || i < 0 || j < 0 || i > kfs.size() || j > kfs.size()){
        return NULL;
    }
    int root = table[i][j];
    // cout << i << " " << j << " " << kfs[root].getKey() << endl;
    BSTNode* node = new BSTNode(kfs[root].getKey(), kfs[root].getFreq());
    if(i + 1 == j){
        return node;
    }
    node->left = buildBSTRecursive(i, root, kfs, table);
    node->right = buildBSTRecursive(root+1, j, kfs, table);
    return node;
}

//build optimal bst from root matrix
//each entry in root table represents index of key in kfs
BST* buildOptimalBST(vector<kf> kfs, vector<vector<int>> table)
{
    int n = kfs.size();
    int root = table[0][n];
    // cout << root << kfs[root].getKey() << endl;
    BST* bst = new BST(kfs[root].getKey(), kfs[root].getFreq());
    bst->root->left = buildBSTRecursive(0, root, kfs, table);
    bst->root->right = buildBSTRecursive(root+1, n, kfs, table);
    return bst;
}
float pointSumX(float lhs, const kf& rhs)
{
    return lhs + rhs.getFreq();
}

int main()
{
    // store keys and Freqs together
    // kf is class for holding key and freq same time
    auto start = chrono::high_resolution_clock::now();
    vector<kf> kfs;

    cout << "Test Case Size 5" << endl;
    kfs.push_back(kf("A", 25));
    kfs.push_back(kf("B", 20));
    kfs.push_back(kf("C", 5));
    kfs.push_back(kf("D", 20));
    kfs.push_back(kf("E", 30));
    sort(kfs.begin(),kfs.end(),less_than_freq());

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
    auto duration = chrono::duration<double>(stop - start);
    cout << "Time taken to find and build optimal BST is " << duration.count() << " second" << endl;

    cout << endl;
    cout << "Printing BST: " << endl;
    cout << "Root----------------->Leaf" << endl;
    optimal_tree->print(optimal_tree->root,"",false);
    cout << endl;

    // to do:

    // print optimal bst structure

    vector<kf> testCase;
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist6(1,50);
    int te[] = {100,500,1000};
    for(auto j: te){
        testCase.clear();
        cout << "Test Case Size " << j << endl;
        for(int i = 0; i < j;i++){
            char a = 'a';
            a += i;
            string s(1,a);
            testCase.push_back(kf(s,dist6(rng)));
        }
        sort(testCase.begin(),testCase.end(),less_than_freq());
        // to make toatl 1, but not sure if we need it or not
        // int sumAll = accumulate(kfs.begin(),kfs.end(),0,pointSumX);
        result = optimalBST(testCase);
        root = get<1>(result);
        cost = get<0>(result);
        optimal_tree = buildOptimalBST(testCase, root);

        cout << "Search Cost of Optimal BST is " << cost  << endl;


        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration<double>(stop - start);
        cout << "Time taken to find and build optimal BST is " << duration.count() << " second for " << j << " nodes" << endl;
        cout << endl;
    }
    // since nodes are too much, it is hard to print, so removed.
    /*
    cout << endl;
    cout << "Printing BST: " << endl;
    cout << "Root----------------->Leaf" << endl;
    optimal_tree->print(optimal_tree->root,"",false); 
    */
    return 0;
}