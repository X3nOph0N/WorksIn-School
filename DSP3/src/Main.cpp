#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<regex>
#include"HufflemanTree.h"
#include"PriorityQueue.h"

using namespace std;

void generateHufflemanCodeFile(fstream*,map<char,string>*);
void generateBinFile(fstream*,string,map<char,string>);

int main(){

    map<char,unsigned int>Alphabet;
    fstream fileOperator;
    string fileName;
    string fileContent;
    map<char,string>Encoder;
    map<string,char>Decoder;

    cerr << "Please enter the file name(*.txt) for processing\n";
    cin >> fileName;

    fileOperator.open(fileName,fstream::in);
    char cBuff;
    while(fileOperator.get(cBuff)){
        fileContent+=cBuff;
        if(Alphabet.find(cBuff)!=Alphabet.end()){
            Alphabet[cBuff]++;
        }
        else{
            Alphabet.emplace(make_pair(cBuff,1));
        }
    }
    fileOperator.close();


    PriorityQueue* CharQueue= new PriorityQueue;
    for(auto character:Alphabet){
            CharQueue->_Push(character);
    }
    HufflemanTree CharTree(CharQueue);

    fileOperator.open(fileName.substr(0,fileName.size()-4)+"Code.txt",fstream::out);
    cerr << "Generating huffleman code for file "<<fileName<<endl;
    Encoder=CharTree._generateHufflemanCode();
    generateHufflemanCodeFile(&fileOperator,&Encoder);
    fileOperator.close();
    for(auto code:Encoder){
        Decoder.emplace(make_pair(code.second,code.first));
    }

    string outputBinFileName = fileName.substr(0,fileName.size()-4)+"Bin.txt";
    fileOperator.open(outputBinFileName,fstream::out);
    cerr<<"Generating binary code file for file "<<fileName<<endl;
    generateBinFile(&fileOperator,fileContent,Encoder);
    fileOperator.close();

    //TODO:read the bin file and reGenerate the text code.
    fileOperator.open(fileName.substr(0,fileName.size()-4)+"Bin.txt",fstream::in);
    string buffer="";
    string reFileContent;
    while(fileOperator.get(cBuff)){
        buffer+=cBuff;
        if(Decoder.find(buffer)!=Decoder.end()){
            reFileContent+=Decoder[buffer];
            buffer.clear();
        }
    }
    fileOperator.close();

    fileOperator.open((fileName.substr(0,fileName.size()-4)+"REGENERATED.txt"),fstream::out);
    cerr<<"Regenerating textCode for file "<<fileName<<endl;
    fileOperator<<reFileContent;
    fileOperator.close();


    return 0;

}

void generateHufflemanCodeFile(fstream* fileOperator,map<char,string>* Encoder){

    *fileOperator<<"{"<<endl;
    for(auto character:*Encoder){
        *fileOperator<<"{"<<character.first<<":"<<character.second<<"}"<<endl;
    }
    *fileOperator<<"}";
}

void generateBinFile(fstream* fileOperator,string fileContent,map<char,string> Encoder){
    for(int i=0;i<fileContent.length();i++){
        *fileOperator<<Encoder[fileContent[i]];
    }
}


