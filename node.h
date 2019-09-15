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

template<class T1,class T2> struct Node {
    T1 key;
    T2 value;
    
    Node* top; 
    Node* left; 
    Node* right;
    
    bool isBlackNode;
    
    explicit Node(const T1& keyy, const T2& valuee,Node* t, Node* l, Node* r, bool isBlackNodee = true)
    : key{keyy}, value{valuee},top{t}, left{l}, right{r}, isBlackNode{isBlackNodee}
    {
    }
};

#endif	/* NODE_H */

