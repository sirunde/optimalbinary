
#ifndef KF_H
#define KF_H

#include <stdlib.h>
#include <string>

class kf
{
private:
    /* data */
    std::string key;
    int freq;

public:
    kf(std::string keys);
    kf(std::string keys, int freq);
    std::string getKey() const;
    int getFreq() const;
    void changeKey(std::string key);
    void changeFreq(int freq);
    bool operator==(const kf& rhs) const;
    bool operator==(const std::string& rhs) const;
    // ~kf();
};
#endif