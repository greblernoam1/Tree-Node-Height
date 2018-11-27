

/* **********************************************************************
 
 File: hw6.h
 
 Author: Noam Grebler Farras
 
 UID: 304343111
 
 Date: March 13, 2016
 
 
 
 Program that creates 10000 binnary trees with n nodes and then calculates the average height for those trees.
 
 ********************************************************************** */




#ifndef HOMEMADE_BST_H
#define HOMEMADE_BST_H

#include "tree_node.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using std::ostream;
using std::vector;
using std::endl;
using std::size_t;


/**
 Function declarations
 */
template <typename T>
ostream& operator<<( ostream&  , const BSTree<T>& );


/**
 Stack Interface
 */
template <typename T>
class BSTree {
public:
    // Default constructor. Creates empty BST
    inline BSTree() : root(0)
    {}
    // Destructor. Continuously erase(root) until root is NULL
    inline ~BSTree()
    { while ( root ) erase(root); }
    // Copy constructor.
    inline BSTree( const BSTree<T>& b ) : root(0)
    { deep_copy( b.root ); }
    // Assignment operator: If not self-assignment, release & deep copy
    inline BSTree<T>& operator=( const BSTree<T>& b )
    { if ( this != &b ){ this->~BSTree(); deep_copy( b.root ); } return *this; }
    
    /**
	    Other member functions
     */
    inline bool is_empty() const
    { return ( root == 0 ); }
    inline TreeNode<T>* get_root() const
    { return root; }
    
    inline TreeNode<T>* find_maximum( TreeNode<T>* pos ) const
    { while ( pos->right ) pos = pos->right; return pos; }
    inline TreeNode<T>* find_minimum( TreeNode<T>* pos ) const
    { while ( pos->left ) pos = pos->left; return pos; }
    inline TreeNode<T>* find_maximum() const
    { return find_maximum(root); }
    inline TreeNode<T>* find_minimum() const
    { return find_minimum(root); }
    
    TreeNode<T>* find( const T& value ) const;
    TreeNode<T>* get_parent( TreeNode<T>* childNode ) const;
    TreeNode<T>* next_in_order( TreeNode<T>* pos ) const;
    
    void insert( const T& value );
    
    void erase( TreeNode<T>* pos );
    inline void erase( const T& value )
    { erase( find(value) ); }
    
    int height( TreeNode<T>* localRoot ) const;
    int height() const { return height(root); }
    
    size_t size( TreeNode<T>* localRoot ) const;
    size_t size() const { return size(root); }
    
    void pre_order( TreeNode<T>* localRoot , ostream& out ) const;
    void pre_order( ostream& out ) const
    { pre_order(root, out); }
    void in_order( TreeNode<T>* localRoot , ostream& out ) const;
    void in_order( ostream& out ) const
    { in_order(root, out); }
    void post_order( TreeNode<T>* localRoot , ostream& out ) const;
    void post_order( ostream& out ) const
    { post_order(root, out); }
    
    /**
     When are two BST's equal?
     */
    bool operator==( const BSTree<T>& b ) const ;
    inline bool operator!=( const BSTree<T>& b ) const
    { return !( *this == b );}
    
    /**
     Saves the contents of the BST into a vector
     The parameter is expected to be an empty vector.
     If this is not the case, it is OK to simply
     append the values at the end [of the vector].
     */
    void to_vector( TreeNode<T>* localRoot , vector<T>& v ) const ;
    void to_vector( vector<T>& v ) const
    { to_vector(root, v); }
    
private:
    // Common statements in: copy constr. & operator=
    void deep_copy( TreeNode<T>* nodeInSourceTree );
    
    TreeNode<T>* root;
};

/**
 ------------------------------------------------------------------
 Lines 108 -- 451 correspond to my implementation of a
 binary searh tree class (BSTree). Modify the contents
 at your own risk!!! This is the file that you will be
 uploading to CCLE. This program compiles against the
 provided driver hw6_tester.cpp, however it does not
 produce the right output. Your job is to add the missing
 implementations and 'make it work the way it is supposed to'.
 ------------------------------------------------------------------
 */

/**
 To find a value
 - Use the BST property:
 Move left for smaller values move right for bigger ones.
 
 NULL is returned if the value is not found.
 */
template <typename T>
TreeNode<T>* BSTree<T>::find( const T& value ) const {
    TreeNode<T>* pos = root;
    
    while( pos ){
        if ( value == pos->data )
            return pos;
        else if ( value < pos->data )
            pos = pos->left;
        else
            pos = pos->right;
    }
    
    return pos; // <-- returns NULL
}

/**
 To find the parent of a node
 - Use the BST property:
 Move left for smaller values move right for bigger ones
 At every move test the children for a match.
 
 NULL is returned if the parameter being passed
 is either the root node, or it points to a node
 outside of the BST.
 */
template <typename T>
TreeNode<T>* BSTree<T>::get_parent( TreeNode<T>* childNode ) const {
    // root has no parent
    if ( childNode == root )
        return 0;
    
    TreeNode<T>* pos = root;
    while ( pos ){
        if ( pos->left == childNode || pos->right == childNode )
            return pos;
        else if ( childNode->data < pos->data )
            pos = pos->left;
        else
            pos = pos->right;
    }
    
    return pos; // <-- returns NULL
}

/**
 To find the parent of a node
 Case 1: The right subtree of pos is non-empty.
 return the minimum value in the right subtree of pos.
 Case 2: The right subtree of pos is empty.
 Move up the tree through ancestors of pos and
 return the node found the first time a move to
 the right is made.
 */
template <typename T>
TreeNode<T>* BSTree<T>::next_in_order( TreeNode<T>* pos ) const {
    // case 1
    if ( pos->right )
        return find_minimum(pos->right);
    
    // case 2
    TreeNode<T>* parentNode = get_parent(pos);
    while ( parentNode ){
        // If moving right (i.e., pos is the left child), done.
        if ( parentNode->left == pos )
            return parentNode;
        
        // If not, keep moving up
        pos = parentNode;
        parentNode = get_parent(parentNode);
    }
    
    return 0; // <-- Only reach this part if there is no next in order.
}

/**
 To find a value
 - Use the BST property:
 Move left for smaller values move right for bigger
 ones. Continue until reaching NULL after a leaf.
 Have a trailing pointer follow every move to mark
 the place where insertion will take place.
 */
template <typename T>
void BSTree<T>::insert( const T& value ){
    // new node + trailing pointer + position pointer
    TreeNode<T>* newNode = new TreeNode<T>(value);
    TreeNode<T>* parentNode = 0;
    TreeNode<T>* pos = root;
    
    while ( pos ){
        parentNode = pos;
        if ( value == pos->data )
            return; // <-- We consider only BST's with different nodes
        if ( value < pos->data )
            pos = pos->left;
        else
            pos = pos->right;
    }
    
    if ( !parentNode )
        root = newNode;
    else if ( value <= parentNode->data )
        parentNode->left = newNode;
    else
        parentNode->right = newNode;
    
    return;
}

/**
 To erase a node marked by pos
 Case 1: pos has no children.
 Make the parent node point to NULL.
 Case 2: pos has one child
 The parent of the pos becomes the parent
 of the child of pos.
 In both of the previous cases, the node marked
 by pos will be deleted.
 
 Case 3: pos has two children
 */
template <typename T>
void BSTree<T>::erase( TreeNode<T>* pos ){
    // make sure we have a non-null node
    if ( pos ) {
        /**
         Request the parent of pos. This could be NULL
         if either pos is the root node or if pos is
         not a node in the BST.
         */
        TreeNode<T>* parentNode = get_parent(pos);
        if ( !parentNode ){
            if ( pos != root ){
                // pos is not in the BST. Do nothing!
                return;
            }
        }
        
        /**
         We are now certain pos is a valid node but we
         have to be careful, parentNode could still be
         NULL if pos is the root node.
         We need to check for this condition before
         attempting to dereference parentNode.
         */
        
        // Case 1: No children
        if ( !pos->left && !pos->right ){
            if ( parentNode ){
                // Find out which children is pos and rearrange links
                if ( parentNode->left == pos )
                    parentNode->left = 0;
                else
                    parentNode->right = 0;
            }
            else {
                /**
                 root is the only node in the BST with no parent
                 In this case, since it also does not have children
                 we know is the only node in the BST. Erasing pos
                 resets the BST.
                 */
                root = 0;
            }
        }
        
        // Case 2: One child
        else if ( pos->left && !pos->right ){
            if ( parentNode ){
                // Find out which children is pos and rearrange links
                if ( parentNode->left == pos )
                    parentNode->left = pos->left;
                else
                    parentNode->right = pos->left;
            }
            else{
                // We are deleting the root node, update the root marker
                root = pos->left;
            }
        }
        else if ( !pos->left && pos->right ){
            if ( parentNode ){
                // Find out which children is pos and rearrange links
                if ( parentNode->left == pos )
                    parentNode->left = pos->right;
                else
                    parentNode->right = pos->right;
            }
            else{
                // We are deleting the root node, update the root marker
                root = pos->right;
            }
            
        }
        
        // Case 3: Two children
        else{
            // Locate the node to be deleted
            TreeNode<T>* successor = next_in_order( pos );
            /**
             Although next_in_order could return NULL,
             for example if pos is the maximum value or
             if pos is not a valid BST node. In this case
             this cannot happen because pos is indeed a
             valid node and it has two children. In
             particular, it has a right child and therefore
             it cannot be the maximum value in the BST.
             */
            
            /**
             Copy the data over to the new node, move pos
             and request its parent.
             Note this parentNode is guaranteed to exist
             because in the worst case scenario it will be
             the original node that pos was pointing at.
             */
            pos->data = successor->data;
            pos = successor;
            parentNode = get_parent(pos);
            
            /**
             Find out which link to rearrange.
             Note that pos->left is null because pos
             is now a minimum value of a subtree.
             */
            if ( parentNode->left == pos )
                parentNode->left = pos->right;
            else
                parentNode->right = pos->right;
        }
        
        // pos marks the node that needs to be released
        delete pos;
        
    }
    
    return;
}

/**
 To compute the height:
 - Return 1 + maximum between the heights of the left
 and right subtrees of localRoot
 */
template <typename T>
int BSTree<T>::height( TreeNode<T>* localRoot ) const{
    if ( !localRoot )
        return -1;
    else {
        int leftHeight = height( localRoot->left );
        int rightHeight = height( localRoot->right );
        
        if ( leftHeight < rightHeight )
            return 1 + rightHeight;
        else
            return 1 + leftHeight;
    }
}

/**
 To compute the size:
 - Return 1 + size of right subtree + size of left subtree
 */
template <typename T>
size_t BSTree<T>::size( TreeNode<T>* localRoot ) const {
    if ( !localRoot )
        return 0;
    else
        return 1 + size(localRoot->left) + size(localRoot->right);
}

/**
 Pre-order traversal
 */
template <typename T>
void BSTree<T>::pre_order( TreeNode<T>* localRoot , ostream& out ) const {
    if ( localRoot ){
        out << localRoot->data << " ";
        pre_order(localRoot->left,out);
        pre_order(localRoot->right,out);
    }
    return;
}

/**
 In-order traversal
 */
template <typename T>
void BSTree<T>::in_order( TreeNode<T>* localRoot , ostream& out ) const {
    if ( localRoot ){
        in_order(localRoot->left,out);
        out << localRoot->data << " ";
        in_order(localRoot->right,out);
    }
    return;
}

/**
 Post-order traversal
 */
template <typename T>
void BSTree<T>::post_order( TreeNode<T>* localRoot , ostream& out ) const {
    if ( localRoot ){
        post_order(localRoot->left,out);
        post_order(localRoot->right,out);
        out << localRoot->data << " ";
    }
    return;
}

/**
 To deep_copy:
 - Pre-order traverse sourceTree and isert nodes into 'this'
 */
template <typename T>
void BSTree<T>::deep_copy( TreeNode<T>* nodeInSourceTree ){
    if ( nodeInSourceTree ){
        insert( nodeInSourceTree->data );
        deep_copy( nodeInSourceTree->left );
        deep_copy( nodeInSourceTree->right );
    }
    return;
}

/**
 THIS IS THE PLACE WHERE YOU SHOULD PLACE YOUT CODE
 */

template <typename T>
bool BSTree<T>::operator==( const BSTree<T>& param1 ) const
{
    
    if (this->height() != param1.height())
    {
        
    return false;
        
    }
    
    vector<T> first_tree, second_tree;
    
    to_vector(root, first_tree);
    
    to_vector(param1.root, second_tree);
    
    for (int i = 0 ; i < first_tree.size(); i ++)
    {
        
        if (first_tree[i] != second_tree[i])
        {
            return false;
        }
    }
    
    return true;
    
}


/***
 
 Is there a way to write a == program without implementing vectors AND using a passed-by-reference BST as parameters?
 
 ****/



 
template <typename T>
void BSTree<T>::to_vector( TreeNode<T>* param1 , vector<T>& param2 ) const {
    

    if(param1 != NULL)
    {
        param2.push_back(param1->data);
        
        to_vector(param1->left,param2);
        
        to_vector(param1->right, param2);
    }
    return;
    
}


template <typename T>
ostream& operator<<( ostream& param1 , const BSTree<T>& param2 ) {
    
   
    vector<T> tree;
    
    param2.to_vector(param2.get_root(), tree);
    
    for (int i = 0; i < tree.size(); i++)
    {
        param1 << tree[i] << " ";
    }
    return param1;
}

#endif