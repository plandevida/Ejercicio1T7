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

void hoja(Arbin<int> &arbol);

int main(int argc, const char * argv[]) {

    Arbin<int> a(Arbin<int>(Arbin<int>(),2,Arbin<int>(Arbin<int>(), 4, Arbin<int>())), 1, Arbin<int>(Arbin<int>(Arbin<int>(), 5, Arbin<int>()), 3, Arbin<int>()));
    
    hoja(a);
    
    Lista<int> lista = Arbin<int>::frontera(a);
    
    Lista<int>::Iterador it = lista.principio();
    
    while (it != lista.final()) {
        cout << it.elem() << endl;
        it.avanza();
    }
    
    Arbin<int> espejo = Arbin<int>::espejo(a);
    
    lista = espejo.niveles();
    
    it = lista.principio();
    
    while (it != lista.final()) {
        cout << it.elem() << endl;
        it.avanza();
    }
    
    return 0;
}

void hoja(Arbin<int> &arbol) {
    
    if ( ! arbol.esVacio()) {
        cout << "Es hoja?" << arbol.esHoja() << endl;
        
        Arbin<int> hijoI = arbol.hijoIz();
        hoja(hijoI);
        
        Arbin<int> hijoD = arbol.hijoIz();
        hoja(hijoD);
    }
}