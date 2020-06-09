#include "Arbol.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Constructor por defecto
Arbol::Arbol(){
	altura = 0;
	raiz = NULL;
}

/* Modificar el valor de la altura del árbol */
void Arbol::setAltura(int a){
	altura = a;
}

/* Obtener la altura del árbol*/
int Arbol::getAltura(){
	return altura;
} 

/* Cambiar el nodo al que apunta la raíz */
void Arbol::setRaiz(Nodo *r){
	raiz = r;
}

/* Obtener el nodo que apunta a la raíz*/
Nodo* Arbol::getRaiz(){
	return raiz;
}

/*	Revisa si la raíz del árbol existe. Si no, crea un nuevo nodo como la raíz.
	Si ya existe, se el nodo se inserta en su lugar correspondiente. 
	Para insertar el nodo primero se compara el valor a insertar con el valor que 
	tiene el nodo actual; si es menor, el apuntador avanza al hijo izquierdo del nodo
	(si hubiera), sino, se inserta uno nuevo como su hijo izquiero. Si el valor a insertar
	es más grande que el valor del nodo actual se hace el mismo procedimiento, pero del lado
	derecho.	
*/
Nodo* Arbol::insertarNodo(int dato){
	bool doble = false; // toma el valor true cuando se intenta ingresar un dato que ya está en el árbol
	Nodo *nuevo = new Nodo(dato);
	Nodo *nodo; // apuntador que va recorriendo el árbol
	if(raiz == NULL){
		cout<<"\n\tEl nodo se insert\xa2 como ra\xa1z del \xa2rbol..."<<endl;
		raiz = nuevo;
		altura = 1;
	}else{
		nodo = raiz;
		while(!doble && nuevo->getPadre()==NULL){
			if(dato==nodo->getInfo()){
				cout<<"\n\tEl nodo ya se encuentra en el \xa2rbol..."<<endl;
				doble = true;
				delete nuevo;
			}else if(dato < nodo->getInfo()){
				if(nodo->getIzq()==NULL){
					nuevo->setPadre(nodo);
					nodo->setIzq(nuevo);
					nuevo->setTipo(1);
					cout<<"\n\tDato insertado correctamente..."<<endl;
					cout<<"\tNodo padre: "<<nuevo->getPadre()->getInfo()<<endl;
					cout<<"\tTipo de hijo: "<<nuevo->getTipo()<<endl;
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
 /* Muestra el recorrido en preorden del árbol 
	0:	es la primera vez que se revisa el nodo, por lo tanto el elemento se muestra en pantalla
	1:	se revisa si el nodo tiene un hijo izquierdo, si lo tiene, el apuntador avanza a ese hijo,
		si no. EL estado del nodo cambia a 2 para indicar que ahora se debe revisar si el nodo tiene
		un hijo derecho.
	2:
	3:
 */
void Arbol::preorden(){
	cout<<"\n\tPreorden: ";
	Nodo *nodo = raiz; // hacer que la variable nodo apunte a la raíz del árbol, para no perder la referencia
	while(raiz->getRevision()<3){
		switch(nodo->getRevision()){
			case 0:
				nodo->setRevision(1);
				cout<<nodo->getInfo()<<" ";
			break;
			case 1:
				nodo->setRevision(2);
				if(nodo->getIzq()!=NULL){
					nodo = nodo->getIzq();
				}
			break;
			case 2:
				if(nodo->getDer()==NULL){
					if(nodo->getTipo()==0){
						nodo->setRevision(3);
					}else{
						nodo->setRevision(0);
						if(nodo->getTipo()==2){
							nodo->getPadre()->setRevision(3);
						}
						nodo = nodo->getPadre();
					}
				}else{
					nodo = nodo->getDer();
				}
			break;
			case 3:
				nodo->setRevision(0);
				if(nodo->getTipo()==2){
					nodo->getPadre()->setRevision(3);
				}
				nodo = nodo->getPadre();			
			break;
		}
	}
	raiz->setRevision(0);
}







