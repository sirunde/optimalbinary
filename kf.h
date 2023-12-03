#ifndef KF_H
#define KF_H
class kf
{
private:
    /* data */
    int key;
    int freq;

public:
    kf(int keys);
    kf(int keys, int freq);
    int getKey();
    int getFreq();
    void changeKey(int key);
    void changeFreq(int freq);
    // ~kf();
};
#endif