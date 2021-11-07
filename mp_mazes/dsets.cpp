/* Your code here! */
/**
 * @file dsets.cpp
 * Implementation of a heap class.
 */

#include "dsets.h" 

void DisjointSets::addelements(int num){
    /** TODO */
    for (int i=0; i<num; i++){
        elemSet.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    /** TODO */
    if (elemSet[elem] < 0){return elem;}
    else {return find(elemSet[elem]);}
}

void DisjointSets::setunion(int a, int b){
    /** TODO */
    int A = find(a);
    int B = find(b);
    int newSize = elemSet[A] + elemSet[B];

    if (A == B){
        return;
    }else if (A < B){
        elemSet[B] = A;
        elemSet[A] = newSize;
    }else {
        elemSet[A] = B;
        elemSet[B] = newSize;
    }
}	

int DisjointSets::size(int elem){
    /** TODO */
    int root = find(elemSet[elem]);
    return (-1 * elemSet[root]);
}

