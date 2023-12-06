#include "kf.h"

kf::kf(std::string keys)
{
    this->key = keys;
    this->freq = 0;
}
kf::kf(std::string keys, int freq)
{
    this->key = keys;
    this->freq = freq;
}

std::string kf::getKey() const
{
    return this->key;
}
int kf::getFreq() const
{
    return this->freq;
}

void kf::changeKey(std::string key)
{
    this->key = key;
}

void kf::changeFreq(int freq)
{
    this->freq = freq;
}
bool kf::operator==(const kf& rhs) const {
    return this->key.compare(rhs.key) == 0;
}
bool kf::operator==(const std::string& key) const {
    return this->key.compare(key) == 0;
}
// kf::~kf()
// {
// }