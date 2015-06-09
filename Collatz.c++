// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

//make cache size 1 million
int* cache_array = new int[1000000];


using namespace std;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    // <your code>

    cache_array[0] = 0;

    int start = i;
    int end = j+1;

    //iterates from i to j
    for(start; start < end; start++){

        int cycle = 0;

        while(start != 1){

            //even
            if((start & 1) == 0){
                start = start/2;
            }

            //odd
            else{
                start = (start * 3) + 1;
            }

            //update cycle counter
            cycle++;
        }

        cache_array[start] = cycle;
    }


    //cache array should have the specified cycle values at that position
    //search
    
    int ret_value = cache_array[i];
    for(i; i < end; i++){

        int temp = cache_array[i];

        if(temp > ret_value){
            ret_value = temp;
        }
    }
    
    return ret_value;}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}