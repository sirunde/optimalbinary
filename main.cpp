// successful search only
#include <iostream>
#include <vector>
#include "kf.h"

using namespace std;

#define MAX 9999999

// Helper function to calculate the sum of frequencies from index i to j
int sum(vector<kf> kfs, int i, int j)
{
    int s = 0;
    for (int k = i; k <= j; k++)
        s += kfs[k].getFreq();
    return s;
}

// bottom up DP for filling in cost and root matrix
// returns root matrix and optimal cost for bst
int optimalBST(vector<kf> kfs)
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
            // cout << "i = " << i << " j = " << j << endl;
            if (d != 1)
            {
                for (int r = i; r < j; r++)
                {
                    int c = cost[i][r] + cost[r + 1][j];
                    // cout << "c = " << c << " " << i << " " << j << endl;
                    if (c < min)
                    {
                        min = c;
                        root[i][j] = r;
                    }
                }
                cost[i][j] = min + sum(kfs, i, j);
            }
            // cout << "cost[" << i << "][" << j << "] = " << cost[i][j] << endl;
        }
    }
    return cost[0][n];
}

int main()
{
    // store keys and Freqs together
    // kf is class for holding key and freq same time
    vector<kf> kfs;
    kfs.push_back(kf(1, 25));
    kfs.push_back(kf(2, 20));
    kfs.push_back(kf(3, 5));
    kfs.push_back(kf(4, 20));
    kfs.push_back(kf(5, 30));

    cout << "Search Cost of Optimal BST is " << optimalBST(kfs) << endl;

    // to do:

    // implement adding keys based on user input
    // show based on freq of input(change freq of key)
    // should have faster time
    // remove keys
    // print optimal bst structure

    return 0;
}