#include"PriorityQueue.h"
#include<initializer_list>
#include<cstring>
#include<vector>
#include<iostream>

void PriorityQueue::_MakePile(){
 int currentHieracyIndex = _maxSize/2-1;
    while(currentHieracyIndex>0){
        for(int i = currentHieracyIndex;i<_size&&i<2*currentHieracyIndex+1;i++){
            if(_data[i].second<_data[(i+i%2)/2-1].second){
                std::pair<char,unsigned> temp=_data[i];
                _data[i]=_data[(i+i%2)/2-1];
                _data[(i+i%2)/2-1]=temp;
            }
        }
        currentHieracyIndex = (currentHieracyIndex+1)/2-1;
    }
};

PriorityQueue::PriorityQueue(){
    _data = new std::pair<char,unsigned>[1];
    _maxSize=1;
    _size=0; 
}

PriorityQueue::PriorityQueue(std::initializer_list<std::pair<char,unsigned>> datas){   
    _data = new std::pair<char,unsigned>[1];
    _maxSize=1;
    _size=0;
    std::cerr<<1;
    for(auto data : datas){
        if(_size>=_maxSize){
            _maxSize=_maxSize<<1;
            std::pair<char,unsigned>* temp = new std::pair<char,unsigned>[_maxSize];
            std::memcpy(temp,_data,_size*sizeof(std::pair<char,unsigned>));
            delete[] _data;
            _data=temp;
        }
        *(_data+_size)=data;
         _size++;
    }
    _MakePile();
};

PriorityQueue::PriorityQueue(std::vector<std::pair<char,unsigned>> datas){
    _data = new std::pair<char,unsigned>[1];
    _maxSize=1;
    _size=0;
    for(auto data : datas){
        if(_size>=_maxSize){
            _maxSize=_maxSize<<1;
            std::pair<char,unsigned>* temp = new std::pair<char,unsigned>[_maxSize];
            std::memcpy(temp,_data,_size*sizeof(std::pair<char,unsigned>));
            delete[] _data;
            _data=temp;
        }
        *(_data+_size)=data;
         _size++;
    }
    _MakePile();
};

std::pair<char,unsigned> PriorityQueue::_Pop(){
    if(_size==0){
        return std::make_pair(NULL,0);
    }
    std::pair<char,unsigned>* temp=_data;
    _data++;
    _size--;
    _MakePile();
    return *temp;
}

void PriorityQueue::_Push(std::pair<char,unsigned> data){
    if(_size>=_maxSize){
        _maxSize=_maxSize<<1;
        std::pair<char,unsigned>* temp = new std::pair<char,unsigned>[_maxSize];
        std::memcpy(temp,_data,_size*sizeof(std::pair<char,unsigned>));
        delete[] _data;
        _data=temp;
    }
    *(_data+_size)=data;
    _size++;
    _MakePile();
}

