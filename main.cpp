/* 
 * File:   main.cpp
 * Author: tai-linh.du
 *
 * Created on 8. September 2019, 15:40
 */

#include <cstdlib>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <cstdlib>

#include "red-black-tree.h"
#include "telefon-book.h"
#include "read-telefon-book-csv-file.h"

using namespace std;

void timeToInsertALargeNumberOfNode(ReadTelefonBookCSVFile r, RedBlackTree<int, TelefonBook> &rbt, int numberOfNote);
void timeToFindRadomNode( RedBlackTree<int,TelefonBook> &rbt, int numberOfRandomNote, int maxKey);
void timeToInsertNewNumberOfNode(ReadTelefonBookCSVFile r, RedBlackTree<int,TelefonBook> &rbt, int numberOfNote, int keyBegin );
void timeToDeleteRandomNote( RedBlackTree<int,TelefonBook> &rbt, int numberOfNote, int maxKey);


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
    
    /*
     rbt1.insertNode( new Node<int,int> {30,0});
     rbt1.insertNode( new Node<int,int> {20,0});
     rbt1.insertNode( new Node<int,int> {40,0});
    rbt1.insertNode( new Node<int,int> {35,0});
    rbt1.insertNode( new Node<int,int> {50,0});
    rbt1.insertNode( new Node<int,int> {10,0});
    rbt1.insertNode( new Node<int,int> {2,0});
    rbt1.insertNode( new Node<int,int> {3,0});
    rbt1.insertNode( new Node<int,int> {4,0}); 
    rbt1.insertNode( new Node<int,int> {5,0});
    rbt1.insertNode( new Node<int,int> {6,0});
    rbt1.insertNode( new Node<int,int> {7,0});
    rbt1.insertNode( new Node<int,int> {8,0});
    rbt1.insertNode( new Node<int,int> {9,0});
    rbt1.insertNode( new Node<int,int> {11,0}); 
    rbt1.insertNode( new Node<int,int> {12,0});
              
         
    rbt1.level_order(rbt1.getRoot());
    
    
    rbt1.removeNode(rbt1.findByKey(1,rbt1.getRoot())); 
    rbt1.removeNode(rbt1.findByKey(30,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(20,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(40,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(35,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(50,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(2,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(3,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(4,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(5,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(6,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(7,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(8,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(9,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(10,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(11,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(12,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(13,rbt1.getRoot()));
    
    
    
    
//     rbt1.removeNode(rbt1.findByKey(40,rbt1.getRoot()));
//    rbt1.removeNode(rbt1.findByKey(30,rbt1.getRoot()));
    
    rbt1.level_order(rbt1.getRoot());
    
     

     rbt1.insertNode( new Node<int,int> {20,0});
     rbt1.insertNode( new Node<int,int> {10,0});

    rbt1.level_order(rbt1.getRoot());
    
    
    rbt1.removeNode(rbt1.findByKey(20,rbt1.getRoot())); 
     rbt1.removeNode(rbt1.findByKey(35,rbt1.getRoot()));
    rbt1.removeNode(rbt1.findByKey(10,rbt1.getRoot()));
        rbt1.removeNode(rbt1.findByKey(40,rbt1.getRoot()));
         
          rbt1.removeNode(rbt1.findByKey(30,rbt1.getRoot()));
           //rbt1.removeNode(rbt1.findByKey(50,rbt1.getRoot()));
         
    
    rbt1.level_order(rbt1.getRoot());
    
    */
    /*----------------------------- COUNT TIME INSERT, FIND, DELETE ---------------------------------*/
    
    
    ReadTelefonBookCSVFile r;
    
    r.readFileAndInsertIntoTelefonBook("au-500.csv");
    
    cout << "Number of readed telefonbook: " << r.telefonbook.size() << endl;
    
    //r.showTelefonBook();
    
    
    
    RedBlackTree<int,TelefonBook> rbt {};
    
    // 100
    int numberOfNode;
    cout << "please enter the number of Node to test: ";
    cin >> numberOfNode;
    
    timeToInsertALargeNumberOfNode(r,rbt,numberOfNode);
    timeToFindRadomNode(rbt,100,numberOfNode);
    timeToDeleteRandomNote(rbt,100,numberOfNode);
    timeToInsertNewNumberOfNode(r,rbt,100,numberOfNode);
    

    
   
    return 0;
}

void timeToInsertALargeNumberOfNode(ReadTelefonBookCSVFile r, RedBlackTree<int,TelefonBook> &rbt, int numberOfNote) {
    
    auto begin = chrono::steady_clock::now();    

    for( int i = 0; i < numberOfNote; i++){
        rbt.insertNode(new Node<int,TelefonBook> {i+1, r.telefonbook[i]});
    }

    auto end = chrono::steady_clock::now();    
    auto dur = end - begin;
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
    cout << "Time to insert " << numberOfNote << " Node into RBT: " << us << endl;
}

void timeToFindRadomNode( RedBlackTree<int,TelefonBook> &rbt, int numberOfRandomNote, int maxKey) {
    
    auto begin2 = chrono::steady_clock::now();    

    for( int i = 0; i < numberOfRandomNote; i++){
        rbt.findByKey(rand() % maxKey + 1, rbt.getRoot());
        //rbt100.insertNode(new Node<int,TelefonBook> {i+1, r.telefonbook[i]});
    }
    //rbt100.level_order(rbt100.getRoot());
    auto end2 = chrono::steady_clock::now();    
    auto dur2 = end2 - begin2;
    auto us2 = std::chrono::duration_cast<std::chrono::microseconds>(dur2).count();
    cout << "Time to find " << numberOfRandomNote << " random Node into RBT: " << us2 << endl;
    
}

void timeToInsertNewNumberOfNode(ReadTelefonBookCSVFile r, RedBlackTree<int,TelefonBook> &rbt, int numberOfNote, int keyBegin ){
    
    auto begin3 = chrono::steady_clock::now();    

    for( int i = keyBegin; i < (keyBegin + numberOfNote); i++){
        rbt.insertNode(new Node<int,TelefonBook> {i+1, r.telefonbook[i]});
    }
    //rbt100.level_order(rbt100.getRoot());
    auto end3 = chrono::steady_clock::now();    
    auto dur3 = end3 - begin3;
    auto us3 = std::chrono::duration_cast<std::chrono::microseconds>(dur3).count();
    cout << "Time to insert "<< numberOfNote <<" new Node into this RBT: " << us3 << endl;
    
    
}

void timeToDeleteRandomNote( RedBlackTree<int,TelefonBook> &rbt, int numberOfNote, int maxKey){
    auto begin4 = chrono::steady_clock::now();    

    for( int i = 0; i < numberOfNote; i++){
        rbt.removeNode(rbt.findByKey(rand() % maxKey + 1, rbt.getRoot()));
    }
    //rbt100.level_order(rbt100.getRoot());
    auto end4 = chrono::steady_clock::now();    
    auto dur4 = end4 - begin4;
    auto us4 = std::chrono::duration_cast<std::chrono::microseconds>(dur4).count();
    cout << "Time to delete "<< numberOfNote <<" Node into RBT: " << us4 << endl;
}
