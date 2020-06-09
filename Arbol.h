#include "nodo.cpp"
#ifndef Arbol_h_included
#define Arbol_h_included

class Arbol{
	private:
		int altura;
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
		Nodo* borrarNodo(int info,struct Nodo *raiz);
		void preorden();
		void inorden();
		void postorden();
		void buscarNodo(int n,struct Nodo *raiz);
		void mostrarArbol(struct Nodo *raiz);
};

#endif
