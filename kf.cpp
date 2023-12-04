#include "kf.h"

kf::kf(string keys)
{
    this->key = keys;
    this->freq = 0;
}
kf::kf(string keys, int freq)
{
    this->key = keys;
    this->freq = freq;
}

string kf::getKey()
{
    return this->key;
}
int kf::getFreq()
{
    return this->freq;
}

void kf::changeKey(string key)
{
    this->key = key;
}

void kf::changeFreq(int freq)
{
    this->freq = freq;
}

// kf::~kf()
// {
// }