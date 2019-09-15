/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MYERROR_H.h
 * Author: linhdt1995
 *
 * Created on April 27, 2017, 5:24 AM
 */

#ifndef MYERROR_H_H
#define MYERROR_H_H

#include<stdexcept>
#include<string>
using std :: string;

inline void error (string s) {throw std:: runtime_error{s}; }
inline void error (string s1 , string s2) {error (s1 + s2);}



#endif /* MYERROR_H_H */

