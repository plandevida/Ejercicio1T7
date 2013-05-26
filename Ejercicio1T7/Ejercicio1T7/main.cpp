//
//  main.cpp
//  Ejercicio1T7
//
//  Created by Dani on 02/04/13.
//  Copyright (c) 2013 EDA. All rights reserved.
//

#include <iostream>
#include "ArbinConCopias.h"

using namespace std;

int main(int argc, const char * argv[]) {

    Arbin<int> a(Arbin<int>(Arbin<int>(), 2, Arbin<int>(Arbin<int>(), 4, Arbin<int>())), 1, Arbin<int>(Arbin<int>(Arbin<int>(), 5, Arbin<int>()), 3, Arbin<int>()));
    
    
    cout << a.esHoja();
    
    return 0;
}

