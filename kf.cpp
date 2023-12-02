#include <kf.h>

kf::kf(int keys)
{
    this->key = keys;
    freq = 0;
}
kf::kf(int key, int freq)
{
    this->key = key;
    this->freq = freq;
}

int kf::getKey(){
    return this->key;
}
int kf::getFreq(){
    return this->freq;
}

void kf::changek(int key){
    this->key = key; 
}


void kf::changefq(int freq){
    this->freq = freq;
}

kf::~kf()
{
}