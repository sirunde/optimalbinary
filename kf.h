
#ifndef KF_H
#define KF_H

#include <stdlib.h>
#include <string>
using namespace std;
class kf
{
private:
    /* data */
    string key;
    int freq;

public:
    kf(string keys);
    kf(string keys, int freq);
    string getKey();
    int getFreq();
    void changeKey(string key);
    void changeFreq(int freq);
    // ~kf();
};
#endif