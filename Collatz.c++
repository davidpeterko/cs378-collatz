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
    //account for backwards ranges>?
    //account for 0 input?

    /** for j > i, doesnt work**/
    /*
    if( j > i){
        
        int temp = i;   //save previous value of i

        i = j;          // i becomes the higher j
        j = temp;       //j becomes temp which is the previous i that was overwrote
    }
    */

    cache_array[0] = 0;

    int end = j+1;

    //iterates from i to j
    for(int start = i; start < end; start++){

        //start cycle at 1 because count first
        int cycle = 1;
        int val = start;

        while(val > 1){

            //even
            if((val & 1) == 0){
                val = val/2;
            }

            //odd
            else{
                val = (val * 3) + 1;
            }

            //update cycle counter
            cycle++;
        }

        cache_array[start] = cycle;
    }


    /** SEARCH CACHE ARRAY FOR ALL SAVED VALUES **/
    
    int ret_value = cache_array[i];
    for(int begin = i; begin < end; begin++){

        int temp = cache_array[begin];

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