#pragma once
#include<map>
#include<string>
#include"PriorityQueue.h"

class TreeNode{
    public:
    std::pair<char,int> _data;
    TreeNode* lChild;
    TreeNode* rChild;
    TreeNode()
    :_data(std::make_pair((char)0,0))
    ,lChild(nullptr)
    ,rChild(nullptr){
    };
    bool operator<(const TreeNode& inputNode) const{
        return this->_data.second<inputNode._data.second;
    }
};

class HufflemanTree{
    private:
    TreeNode* _start;
    TreeNode* _root;
    void _findCode(std::map<char,std::string>*,TreeNode*,std::string);
    public:
    HufflemanTree(PriorityQueue*);
    std::map<char,std::string> _generateHufflemanCode();
    
};