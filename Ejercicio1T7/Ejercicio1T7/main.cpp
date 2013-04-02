//
//  main.cpp
//  Ejercicio1T7
//
//  Created by Dani on 02/04/13.
//  Copyright (c) 2013 EDA. All rights reserved.
//

#include <iostream>
#include "ArbinConCopias.h"

int main(int argc, const char * argv[]) {

    Arbin<int> a;
    
    for (int i = 0; i < 10; i++) {
        Arbin<int> b(NULL, i+1, NULL);
        Arbin<int> c(NULL, i+2, NULL);
        
        a = construyeYVacia<int>(b, i, c);
    }
    
    return 0;
}

