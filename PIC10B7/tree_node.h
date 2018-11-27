#ifndef TREE_NODE_H
#define TREE_NODE_H

/**
 Forward declaration
 */
template <typename T>
class BSTree;

template <typename T>
class TreeNode;

/**
 StackNode Interface
 */
template <typename T>
class TreeNode {
public:
    inline TreeNode( const T& nData ) : data(nData) , left(0) , right(0) {} // <-- Do nothing.
    inline T get_value() const { return data; }
    
    friend class BSTree<T>;
private:
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
};

#endif