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
#include "node.h"
#include <queue>

using namespace std;

template<class T1,class T2> class RedBlackTree {
    
    private:
        Node<T1,T2>* root;
        int height;
        int blackHeight;
        
        /* find parent of the inserted Node*/
        Node<T1,T2>* findToInsert( T1& key, Node<T1,T2>* n);
        
        /*find a node by key*/
        Node<T1,T2>* find( T1& key, Node<T1,T2>* n) ; 
        
        /* insert into the tree by key without care of color and balancing */
        Node<T1,T2>* insertWithoutCareAboutColor( Node<T1,T2>* newNode);
        
        Node<T1,T2>* rotateR(Node<T1,T2>* node);
        
        Node<T1,T2>* rotateL(Node<T1,T2>* node);
        
        /* update color and rotation for the left left case of insert function
         * the parent is on the left site of grandparent
         * and the node is on the left site of parent */
        void leftLeftCase(Node<T1,T2>* n);
        
        /* mirror of left left case*/
        void rightRightCase(Node<T1,T2>* n);
        

    public:
        RedBlackTree< T1, T2>(){
            root = nullptr;
            blackHeight = 0;
            height = 0;
        }
        
        void rotation(Node<T1,T2>* node);
        void recoloring(Node<T1,T2>* node);
        
        Node<T1,T2>* findByKey( T1& key, Node<T1,T2>* n );
        // Node<T1,T2>* findByValue(T1 key);
        
        void insertNode(Node<T1,T2>* node);
        
        Node<T1,T2>* removeNode(Node<T1,T2>* node);
        
        void level_order(Node<T1,T2>* n);
        
        Node<T1,T2>* getRoot (){return root;}
};


template<class T1, class T2>
Node<T1,T2>* RedBlackTree<T1,T2>::findToInsert( T1& key, Node<T1,T2>* n) {
    
    //at begin, node n ist root
    if (key < n->key) { // left site
        
        if (n -> left != nullptr){ //wenn ist Knote nicht blatt bei left
            return findToInsert(key, n->left);

        } else return n; //wenn n -> left == nullptr 
    } else {// if key > n -> key. ..Right
        if (n->right != nullptr){
            return findToInsert(key, n->right);
        } else return n; //wenn n -> right == nullptr
    }
}

template<class T1,class T2>
Node<T1,T2>* 
RedBlackTree<T1,T2>::insertWithoutCareAboutColor
( Node<T1,T2>* newNode) { //const T1& key
    try{
        Node<T1,T2>* n{ findByKey( newNode->key, root) };

        if (n != nullptr){
            error("this new node key is already exist");
        }  
        else {
            if (root == nullptr) { 
                root = newNode;
                return root;
            } else { // if root is not null
                Node<T1,T2>* parentNode = findToInsert(newNode->key, root);
                if (newNode->key < parentNode->key){
                    parentNode->left = newNode; 
                    newNode->parent = parentNode;
                    return newNode;
                }
                else {
                    parentNode -> right = newNode; 
                    newNode->parent = parentNode;
                    return newNode;
                }
            }
        }
    } catch (const exception& e){
        cout << e.what();
    }
}

template<class T1, class T2>
void RedBlackTree<T1,T2>::insertNode(Node<T1,T2>* node){
    this->insertWithoutCareAboutColor(node);
    
    while(true){
        
        if (node != nullptr && node->parent == nullptr){
            this->root = node;
            node->nodeColor = BLACK;
            break;
        } else if (node != nullptr && node->parent->nodeColor == RED){//parent RED
            
            //if uncle is red
            if (node->findUncle() != nullptr && node->findUncle()->nodeColor == RED){
                node->findUncle()->nodeColor = BLACK;
                node->parent->nodeColor = BLACK;
                node->parent->parent->nodeColor = RED;
                node = node->parent->parent;
                continue;
            } else if(node->findUncle() != nullptr && node->findUncle()->nodeColor == BLACK){
                
                //left left case
                if ( node->parent->isOnLeft() && node->isOnLeft()){
                    leftLeftCase(node);
                    
                } else if (node->parent->isOnLeft() && node->isOnRight() ){ 
                    // left right case
                    rotateL(node->parent);
                    leftLeftCase(node);
                    
                } else if ( node->parent->isOnRight() && node->isOnRight()){
                    
                    rightRightCase(node);
                } else if (node->parent->isOnRight() && node->isOnLeft()){
                    
                     // right left case
                    rotateR(node->parent);
                    rightRightCase(node);
                }
            } 
        } else break;
    }

    
}

template<class T1, class T2>
Node<T1,T2>* RedBlackTree<T1,T2>::removeNode(Node<T1,T2>* node){
    
}

template<class T1,class T2>
Node<T1,T2>* RedBlackTree<T1,T2>::findByKey( T1& key, Node<T1,T2>* n )  {
    if (n == nullptr) return nullptr;
    if (n->key == key) return n; // Vergleich mit key
      
    if (key < n->key && n -> left != nullptr) { // if key < n -> key. und n ist nicht blatt
        Node<T1,T2>* temp1 = findByKey(key, n->left);
        if (temp1 != nullptr) return temp1;
    }

    if (key > n->key && n -> right != nullptr) {// if key > n -> key. und n ist nicht blatt
        Node<T1,T2>* temp2 = findByKey(key, n->right);
        if (temp2 != nullptr) return temp2;
    }
    return nullptr;
}


template<class T1,class T2>
 Node<T1,T2>* RedBlackTree<T1,T2>::rotateR(Node<T1,T2>* n){ // wenn neuW < W
    Node<T1,T2>* parent = n->parent;
    
    Node<T1,T2>* newW = n -> left; // new root of undertree
    if(parent != nullptr){
        newW->parent = parent;
    } else {
        newW->parent = nullptr;
    }
    
    if(newW -> right != nullptr){
        n -> left = newW -> right; 
        (n -> left)->parent = n;
    } else {
        n->left = nullptr;
    }

    newW -> right = n; 
    n->parent = newW;
    
    
    //for top
    if (parent == nullptr){
        root = newW;
    } else {
        if(parent->key > newW->key) parent -> left = newW; 
        if(parent->key < newW->key) parent -> right = newW;
    }
    return newW;
}

template<class T1,class T2>
 Node<T1,T2>* RedBlackTree<T1,T2>:: rotateL(Node<T1,T2>* n){ 
    
    Node<T1,T2>* parent = n->parent;
    
    Node<T1,T2>* newW = n -> right;
    if(parent != nullptr){
        newW->parent = parent;
    } else {
        newW->parent = nullptr;
    }

    
    if (newW->left != nullptr){
        n -> right = newW -> left;
        (n -> right)->parent = n;
    } else {
        n->right = nullptr;
    }

    
    newW -> left = n;
    n->parent = newW->left;
    
    //for top
    if (parent == nullptr){
        root = newW;
    } else {
        if(parent->key > newW->key) parent -> left = newW; 
        if(parent->key< newW->key) parent -> right = newW;
    }
    return newW;
}

template<class T1,class T2>
void RedBlackTree<T1,T2>:: leftLeftCase(Node<T1,T2>* node){
    
    // swap color parent and grandparent
    COLOR temp = node->parent->nodeColor;
    node->parent->nodeColor = node->parent->parent->nodeColor;
    node->parent->parent->nodeColor = temp;

    // rotate right in node grandparent
    rotateR(node->parent->parent);
}

template<class T1,class T2>
void RedBlackTree<T1,T2>:: rightRightCase(Node<T1,T2>* node){
    
    // swap color parent and grandparent
    COLOR temp = node->parent->nodeColor;
    node->parent->nodeColor = node->parent->parent->nodeColor;
    node->parent->parent->nodeColor = temp;

    // rotate left in node grandparent
    rotateL(node->parent->parent);
}

template<class T1,class T2>
void RedBlackTree<T1,T2> ::level_order(Node<T1,T2>* n) {
    if (n == nullptr) return;
    queue<Node<T1,T2>*> q{}; //container First in first out
    q.push(n); //push in back
    while (!q.empty()) {
        n = q.front(); //die erste Wert in Container wird gespeichert fuer Besuch
        q.pop();
        cout << n -> key << "-" << (n->nodeColor == RED ? "RED" : "BLACK") << " "; // z.B. cout
        if (n->left != nullptr)
            q.push(n->left);
        if (n->right != nullptr)
            q.push(n->right);
    }
}


#endif	/* RED_BLACK_TREE_H */

