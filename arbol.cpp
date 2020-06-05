#include "Arbol.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Arbol::Arbol(){
	altura = 0;
	raiz = NULL;
}

void Arbol::setAltura(int a){
	altura = a;
}

int Arbol::getAltura(){
	return altura;
} 

void Arbol::setRaiz(Nodo *r){
	raiz = r;
}

Nodo* Arbol::getRaiz(){
	return raiz;
}

/*	Revisa si la raíz del árbol existe. Si no, crea un nuevo nodo como la raíz.
	Si ya existe, se el nodo se inserta en su lugar correspondiente. */
Nodo* Arbol::insertarNodo(int dato){
	if(raiz == NULL){
		cout<<"\n\tEl nodo se inserto como raiz del arbol..."<<endl;
		Nodo r(dato);
		raiz = &r;
		altura = 1;
		// cout<<"raiz: "<<raiz->getInfo()<<endl;
	}else{
		
	}
	return raiz;
}
