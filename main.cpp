/* 
 * File:   main.cpp
 * Author: dani
 *
 * Created on 2 de abril de 2013, 20:39
 */

#include <cstdlib>
#include "ArbinConCopias.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Arbin<int> a();
    
    for ( int i = 0; i < 10; i++) {
        Arbin<int> b(NULL, i+1, NULL);
        Arbin<int> c(NULL, i+2, NULL);
        
        a.construyeYVacia(b, i, c);
    }
    
    return 0;
}

