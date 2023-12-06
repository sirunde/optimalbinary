// successful search only
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include "kf.h"

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
int optimalBST(std::vector<kf> kfs)
{
    // initialize cost and root matrix
    int n = kfs.size();
    int cost[n + 1][n + 1];
    int root[n + 1][n + 1];

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
    return cost[0][n];
}

// for sorting
struct less_than_freq
{
    inline bool operator() (const kf& struct1, const kf& struct2)
    {
        return (struct1.getFreq() < struct2.getFreq());
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

int main()
{
    // store keys and Freqs together
    // kf is class for holding key and freq same time
    std::vector<kf> kfs;
    // kfs.push_back(kf(1, 25));
    // kfs.push_back(kf(2, 20));
    // kfs.push_back(kf(3, 5));
    // kfs.push_back(kf(4, 20));
    // kfs.push_back(kf(5, 30));

    // kfs.push_back(kf(1, 213));
    // kfs.push_back(kf(2, 20));
    // kfs.push_back(kf(3, 547));
    // kfs.push_back(kf(4, 100));
    // kfs.push_back(kf(5, 120));

    std::cout << "Search Cost of Optimal BST is " << optimalBST(kfs) << std::endl;

    // to do:

    // implement adding keys based on user input
    // show based on freq of input(change freq of key)
    // should have faster time
    // remove keys
    // print optimal bst structure

    return 0;
}