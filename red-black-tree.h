/* 
 * File:   red-black-tree.h
 * Author: tai-linh.du
 *
 * Created on 15. September 2019, 14:00
 * 
 * this file define structure of a red black tree
 */

#ifndef RED_BLACK_TREE_H
#define	RED_BLACK_TREE_H

#include "MYERROR_H.h"
#include<iostream>

using namespace std;

template<class T1,class T2> class RedBlackTree {
    
    private:
        Node* root;
        int height;
        int blackHeight;
    public:
        void rotation(Node* node);
        void recoloring(Node* node);
        
        Node* findByKey(T1 key);
        Node* findByValue(T1 key);
        
        void addNewNode(Node* node);
        
        Node* removeNode(Node* node);
        
};


#endif	/* RED_BLACK_TREE_H */

