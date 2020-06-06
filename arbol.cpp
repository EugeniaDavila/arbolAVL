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
	Si ya existe, se el nodo se inserta en su lugar correspondiente. 
	
*/
Nodo* Arbol::insertarNodo(int dato){
	bool doble = false; // toma el valor true cuando se intenta ingresar un dato que ya está en el árbol
	Nodo *nuevo = new Nodo(dato);
	Nodo *nodo; // apuntador que va recorriendo el árbol
	if(raiz == NULL){
		cout<<"\n\tEl nodo se inserto como raiz del arbol..."<<endl;
		raiz = nuevo;
		altura = 1;
	}else{
		nodo = raiz;
		while(!doble&&nuevo->getPadre()==NULL){
			if(dato==nodo->getInfo()){
				cout<<"\n\tEl nodo ya se encuentra en el arbol..."<<endl;
				doble = true;
			}else if(dato < nodo->getInfo()){
				if(nodo->getIzq()==NULL){
					nuevo->setPadre(nodo);
					nodo->setIzq(nuevo);
					nuevo->setTipo(1);
					cout<<"\n\tDato insertado correctamente..."<<endl;
					cout<<"\tNodo padre: "<<nuevo->getPadre()->getInfo()<<endl;
					cout<<"\tHijo: "<<nuevo->getTipo()<<endl;
				}else{
					nodo = nodo->getIzq();
				}
			}else{ //if(info>nodo->dato)
				if(nodo->getDer()==NULL){
					nuevo->setPadre(nodo);
					nodo->setDer(nuevo);
					nuevo->setTipo(2);
					cout<<"\n\tDato insertado correctamente..."<<endl;
					cout<<"\tNodo padre: "<<nuevo->getPadre()->getInfo()<<endl;
					cout<<"\tHijo: "<<nuevo->getTipo()<<endl;
				}else{
					nodo = nodo->getDer();
				}				
			}
		}
	}
	return raiz;
}
