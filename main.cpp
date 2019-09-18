/* 
 * File:   main.cpp
 * Author: tai-linh.du
 *
 * Created on 8. September 2019, 15:40
 */

#include <cstdlib>
#include <iostream>
#include "red-black-tree.h"
#include "telefon-book.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    RedBlackTree<int,int> rbt1 {};
    
    rbt1.insertNode( new Node<int,int> {10,0});
    rbt1.insertNode( new Node<int,int> {11,0});
    rbt1.insertNode( new Node<int,int> {12,0});
    rbt1.insertNode( new Node<int,int> {13,0});
    rbt1.insertNode( new Node<int,int> {14,0});
    rbt1.insertNode( new Node<int,int> {15,0});
    rbt1.insertNode( new Node<int,int> {16,0});
    rbt1.insertNode( new Node<int,int> {17,0});
    
    rbt1.level_order(rbt1.getRoot());
    
    return 0;
}

