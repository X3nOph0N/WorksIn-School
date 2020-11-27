#include"BinaryTree.h"

namespace Project3{
template <class NodeType>
BinaryTree<NodeType>::BinaryTree(bool __inputCompare(const NodeType,const NodeType)=nullptr){
    if(__inputCompare){
        __compare = __inputCompare;
    }
    else{
        
        __comapre =[const NodeType a,const NodeType b]{
            return static_cast<unsigned>(a)>static_cast<unsigned>(b);
        };
    }
}
}

