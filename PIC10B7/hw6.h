
/* **********************************************************************
 
 File: hw6.h
 
 Author: Noam Grebler Farras
 
 UID: 304343111
 
 Date: March 13, 2016
 
 
 
 Program that creates 10000 binnary trees with n nodes and then calculates the average height for those trees.
 
 ********************************************************************** */


#ifndef hw6_h
#define hw6_h
#include "bst.h"
#include <iostream>





bool in_forest (vector<vector<int>> forest, vector<int> vec)
{
    for (int i = 0; i < forest.size(); i++)
    {
        if (forest[i] == vec)
            return true;
    }
    return false;
}


void shuffleVector( vector<int>& vec){
    for ( int i=0 ; i < vec.size() ; i++ ){
        int j = rand() % vec.size() ; // <-- New random position
        int temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
    }
}

double compute_average_height(int h)
{
    if(h<=0)
    {
        return 0;
    }
    
    vector<vector<int>> forest;
    double height=0.0;
    vector<int> vect;
    BSTree<int> t;
    
    for (int i = 0; i < 10000; i++)
    {
     
        for (int i = 0; i < h; i++)
        {
            vect.push_back(i+1);
        }
        
        
        shuffleVector(vect);
        
  
        if (!in_forest(forest,vect))
        {
            forest.push_back(vect);
            for (int i = 0; i < vect.size(); i++)
                t.insert(vect[i]);
            height+=t.height();
        }
        
        
        while (vect.size() != 0)
            vect.pop_back();
        while (t.get_root() != NULL)
            t.erase(t.get_root());
        
    }
    
    double av_height = height/(double)forest.size();
    return av_height;

    
}



#endif
