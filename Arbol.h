#include "nodo.cpp"
#ifndef Arbol_h_included
#define Arbol_h_included

class Arbol{
	private:
		int altura;
		Nodo* lista; // lista de nodos
		
	public:
		// Constructor
		Arbol();
		
		// setters y getters
		void Arbol::setAltura(int a)
		int Arbol::getAltura()
		
		// M�todos generales
		Nodo* insertarNodo(int info);
		Nodo* borrarNodo(int info,struct Nodo *raiz);
		void preorden(struct Nodo *raiz);
		void inorden(struct Nodo *raiz);
		void postorden(struct Nodo *raiz);
		void buscarNodo(int n,struct Nodo *raiz);
		void mostrarArbol(struct Nodo *raiz);
};

#endif
