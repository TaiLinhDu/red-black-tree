/* 
 * File:   node.h
 * Author: tai-linh.du
 *
 * Created on 15. September 2019, 14:17
 * 
 * this file finine structure of a node in red black tree
 */

#ifndef NODE_H
#define	NODE_H

enum COLOR { RED, BLACK }; 

template<class T1,class T2> struct Node {
    T1 key;
    T2 value;
    
    Node* parent; 
    Node* left; 
    Node* right;
    
    COLOR nodeColor = RED;
    
    explicit Node(T1 keyy,T2 valuee,COLOR color = RED)
    : key{keyy}, value{valuee}, nodeColor{color},parent{nullptr},left{nullptr},right{nullptr}
    {
    }
    
    explicit Node(const T1 keyy, const T2 valuee,Node* p , Node* l , Node* r , COLOR color = RED)
    : key{keyy}, value{valuee},parent{p}, left{l}, right{r}, nodeColor{color}
    {
    }
    
    Node<T1,T2>* findUncle(){
       
       if (parent == nullptr || parent->parent == nullptr){
           return nullptr; 
       }
         
       if (parent->isOnLeft()){
           if (parent->parent->right == nullptr){
              return new Node( T1{}, T2{},BLACK); 
           }
            return parent->parent->right; 
       } else {
            if (parent->parent->left == nullptr){
              return new Node( T1{}, T2{},BLACK); 
           }
            return parent->parent->left;
       }
       
 
    }
    
    // check if node is left child of parent 
    bool isOnLeft() { return this == parent->left; } 
    
    // check if node is left child of parent 
    bool isOnRight() { return this == parent->right; } 
};

#endif	/* NODE_H */

