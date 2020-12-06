#include<string>
#include<cstring>
#include<map>
#include<iostream>
#include"HufflemanTree.h"
#include"PriorityQueue.h"

using namespace std;

HufflemanTree::HufflemanTree(PriorityQueue* CharQueue){
    unsigned int cnt=CharQueue->_GetSize();
    _start =new TreeNode[2*cnt-1];
    for(int i=0; i<cnt;i++){
        TreeNode temp1;
        temp1._data=CharQueue->_Pop();
        *(_start+i) = temp1;
    }
    int size=cnt;
    int currentPos=0;
    for(int i=cnt;i<2*cnt-1;i++){
        TreeNode *temp1=_start+currentPos++;
        size--;
        PriorityQueue::_PubMakePile<TreeNode>(_start+currentPos,size);
        TreeNode *temp2=_start+currentPos++;
        size--;
        PriorityQueue::_PubMakePile<TreeNode>(_start+currentPos,size);
        TreeNode *temp3=new TreeNode();
        temp3->lChild=temp1;
        temp3->rChild=temp2;
        temp3->_data.second=temp1->_data.second+temp2->_data.second;
        memcpy(_start+i,temp3,sizeof(TreeNode));
        size++;
        PriorityQueue::_PubMakePile<TreeNode>(_start+currentPos,size);
    }
    if(cnt==1){
        _root=_start;
    }
    else{
        _root=_start+2*cnt-2;
    }
    for(int i=0;i<2*cnt-1;i++){
    }
}

map<char,string> HufflemanTree::_generateHufflemanCode(){
    map<char,string>Encoder;
    string init = "";
    _findCode(&Encoder,_root,init);
    return Encoder;
}

void HufflemanTree::_findCode(map<char,string>* Encoder,TreeNode* root,string currentCode){
    if(root==nullptr){
        return;
    }
    if((int)root->_data.first!=0){
        Encoder->emplace(make_pair(root->_data.first,currentCode));
    }
    else{
        _findCode(Encoder,root->lChild,currentCode+"0");
        _findCode(Encoder,root->rChild,currentCode+"1");
    }
} 