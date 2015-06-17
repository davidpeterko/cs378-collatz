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

#define CACHE_SIZE 1000000

//Cache
#ifdef CACHE_SIZE
int cache_array[CACHE_SIZE];    
#endif

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
    assert(i > 0);
    assert(j > 0);

    //Swaps values if i j ranges are backwards
    if( i > j){
        int temp = i;   
        i = j;          
        j = temp;       
    }

    int end = j+1;

    /** FIND CYCLE LENGTH **/

    for(int start = i; start < end; start++){

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

        assert(cycle > 0);

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
    
    return ret_value;
}

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
