#pragma once
#include<initializer_list>
#include<vector>
#include<map>
#include<iostream>
#include<cstdlib>
class PriorityQueue {
    private:
    std::pair<char,unsigned>* _data;
    unsigned int _size;
    unsigned int _maxSize;
    void _MakePile();
    public:
    PriorityQueue();
    PriorityQueue( std::initializer_list<std::pair<char,unsigned>> );
    PriorityQueue( std::vector<std::pair<char,unsigned>>);
    std::pair<char,unsigned> _Pop();
    void _Push(std::pair<char,unsigned>);
    inline bool _IsEmpty() const{return (_size ==0);}
    inline unsigned int _GetSize() const{return _size;}

    template <typename T>
    static void _PubMakePile(T* start,unsigned int inputSize){
        unsigned int maxSize=1;
        while(maxSize<inputSize){
            maxSize=maxSize<<1;
        }
        int currentHieracyIndex = maxSize/2-1;
        while(currentHieracyIndex>0){
            for(int i = currentHieracyIndex;i<inputSize&&i<2*currentHieracyIndex+1;i++){
                if(start[i]<start[(i+i%2)/2-1]){
                    T* temp = new T;
                    memcpy(temp,start+i,sizeof(T));
                    memcpy(start+i,start+(i+i%2)/2-1,sizeof(T));
                    memcpy(start+(i+i%2)/2-1,temp,sizeof(T));
                    delete temp;
                    temp=nullptr;
                }
            }
        currentHieracyIndex = (currentHieracyIndex+1)/2-1;
        }
    }
};