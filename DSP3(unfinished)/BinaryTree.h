#pragma once 

#include"TreeNode.h"
namespace Project3{ 
template <class NodeType>
class BinaryTree{
    public:
    BinaryTree(bool (const NodeType,const NodeType));
    void __insert(NodeType _inputData); 
    void __delete(NodeType _inputData);
    private:
    TreeNode<NodeType>* _rootPtr;
    bool (*__compare)(const NodeType,const NodeType);
};
}