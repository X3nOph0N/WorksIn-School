#pragma once
#include<string>
template<int N>
class HuffleCode {
    public:
    HuffleCode(unsigned*);
    void generateBinFile(std::string);
    bool readBinFile(std::string);
    int* getCode(){return _code;};
    private:
    unsigned _code[N];
};