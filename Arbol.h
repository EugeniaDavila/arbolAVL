#include "nodo.cpp"
#ifndef Arbol_h_included
#define Arbol_h_included

class Arbol{
	private:
		Nodo *raiz; // raiz del árbol
		
	public:
		// Constructor
		Arbol();
		
		// setters y getters
		void setAltura(int a);
		void setRaiz(Nodo *r);
		int getAltura();
		Nodo* getRaiz();
		
		// Métodos generales
		Nodo* insertarNodo(int info);
		void borrarNodo(int info);
		void preorden();
		void inorden();
		void postorden();
		Nodo* buscarNodo(int n);
		Nodo* buscarMayorIzq(Nodo *n);
		Nodo* calcularEquilibrio();
		Nodo* notificarNodoPadre(Nodo *n,int altura);
		void restructurar(Nodo *n);
		void mostrarArbol();
};

#endif
