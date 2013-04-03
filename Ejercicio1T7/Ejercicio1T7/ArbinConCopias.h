/**
  @file Arbin.h

  Implementaci�n din�mica del TAD Arbol Binario.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012
*/
#ifndef __ARBIN_H
#define __ARBIN_H

#include "Excepciones.h"

#include "Lista.h" // Tipo devuelto por los recorridos

#include "Cola.h" // Tipo auxiliar para implementar el recorrido por niveles

/**
 Implementaci�n din�mica del TAD Arbin utilizando 
 nodos con un puntero al hijo izquierdo y otro al
 hijo derecho.

 Las operaciones son:

 - ArbolVacio: -> Arbin. Generadora implementada en el
   constructor sin par�metros.
 - Cons: Arbin, Elem, Arbin -> Arbin. Generadora implementada
   en un constructor con tres par�metros.
 - hijoIz, hijoDr: Arbin - -> Arbin. Observadoras que
   devuelven el hijo izquiero o derecho de un �rbol.
 - esVacio: Arbin -> Bool. Observadora que devuelve si
   un �rbol binario es vac�o.

 @author Marco Antonio G�mez Mart�n
 */
template <class T>
class Arbin {
public:

	/** Constructor; operacion ArbolVacio */
	Arbin() : _ra(NULL) {
	}

	/** Constructor; operacion Cons */
	Arbin(const Arbin &iz, const T &elem, const Arbin &dr) :
		_ra(new Nodo(copiaAux(iz._ra), elem, copiaAux(dr._ra))) {
	}

	/**
	 Otra operaci�n generadora (est�tica) que
	 evita las copias vaciando los �rboles que recibe.
	 */
	template <T>
	static Arbin<T> construyeYVacia(Arbin<T> &iz, const T &elem, Arbin<T> &dr) {
		Arbin<T> ret(new Arbin<T>::Nodo(iz._ra, elem, dr._ra));
		iz._ra = NULL;
		dr._ra = NULL;
		return ret;
	}

	/** Destructor; elimina la estructura jer�rquica de nodos. */
	~Arbin() {
		libera();
		_ra = NULL;
	}

	/**
	 Devuelve el elemento almacenado en la raiz

	 raiz(Cons(iz, elem, dr)) = elem
	 error raiz(ArbolVacio)
	 @return Elemento en la ra�z.
	 */
	const T &raiz() const {
		if (esVacio())
			throw EArbolVacio();
		return _ra->_elem;
	}

	/**
	 Devuelve un �rbol copia del �rbol izquierdo.
	 Es una operaci�n parcial (falla con el �rbol vac�o).

	 hijoIz(Cons(iz, elem, dr)) = iz
	 error hijoIz(ArbolVacio)
	*/
	Arbin hijoIz() const {
		if (esVacio())
			throw EArbolVacio();

		return Arbin(copiaAux(_ra->_iz));
	}

	/**
	 Devuelve un �rbol copia del �rbol derecho.
	 Es una operaci�n parcial (falla con el �rbol vac�o).

	 hijoDr(Cons(iz, elem, dr)) = dr
	 error hijoDr(ArbolVacio)
	*/
	Arbin hijoDr() const {
		if (esVacio())
			throw EArbolVacio();

		return Arbin(copiaAux(_ra->_dr));
	}

	/**
	 Operaci�n observadora que devuelve si el �rbol
	 es vac�o (no contiene elementos) o no.

	 esVacio(ArbolVacio) = true
	 esVacio(Cons(iz, elem, dr)) = false
	 */
	bool esVacio() const {
		return _ra == NULL;
	}

	// //
	// RECORRIDOS SOBRE EL �RBOL
	// //

	Lista<T> preorden() const {
		Lista<T> ret;
		preordenAcu(_ra, ret);
		return ret;
	}

	Lista<T> inorden() const {
		Lista<T> ret;
		inordenAcu(_ra, ret);
		return ret;
	}

	Lista<T> postorden() const {
		Lista<T> ret;
		postordenAcu(_ra, ret);
		return ret;
	}

	Lista<T> niveles() const {

		if (esVacio())
			return Lista<T>();

		Lista<T> ret;
		Cola<Nodo*> porProcesar;
		porProcesar.ponDetras(_ra);

		while (!porProcesar.esVacia()) {
			Nodo *visita = porProcesar.primero();
			porProcesar.quitaPrim();
			ret.ponDr(visita->_elem);
			if (visita->_iz)
				porProcesar.ponDetras(visita->_iz);
			if (visita->_dr)
				porProcesar.ponDetras(visita->_dr);
		}

		return ret;
	}

	// //
	// OTRAS OPERACIONES OBSERVADORAS
	// //

	/**
	 Devuelve el n�mero de nodos de un �rbol.
	 */
	unsigned int numNodos() const {
		return numNodosAux(_ra);
	}

	/**
	 Devuelve la talla del �rbol.
	 */
	unsigned int talla() const {
		return tallaAux(_ra);
	}

	/**
	 Devuelve el n�mero de hojas de un �rbol.
	 */
	unsigned int numHojas() const {
		return numHojasAux(_ra);
	}
    
    /*
     * Devuelve true si el árbol es una hoja.
     */
    bool esHoja() const {
        return (hijoIz().esVacio() && hijoDr().esVacio());
    }
    
    /*
     * Devuelve una lista con las hojas del árbol de izq a drch.
     */
    static Lista<T> frontera(const Arbin<T> &arbol) {
        Lista<T> ret;
        
        if (arbol.esVacio())
			return ret;
        
        if (arbol.esHoja()) {
            ret.ponDr(arbol.raiz());
        }
        
        Lista<T> hijoI = frontera(arbol.hijoIz());
        ret.concatenaCopia(hijoI);
        
        Lista<T> hijoD = frontera(arbol.hijoDr());
        ret.concatenaCopia(hijoD);
        
		return ret;
    }
    
    static Arbin<T> espejo(Arbin<T> &arbol) {
        
        Arbin<T> ret;
        
        if ( ! arbol.esVacio() ) {
            Arbin<T> iz = arbol.hijoIz();
            Arbin<T> dr = arbol.hijoDr();
            
            T elem = arbol.raiz();
            
            ret = Arbin<T>(dr, elem, iz);
        
            espejo(iz);
            espejo(dr);
        }
    
        return ret;
    }

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Arbin(const Arbin<T> &other) : _ra(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Arbin<T> &operator=(const Arbin<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const Arbin<T> &rhs) const {
		return comparaAux(_ra, rhs._ra);
	}

	bool operator!=(const Arbin<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y los punteros al hijo izquierdo y al hijo derecho.
	 */
	class Nodo {
	public:
		Nodo() : _iz(NULL), _dr(NULL) {}
		Nodo(const T &elem) : _elem(elem), _iz(NULL), _dr(NULL) {}
		Nodo(Nodo *iz, const T &elem, Nodo *dr) : 
			_elem(elem), _iz(iz), _dr(dr) {}

		T _elem;
		Nodo *_iz;
		Nodo *_dr;
	};

	/**
	 Constructor protegido que crea un �rbol
	 a partir de una estructura jer�rquica de nodos
	 previamente creada.
	 Se utiliza en hijoIz e hijoDr.
	 */
	Arbin(Nodo *raiz) : _ra(raiz) {
	}

	void libera() {
		libera(_ra);
	}

	void copia(const Arbin &other) {
		_ra = copiaAux(other._ra);
	}

	// //
	// M�TODOS AUXILIARES PARA LOS RECORRIDOS
	// //
	
	static void preordenAcu(Nodo *ra, Lista<T> &acu) {
		if (ra == NULL)
			return;

		acu.ponDr(ra->_elem);
		preordenAcu(ra->_iz, acu);
		preordenAcu(ra->_dr, acu);
	}

	static void inordenAcu(Nodo *ra, Lista<T> &acu) {
		if (ra == NULL)
			return;

		inordenAcu(ra->_iz, acu);
		acu.ponDr(ra->_elem);
		inordenAcu(ra->_dr, acu);
	}

	static void postordenAcu(Nodo *ra, Lista<T> &acu) {
		if (ra == NULL)
			return;

		postordenAcu(ra->_iz, acu);
		postordenAcu(ra->_dr, acu);
		acu.ponDr(ra->_elem);
	}

	// //
	// M�TODOS AUXILIARES (RECURSIVOS) DE OTRAS OPERACIONES
	// OBSERVADORAS
	// //

	static unsigned int numNodosAux(Nodo *ra) {
		if (ra == NULL)
			return 0;
		return 1 + numNodosAux(ra->_iz) + numNodosAux(ra->_dr);
	}

	static unsigned int tallaAux(Nodo *ra) {
		if (ra == NULL)
			return 0;

		int tallaiz = tallaAux(ra->_iz);
		int talladr = tallaAux(ra->_dr);
		if (tallaiz > talladr)
			return 1 + tallaiz;
		else
			return 1 + talladr;
	}

	static unsigned int numHojasAux(Nodo *ra) {
		if (ra == NULL)
			return 0;

		if ((ra->_iz == NULL) && (ra->_dr == NULL))
			return 1;

		return numHojasAux(ra->_iz) + numHojasAux(ra->_dr);
	}

private:

	/**
	 Elimina todos los nodos de una estructura arb�rea
	 que comienza con el puntero ra.
	 Se admite que el nodo sea NULL (no habr� nada que
	 liberar).
	 */
	static void libera(Nodo *ra) {
		if (ra != NULL) {
			libera(ra->_iz);
			libera(ra->_dr);
			delete ra;
		}
	}

	/**
	 Copia la estructura jer�rquica de nodos pasada
	 como par�metro (puntero a su raiz) y devuelve un
	 puntero a una nueva estructura jer�rquica, copia
	 de anterior (y que, por tanto, habr� que liberar).
	 */
	static Nodo *copiaAux(Nodo *ra) {
		if (ra == NULL)
			return NULL;

		return new Nodo(copiaAux(ra->_iz),
						ra->_elem,
						copiaAux(ra->_dr));
	}

	/**
	 Compara dos estructuras jer�rquicas de nodos,
	 dadas sus raices (que pueden ser NULL).
	 */
	static bool comparaAux(Nodo *r1, Nodo *r2) {
		if (r1 == NULL)
			return (r2 == NULL);
		else if (r2 == NULL)
			return false;
		else {
			return (r1->_elem == r2->_elem) &&
				comparaAux(r1->_iz, r2->_iz) &&
				comparaAux(r1->_dr, r2->_dr);
		}
	}

protected:
	// Ra�z protegida para poder hacer los ejercicios
	// de extensi�n del TAD Arbin heredando de la clase
	/** 
	 Puntero a la ra�z de la estructura jer�rquica
	 de nodos.
	 */
	Nodo *_ra;
};

#endif // __ARBIN_H
