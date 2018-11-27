/**
 May 28, 2015.
 Ricardo Salazar
 
 A driver for our homemade Binary Search Tree class
 


#include "bst.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using std::cout;
using std::endl;
using std::vector;

// shuffles numbers from 1 to n
void shuffleVector( vector<int>& );

/**
 Shuffles a vector with n entries.
 The algorithm:
 - For every index from 1 to n
 Generate random index r between 1 and n
	Exchange elements v[i] and v[r].
 */

/*
void shuffleVector( vector<int>& v ){
    for ( int i=0 ; i < v.size() ; i++ ){
        int j = rand() % v.size() ; // <-- New random position
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}


/**
 Main routine
 */

/*

int main(){
    const int FORREST_SIZE = 3;
    const int MAX_NODES = 10;
    
    long int startingTime = static_cast<long int>( time( NULL ) );
    srand( startingTime );
    
    // A vector of trees!!! ( a forrest )
    vector< BSTree<int> > forrest;
    cout << "The forrest will be populated by turning the following\n"
    << "sequences of random numbers into Binary Search Trees:" << endl;
    for ( int k = 0 ; k < FORREST_SIZE ; k ++ ) {
        
        vector<int> v(MAX_NODES);
        
        // populate the vector with numbers from 1 to MAX_NODES
        for (int i=0 ; i < v.size() ; i ++ )
            v[i] = i+1;
        
        // shuffle the vector
        shuffleVector( v );
        
        // Generate a BST with the elements of v
        BSTree<int> tree;
        for (int i=0 ; i < v.size() ; i ++ ){
            cout << v[i] << " ";
            tree.insert(v[i]);
        }
        cout << endl;
        
        // Add tree to forrest
        forrest.push_back(tree);
    }
    cout << endl;
    
    // Display statistics: heights of the trees
    for ( int i = 0 ; i < forrest.size() ; i++ ){
        cout << "Tree " << i+1 << " has height: "
        << forrest[i].height() << endl;
    }
    
    // Display first tree using operator<<
    cout << "\nThree 1 as a vector..." << endl;
    cout << forrest[0] ;
    
    
    // Testing operator !=
    if ( forrest[0] != forrest[1] )
        cout << "Trees 1 and 2 are not equal." << endl;
    
    // Convert first tree into a vector. Needed to test == below
    vector<int> v;
    forrest[0].to_vector(v);
    
    // Reconsutruct copy of first tree from its vector representation
    BSTree<int> phoenix_tree; // <-- back to life from its ashes...
    for ( int i = 0 ; i < v.size() ; i++ )
        phoenix_tree.insert(v[i]);
    
    // Testing operator ==
    if ( forrest[0] == phoenix_tree )
        cout << "1st tree equals its reconstruction." << endl;
    
    // Some statistics about the running time
    cout << "\nProgram ran in: "
    << static_cast<long int>( time( NULL ) ) - startingTime
    << " seconds" << endl ;
    
    return 0;
}

*/