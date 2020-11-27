#include"HuffleCode.h"
#include<fstream>
#include<iostream>
#include<string>

using namespace std;

template<int N>
HuffleCode<N>::HuffleCode(unsigned inputCode[N]){
    for(int i = 0; i <n;i++){
        _code[i]=inputCode[i];
    }
}

template<int N>
void HuffleCode<N>::generateBinFile(string filename){
    fstream writeFile;
    filename+=".bin";
    writeFile.open(filename.c_str(),fstream::in|fstream::binary|fstream::_Noreplace);
    writeFile<<N;
    for(int i = 0; i < N;i++){
        writeFile<<_code[i];
    }
    writeFile.close();
}

template<int N>
bool HuffleCode<N>::readBinFile(string filename){
    fstream readFile;
    filename+=".bin";
    readFile.open(filename.c_str(),fstream::out|fstream::binary|fstream::_Nocreate);

}