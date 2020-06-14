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
		cout<<"\n\tEl nodo se insert\xa2 como ra\xa1z del \xa0rbol..."<<endl;
		raiz = nuevo;
		altura = 1;
	}else{
		nodo = raiz;
		while(!doble && nuevo->getPadre()==NULL){
			if(dato==nodo->getInfo()){
				cout<<"\n\tEl nodo ya se encuentra en el \xa0rbol..."<<endl;
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

 /* Muestra el recorrido en preorden del árbol (Raíz,Nodo Izquierdo, Nodo Derecho)
 	El ciclo se ejecuta mientras el estado (revisión) de la ráiz del árbol sea menor a 3.
 	El árbol se va recorriendo de la siguiente manera: al apuntar a un nodo se imprime su valor
 	y se avanza a su hijo izquierdo, mostrando tambien su valor. Si no hay hijo izquierdo, en su lugar
	se avanza al hijo derecho mostrando su valor. 
	Con el atributo revisión se indica cuantas veces se ha pasado por un nodo y que es lo que se debe hacer con el.
	0:	Es la primera vez que se revisa el nodo, por lo tanto el elemento se muestra en pantalla
	1:	Se revisa si el nodo tiene un hijo izquierdo, si lo tiene, el apuntador avanza a ese hijo,
		si no. EL estado del nodo cambia a 2 para indicar que ahora se debe revisar si el nodo tiene
		un hijo derecho.
	2:	Se revisa si el nodo actual tiene hijo derecho, si lo tiene, avanza a ese nodo.
		Si no tiene, revisa si el nodo actual actual es una raíz, si lo escambia el estado a 3.
		Si el nodo ya no tiene hijo derecho, entonces ese subarbol ya se terminado de analizar
		el nodo actual reinicia su estado a 0 y si el nodo es el hijo derecho de otro nodo, se cambia
		el estado de su nodo padre a 3, para indicar que el análisis de sus nodos hijo está completo.
		El apuntador se coloca en el nodo padre. 
	3:	El estado 3 indica que todos los hijos de un nodo ya han sido analizados.
		El estado del nodo se reinicia a 0 si el nodo es de tipo 2 (hijo derecho), y se modifica el 
		estado de su nodo padre a 3.
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

/*	Muestra el recorrido en inorden del árbol (Nodo Izquierdo, Raíz, Nodo Derecho)
	El árbol se va recorriendo nodo a nodo de la siguiente manera: se comprueba primero
	si un nodo tiene un hijo izquierdo, si lo tiene se avanza a ese hijo, si no, se
	muestra el valor del nodo y se avanza al hijo derecho, repitiendo el análisis para
	ese nodo. 
	Con el atributo revisión se indica cuantas veces se ha pasado por un nodo y que es lo que se debe hacer con el.
	0:	Revisa si el nodo tiene hijo izquierdo, si lo tiene avanza a ese nodo, si no, imprime el valor del nodo actual.
	1:	Este estado lo tiene el nodo del cual ya se revisaron ambos lados de sus nodos hijos, pero dicho nodo puede
		ser parte de otro subárbol del cual sólo se ha revisado un lado.
	2:	Revisa si el nodo actual tiene hijo derecho, si lo tiene avanza a ese nodo. Si no lo tiene se puede suceder alguno
		de los siguientes tres casos:
	 	a)	Si el nodo actual es el hijo izquierdo de otro nodo, el puntero avanza a su nodo padre y muestra su valor en pantalla; 
		 	despues el valor de revisión del nodo se cambia a 2 para indicar que se debe revisar su hijo derecho.
		b)	Si el nodo actual es la raíz del árbol, el ciclo finaliza y su valor revision se inicializa a cero
		c)	Si el nodo es el hijo derecho de otro nodo, el puntero avanza al nodo padre y su atributo revision se cambia a 1,
			indicando que ya se han analizado ambos lados de ese subárbol
*/
void Arbol::inorden(){
	cout<<"\n\tInorden: ";
	bool terminado = false;
	Nodo *nodo = raiz; // apuntar a la raíz del árbol sin perder la referencia original
	while(!terminado){
		switch(nodo->getRevision()){
			case 0:
				nodo->setRevision(2);
				if(nodo->getIzq()==NULL){
					cout<<nodo->getInfo()<<" ";
				}else{
					nodo = nodo->getIzq();
				}
			break;
			case 1:
				if(nodo->getTipo()==0){
					nodo->setRevision(0);
					terminado = true;
				}else if(nodo->getTipo()==1){
					nodo->setRevision(0);
					nodo = nodo->getPadre();
					cout<<nodo->getInfo()<<" ";
					nodo->setRevision(2);
				}else{
					nodo->setRevision(0);
					nodo = nodo->getPadre();
					nodo->setRevision(1);
				}
			break;
			case 2:
				nodo->setRevision(0);
				if(nodo->getDer()==NULL){
					if(nodo->getTipo()==1){
						nodo = nodo->getPadre();
						cout<<nodo->getInfo()<<" ";
						nodo->setRevision(2);
					}else if(nodo->getTipo()==0){
						terminado = true;
						nodo->setRevision(0);
					}else{
						nodo = nodo->getPadre();
						nodo->setRevision(1);
					}
				}else{
					nodo = nodo->getDer();
				}
			break;
		}
	} 
}

/*	Muestra el recorrido en postorden del árbol (Nodo Izquierdo, Nodo Derecho, Raíz)
	0:	Revisa si el nodo tiene hijo izquierdo, si lo tiene, avanza a ese nodo.
		Si el nodo no lo tiene, solo cambia su revisión a 1, indicando que se debe revisar su hijo derecho
	1:	Revisa si el nodo actual tiene hijo derecho, si lo tiene avanza a este nodo.
		Si no lo tiene, revisión cambia a 2, en donde se indica que ya se han revisado ambos lados del nodo.
	2:	Se analiza el tipo de nodo:
		a)	Si el nodo es la raíz del árbol, entonces el termina su ejecución al estar analizados ambos lados del árbol.
		b)	Si el nodo es un hijo izquierdo o derecho, se muestra en pantalla y el apuntador avanza a su nodo padre
*/
void Arbol::postorden(){
	cout<<"\n\tPostorden: ";
	Nodo *nodo;
	nodo = raiz;
	bool terminado = false;
	while(!terminado){
		switch(nodo->getRevision()){
			case 0:
				nodo->setRevision(1);
				if(nodo->getIzq()!=NULL){
					nodo = nodo->getIzq();
				}
			break;
			case 1:
				nodo->setRevision(2);
				if(nodo->getDer()!=NULL){
					nodo = nodo->getDer();
				}
			break;
			case 2:
				if(nodo->getTipo()==0){
					terminado = true;
				}else{ // si el nodo es de tipo 1 o 2
					nodo->setRevision(0);
					cout<<nodo->getInfo()<<" ";
					nodo = nodo->getPadre();
				}
			break;
		}
	}
	raiz->setRevision(0);
	cout<<raiz->getInfo()<<endl;
}

/*	Para buscar un nodo se compara el valor ingresado por el usuario con
	el valor del nodo actual, iniciando desde la raíz, Si el valor del nodo
	es menor al valor del usuario, se busca avanzar al hijo izquierdo del
	nodo actual. Si el valor que busca el usuario es mayor al valor del nodo
	actual, se busca avanzar al hijo derecho. Si el nodo al que se debe avanzar
	no existiera, entonces el dato buscado no se encontraría en el árbol, por lo que
	la bandera fallo tomaría el valor true. 
*/
Nodo* Arbol::buscarNodo(int n){
	bool encontrado = false;
	bool fallo = false;
	Nodo *nodo = raiz;
	if(raiz!=NULL){
		while(!encontrado&&!fallo){
			if(n>nodo->getInfo()){
				if(nodo->getDer()!=NULL){
					nodo = nodo->getDer();
				}else{
					fallo = true;
				}
			}else if(n<nodo->getInfo()){
				if(nodo->getIzq()!=NULL){
					nodo = nodo->getIzq();
				}else{
					fallo = true;
				}
			}else{
				encontrado = true;
			}
		}
		if(fallo){
			nodo = NULL;
		}
	}
	return nodo;
}

void Arbol::borrarNodo(int info){
	Nodo *nodo = buscarNodo(info);
	if(nodo==NULL){
		cout<<"\tNo se pudo eliminar el nodo."<<endl;
		cout<<"\tEl nodo no est\xa0 en el \xa0rbol..."<<endl;
	}else{
		cout<<"\tEliminando nodo..."<<endl;
		if(nodo->getDer()==NULL&nodo->getIzq()==NULL){ // si el nodo no tiene hijos
			cout<<"\tEl nodo no tiene hijos..."<<endl;
			if(nodo->getTipo()==1){  // si el nodo es un hijo izquierdo
				nodo->getPadre()->setIzq(NULL);
			}else if(nodo->getTipo()==2){ // si el nodo es un hijo derecho
				nodo->getPadre()->setDer(NULL);
			}
		}else if(nodo->getIzq()!=NULL&&nodo->getDer()==NULL){
			cout<<"\tEl nodo tiene un hijo izquierdo..."<<endl;
			if(nodo->getTipo()==1){  
				nodo->getPadre()->setIzq(nodo->getIzq());
				nodo->getIzq()->setPadre(nodo->getPadre());
			}else if(nodo->getTipo()==2){ 
				nodo->getPadre()->setDer(nodo->getIzq());
				nodo->getIzq()->setPadre(nodo->getPadre());
				nodo->getIzq()->setTipo(2);
			}else{
				raiz=nodo->getIzq();
				raiz->setTipo(0);
				raiz->setPadre(NULL);
			}
		}
		delete nodo;
		nodo = NULL;
	}
}
