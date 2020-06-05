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

/*	Revisa si la ra�z del �rbol existe. Si no, crea un nuevo nodo como la ra�z.
	Si ya existe, se el nodo se inserta en su lugar correspondiente. */
Nodo* Arbol::insertarNodo(int dato){
	bool doble = false; // toma el valor true cuando se intenta ingresar un dato que ya est� en el �rbol
	Nodo *nuevo = new Nodo(dato);
	Nodo *nodo; // apuntador que va recorriendo el �rbol
	if(raiz == NULL){
		cout<<"\n\tEl nodo se inserto como raiz del arbol..."<<endl;
		raiz = nuevo;
		altura = 1;
		//cout<<"raiz: "<<raiz->getInfo()<<endl;
	}else{
		nodo = raiz;
		while(!doble&&nuevo->getPadre()==NULL){
			if(dato==nodo->getInfo()){
				cout<<"\n\tEl nodo ya se encuentra en el arbol..."<<endl;
				doble = true;
			}
		}
	}
	return raiz;
}
