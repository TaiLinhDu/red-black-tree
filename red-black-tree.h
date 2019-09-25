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
        Node<T1,T2>* find(const T1& key, Node<T1,T2>* n) ; 
        
        /* insert into the tree by key without care of color and balancing */
        Node<T1,T2>* insertNodeWithoutCareAboutColor( Node<T1,T2>* newNode);
        
        /**
         * remove Node as Binar Searchtree
         * @param node
         * @return 
         */
        bool removeNodeWithoutCareAboutColor( Node<T1,T2>* node);
        
        /**
         * recolor or rotation after remove Node
         * @param parentNodeOfSelectedNote
         * @param isSelectedNodeOnTheLeft
         */
        void handleCasesWhenRemoveNode( 
                Node<T1,T2>* node,
                Node<T1,T2>* replacementNode,
                Node<T1,T2>* selectedXNode, //x
                Node<T1,T2>* siblingOfSelectedXNode, // w
                Node<T1,T2>* parentNodeOfSelectedNote,
                bool isSelectedNodeOnTheLeft);
        
        void handle4CaseWhenRemoveNode( 
            Node<T1,T2>* node,
            Node<T1,T2>* replacementNode,
            Node<T1,T2>* selectedXNode,
            Node<T1,T2>* siblingOfSelectedXNode,
            Node<T1,T2>* parentNodeOfSelectedNote,
            bool isSelectedNodeOnTheLeft);
        
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
        
        Node<T1,T2>* findByKey(const T1& key, Node<T1,T2>* n );
        // Node<T1,T2>* findByValue(T1 key);
        
        void insertNode(Node<T1,T2>* node);
        
        bool removeNode(Node<T1,T2>* node);
        
        void level_order(Node<T1,T2>* n);
        
        Node<T1,T2>* getRoot (){return root;}
};


template<class T1, class T2>
Node<T1,T2>* RedBlackTree<T1,T2>::findToInsert( T1& key, Node<T1,T2>* n) {
    
    //at begin, node n ist root
    if (key < n->key) { // left site
        
        if (n -> left != nullptr){ //wenn ist Knode nicht blatt bei left
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
RedBlackTree<T1,T2>::insertNodeWithoutCareAboutColor
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
                Node<T1,T2>* parentNodeOfSelectedNote = findToInsert(newNode->key, root);
                if (newNode->key < parentNodeOfSelectedNote->key){
                    parentNodeOfSelectedNote->left = newNode; 
                    newNode->parent = parentNodeOfSelectedNote;
                    return newNode;
                }
                else {
                    parentNodeOfSelectedNote -> right = newNode; 
                    newNode->parent = parentNodeOfSelectedNote;
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
    this->insertNodeWithoutCareAboutColor(node);
    
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
                    leftLeftCase(node->left);
                    
                } else if ( node->parent->isOnRight() && node->isOnRight()){
                    
                    rightRightCase(node);
                    
                } else if (node->parent->isOnRight() && node->isOnLeft()){
                    
                     // right left case
                    rotateR(node->parent);
                    rightRightCase(node->right);
                }
                break;
            } else break; 
        } else break;
    }
    
}

template<class T1,class T2>
Node<T1,T2>* RedBlackTree<T1,T2>::findByKey(const T1& key, Node<T1,T2>* n )  {
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
    if (parent != nullptr){
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
    n->parent = newW;
    
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
    cout << "---------------------------------" << endl;
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
    
    cout << "---------------------------------" << endl;
}
template<class T1,class T2>
bool RedBlackTree<T1,T2>::removeNodeWithoutCareAboutColor(Node<T1,T2>* node){
    
    // source for this function: https://github.com/alenachang/red-black-deletion-steps/blob/master/RedBlackDeletionSteps.pdf
    Node<T1,T2>* replacementNode = nullptr;
    Node<T1,T2>* selectedXNode = nullptr;
    Node<T1,T2>* siblingOfSelectedXNode = nullptr;
    Node<T1,T2>* parentNodeOfSelectedNote = nullptr;
    bool isSelectedNodeOnTheLeft = false;
    
    //---------------- deleted node does not have child ------------------------
    if (node->left == nullptr && node->right == nullptr){
        if(node->parent != nullptr){
            if (node->isOnLeft()){
                (node->parent)->left = nullptr;
                isSelectedNodeOnTheLeft = true;
                siblingOfSelectedXNode = node->parent->right;
            } else {
                (node->parent)->right = nullptr;
                siblingOfSelectedXNode = node->parent->left;
            }
            
            // for inital step
            // replacementNode is nullptr
            parentNodeOfSelectedNote = node->parent;
            
            
        } else 
            root = nullptr;
        

        
    
    //------------------deleted node have one child -------------------------
    } else if ((node->left == nullptr && node->right != nullptr) ||
            (node->left != nullptr && node->right == nullptr)){
        
        if (node->left != nullptr){
            
            // set x
            replacementNode = node->left;
            
            //also x for 4 case
            selectedXNode = node->left;
            // for handle case
            isSelectedNodeOnTheLeft = true;
            
            if (node->parent != nullptr){
                
                if (node->isOnLeft()){
                    
                    (node->parent)->left = node->left;
                    (node->left)->parent = node->parent;


                } else { //node is on the right site
                    (node->parent)->right = node->left;
                    (node->left)->parent = node->parent;
                }
            }else {
                root = node->left;
            }
            
        } else { // node->right != nullptr
            
            replacementNode = node->right;
            selectedXNode = node->right;
            
            if (node->parent != nullptr){ 
                if (node->isOnLeft()){
                    (node->parent)->left = node->right;
                    (node->right)->parent = node->parent;

                } else { //node is on the right site
                    (node->parent)->right = node->right;
                    (node->right)->parent = node->parent;
                }
            } else {
                root = node->right;
            }
        }
        
        // for handle case
        parentNodeOfSelectedNote = selectedXNode->parent;
        
    //-------------------deleted node have two children---------------------------
    } else { // node have two children
        
        Node<T1,T2>* newNode = node->minKeyNode(node->right);
            
        //xmin key Node have no child
        if (newNode->right == nullptr){
 
            if(newNode != node->right){
                newNode->right = node->right;
                newNode->parent->left = nullptr;
            
            } else 
                newNode->right = nullptr;
            
        // min key Node have one child
        } else { //newNode->right != nullptr
            
            if (newNode != node->right){
                // newNode has right child
                (newNode->parent)->left = newNode->right;
                (newNode->right)->parent = newNode->parent;
                
                newNode->right = node->right;
            } else { // newNode is right child of node
                //nothing happend
            }
        }
        
        newNode->left = node->left;

        newNode->parent = node->parent;
        if(node->parent == nullptr){
            root = newNode;
        } else {
            if (node->isOnLeft()){
                (node->parent)->left = newNode;
                 isSelectedNodeOnTheLeft = true;
            } else
                (node->parent)->right = newNode;
        }
        
        replacementNode = newNode;
        selectedXNode = newNode->right;
        siblingOfSelectedXNode = newNode->left;
        parentNodeOfSelectedNote = selectedXNode->parent;
    }
            
    handleCasesWhenRemoveNode(node,replacementNode,selectedXNode,siblingOfSelectedXNode,parentNodeOfSelectedNote,isSelectedNodeOnTheLeft);
        
    //delete node
    delete node;
    node = nullptr;
    return true;
}

template<class T1,class T2>
bool RedBlackTree<T1,T2>::removeNode(Node<T1,T2>* node){
    
    removeNodeWithoutCareAboutColor(node);
    
    
}

template<class T1,class T2>
void RedBlackTree<T1,T2>::handleCasesWhenRemoveNode( 
                Node<T1,T2>* node,
                Node<T1,T2>* replacementNode,
                Node<T1,T2>* selectedXNode,
                Node<T1,T2>* siblingOfSelectedXNode,
                Node<T1,T2>* parentNodeOfSelectedNote,
                bool isSelectedNodeOnTheLeft){
    
    if (node->nodeColor == RED && 
            (replacementNode != nullptr && replacementNode->nodeColor == BLACK)){
        replacementNode->nodeColor = RED;
        handle4CaseWhenRemoveNode(node, replacementNode, selectedXNode,
                siblingOfSelectedXNode, parentNodeOfSelectedNote, isSelectedNodeOnTheLeft);
    
    } else if (node->nodeColor == BLACK && 
         (replacementNode != nullptr && replacementNode->nodeColor == RED)){
        replacementNode->nodeColor = BLACK;
    
    } else if (node->nodeColor == BLACK && 
         ( replacementNode == nullptr || (replacementNode != nullptr && replacementNode->nodeColor == BLACK))){
        handle4CaseWhenRemoveNode(node, replacementNode, selectedXNode,
                siblingOfSelectedXNode, parentNodeOfSelectedNote, isSelectedNodeOnTheLeft);
    }
}


template<class T1,class T2>
void RedBlackTree<T1,T2>::handle4CaseWhenRemoveNode( 
    Node<T1,T2>* node,
    Node<T1,T2>* replacementNode,
    Node<T1,T2>* selectedXNode,
    Node<T1,T2>* siblingOfSelectedXNode,
    Node<T1,T2>* parentNodeOfSelectedNote,
    bool isSelectedNodeOnTheLeft){
    
    // Case 0
    if (selectedXNode != nullptr && selectedXNode->nodeColor == RED){
        selectedXNode->nodeColor = BLACK;
        return;
        
    // CASE 1
    } else if ((selectedXNode == nullptr || 
            (selectedXNode != nullptr && selectedXNode->nodeColor == BLACK))
            && (siblingOfSelectedXNode != nullptr && siblingOfSelectedXNode->nodeColor == RED)){
        
        siblingOfSelectedXNode->nodeColor = BLACK;
        parentNodeOfSelectedNote->nodeColor = RED;
        
        if (selectedXNode->isOnLeft()){
            
            rotateL(parentNodeOfSelectedNote);
            siblingOfSelectedXNode = parentNodeOfSelectedNote->right;
                    
        } else {
            rotateR(parentNodeOfSelectedNote);
            siblingOfSelectedXNode = parentNodeOfSelectedNote->left;
        }
    }   

    //CASE 2
    if (
            (selectedXNode == nullptr || 
            (selectedXNode != nullptr && selectedXNode->nodeColor == BLACK))
            &&
            (siblingOfSelectedXNode != nullptr && siblingOfSelectedXNode->nodeColor == BLACK)
            &&
            (siblingOfSelectedXNode->left == nullptr 
            || (siblingOfSelectedXNode->left != nullptr && siblingOfSelectedXNode->left->nodeColor == BLACK)
            )
            && 
            (siblingOfSelectedXNode->right == nullptr 
            || (siblingOfSelectedXNode->right != nullptr && siblingOfSelectedXNode->right->nodeColor == BLACK)) 
            ) {
        siblingOfSelectedXNode->nodeColor = RED;
        selectedXNode = parentNodeOfSelectedNote;

        if (selectedXNode->nodeColor == RED){
            selectedXNode->nodeColor = BLACK;
        } else {
            // set new sibling (w))
            if(selectedXNode->isOnLeft()){
                siblingOfSelectedXNode = parentNodeOfSelectedNote->right;
            } else {
                    siblingOfSelectedXNode = parentNodeOfSelectedNote->left;
            }
            handle4CaseWhenRemoveNode(node,replacementNode,selectedXNode,siblingOfSelectedXNode,parentNodeOfSelectedNote,isSelectedNodeOnTheLeft);
        }
        
        return;
    }

    //CASE 3
    if ( 
            (selectedXNode == nullptr || 
            (selectedXNode != nullptr && selectedXNode->nodeColor == BLACK))
            &&
            (siblingOfSelectedXNode != nullptr && siblingOfSelectedXNode->nodeColor == BLACK) 
            && isSelectedNodeOnTheLeft
            &&( siblingOfSelectedXNode->left != nullptr && siblingOfSelectedXNode->left->nodeColor == RED )
            && (siblingOfSelectedXNode->right == nullptr || (siblingOfSelectedXNode->right != nullptr && siblingOfSelectedXNode->right->nodeColor == BLACK))
        ){
        siblingOfSelectedXNode->left->nodeColor = BLACK;

        siblingOfSelectedXNode->nodeColor = RED;
        rotateR(siblingOfSelectedXNode);
        siblingOfSelectedXNode = parentNodeOfSelectedNote->right;

    } else if (
        (siblingOfSelectedXNode != nullptr && siblingOfSelectedXNode->nodeColor == BLACK) 
        && !isSelectedNodeOnTheLeft 
        && (siblingOfSelectedXNode->left == nullptr || (siblingOfSelectedXNode->left != nullptr && siblingOfSelectedXNode->left->nodeColor == BLACK))
        &&( siblingOfSelectedXNode->right != nullptr && siblingOfSelectedXNode->right->nodeColor == RED )
            
        ){
        siblingOfSelectedXNode->right->nodeColor = BLACK;

        siblingOfSelectedXNode->nodeColor = RED;
        rotateL(siblingOfSelectedXNode);
        siblingOfSelectedXNode = parentNodeOfSelectedNote->left;

    }
    
    //CASE 4
    if ( 
            (selectedXNode == nullptr || 
            (selectedXNode != nullptr && selectedXNode->nodeColor == BLACK))
            &&
            ((siblingOfSelectedXNode != nullptr && siblingOfSelectedXNode->nodeColor == BLACK) )
            && (
            (isSelectedNodeOnTheLeft && siblingOfSelectedXNode->right->nodeColor == RED) 
            || ( !isSelectedNodeOnTheLeft && siblingOfSelectedXNode->left->nodeColor == RED) 
               ) 
         ){

        siblingOfSelectedXNode->nodeColor = parentNodeOfSelectedNote->nodeColor;
        parentNodeOfSelectedNote->nodeColor = BLACK;

        if (isSelectedNodeOnTheLeft){
            siblingOfSelectedXNode->right->nodeColor = BLACK;
            rotateL(parentNodeOfSelectedNote);
        } else {
            siblingOfSelectedXNode->left->nodeColor = BLACK;
            rotateR(parentNodeOfSelectedNote);
        } 
    }
}
        

#endif	/* RED_BLACK_TREE_H */

