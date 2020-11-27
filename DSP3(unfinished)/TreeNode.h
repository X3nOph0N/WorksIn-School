#pragma once 
namespace Project3{
template <class NodeType>
class TreeNode {
    friend class Tree;
    public:
    TreeNode(NodeType _inputNodeData,TreeNode<NodeType>* _lc,TreeNode<NodeType>* _rc)
    :_nodeData(_inputNodeData)
    ,_lcPtr(_lc)
    ,_rcPtr(_rc)
    {};
    private:
    NodeType _nodeData;
    TreeNode<NodeType>* _lcPtr;
    TreeNode<NodeType>* _rcPtr;
};
}