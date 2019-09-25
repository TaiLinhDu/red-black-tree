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
    
    /*
    rbt1.insertNode( new Node<int,int> {10,0});
    rbt1.insertNode( new Node<int,int> {20,0});
    rbt1.insertNode( new Node<int,int> {30,0});
    rbt1.insertNode( new Node<int,int> {15,0});
    rbt1.insertNode( new Node<int,int> {5,0});
    rbt1.insertNode( new Node<int,int> {25,0});
    rbt1.insertNode( new Node<int,int> {26,0});
     * */
    
     rbt1.insertNode( new Node<int,int> {30,0});
      rbt1.insertNode( new Node<int,int> {20,0});
       rbt1.insertNode( new Node<int,int> {40,0});
        rbt1.insertNode( new Node<int,int> {50,0});
    rbt1.level_order(rbt1.getRoot());
    
    
    bool removeNode = rbt1.removeNode(rbt1.findByKey(20,rbt1.getRoot()));
    
    rbt1.level_order(rbt1.getRoot());

    

    
    return 0;
}

