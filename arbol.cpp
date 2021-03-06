#include "Arbol.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

/* Constructor por defecto */
Arbol::Arbol(){
	raiz = NULL;
}

/* Cambiar el nodo al que apunta la ra�z */
void Arbol::setRaiz(Nodo *r){
	raiz = r;
}

/* Obtener el nodo que apunta a la ra�z*/
Nodo* Arbol::getRaiz(){
	return raiz;
}

/*	Revisa si la ra�z del �rbol existe. Si no, crea un nuevo nodo como la ra�z.
	Si ya existe, se el nodo se inserta en su lugar correspondiente. 
	Para insertar el nodo primero se compara el valor a insertar con el valor que 
	tiene el nodo actual; si es menor, el apuntador avanza al hijo izquierdo del nodo
	(si hubiera), sino, se inserta uno nuevo como su hijo izquiero. Si el valor a insertar
	es m�s grande que el valor del nodo actual se hace el mismo procedimiento, pero del lado
	derecho.	
*/
Nodo* Arbol::insertarNodo(int dato){
	bool doble = false; // toma el valor true cuando se intenta ingresar un dato que ya est� en el �rbol
	Nodo *nuevo = new Nodo(dato);
	Nodo *nodo; // apuntador que va recorriendo el �rbol
	Nodo *nodoAux; // auxiliar para el balanceo de �rboles
	if(raiz == NULL){
		cout<<"\n\tEl nodo se insert\xa2 como ra\xa1z del \xa0rbol..."<<endl;
		raiz = nuevo;
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
				}else{
					nodo = nodo->getIzq();
				}
			}else{ //if(info>nodo->dato)
				if(nodo->getDer()==NULL){
					nuevo->setPadre(nodo);
					nodo->setDer(nuevo);
					nuevo->setTipo(2);
					cout<<"\n\tDato insertado correctamente..."<<endl;
				}else{
					nodo = nodo->getDer();
				}				
			}
		}
	}
	if(!doble){
		nodoAux = calcularEquilibrio();
		if(nodoAux!=NULL){
			restructurar(nodoAux);
		}
	}
	return raiz;
}

 /* Muestra el recorrido en preorden del �rbol (Ra�z,Nodo Izquierdo, Nodo Derecho)
 	El ciclo se ejecuta mientras el estado (revisi�n) de la r�iz del �rbol sea menor a 3.
 	El �rbol se va recorriendo de la siguiente manera: al apuntar a un nodo se imprime su valor
 	y se avanza a su hijo izquierdo, mostrando tambien su valor. Si no hay hijo izquierdo, en su lugar
	se avanza al hijo derecho mostrando su valor. 
	Con el atributo revisi�n se indica cuantas veces se ha pasado por un nodo y que es lo que se debe hacer con el.
	0:	Es la primera vez que se revisa el nodo, por lo tanto el elemento se muestra en pantalla
	1:	Se revisa si el nodo tiene un hijo izquierdo, si lo tiene, el apuntador avanza a ese hijo,
		si no. EL estado del nodo cambia a 2 para indicar que ahora se debe revisar si el nodo tiene
		un hijo derecho.
	2:	Se revisa si el nodo actual tiene hijo derecho, si lo tiene, avanza a ese nodo.
		Si no tiene, revisa si el nodo actual actual es una ra�z, si lo escambia el estado a 3.
		Si el nodo ya no tiene hijo derecho, entonces ese subarbol ya se terminado de analizar
		el nodo actual reinicia su estado a 0 y si el nodo es el hijo derecho de otro nodo, se cambia
		el estado de su nodo padre a 3, para indicar que el an�lisis de sus nodos hijo est� completo.
		El apuntador se coloca en el nodo padre. 
	3:	El estado 3 indica que todos los hijos de un nodo ya han sido analizados.
		El estado del nodo se reinicia a 0 si el nodo es de tipo 2 (hijo derecho), y se modifica el 
		estado de su nodo padre a 3.
 */
void Arbol::preorden(){
	cout<<"\n\tPreorden: ";
	Nodo *nodo = raiz; // hacer que la variable nodo apunte a la ra�z del �rbol, para no perder la referencia
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

/*	Muestra el recorrido en inorden del �rbol (Nodo Izquierdo, Ra�z, Nodo Derecho)
	El �rbol se va recorriendo nodo a nodo de la siguiente manera: se comprueba primero
	si un nodo tiene un hijo izquierdo, si lo tiene se avanza a ese hijo, si no, se
	muestra el valor del nodo y se avanza al hijo derecho, repitiendo el an�lisis para
	ese nodo. 
	Con el atributo revisi�n se indica cuantas veces se ha pasado por un nodo y que es lo que se debe hacer con el.
	0:	Revisa si el nodo tiene hijo izquierdo, si lo tiene avanza a ese nodo, si no, imprime el valor del nodo actual.
	1:	Este estado lo tiene el nodo del cual ya se revisaron ambos lados de sus nodos hijos, pero dicho nodo puede
		ser parte de otro sub�rbol del cual s�lo se ha revisado un lado.
	2:	Revisa si el nodo actual tiene hijo derecho, si lo tiene avanza a ese nodo. Si no lo tiene se puede suceder alguno
		de los siguientes tres casos:
	 	a)	Si el nodo actual es el hijo izquierdo de otro nodo, el puntero avanza a su nodo padre y muestra su valor en pantalla; 
		 	despues el valor de revisi�n del nodo se cambia a 2 para indicar que se debe revisar su hijo derecho.
		b)	Si el nodo actual es la ra�z del �rbol, el ciclo finaliza y su valor revision se inicializa a cero
		c)	Si el nodo es el hijo derecho de otro nodo, el puntero avanza al nodo padre y su atributo revision se cambia a 1,
			indicando que ya se han analizado ambos lados de ese sub�rbol
*/
void Arbol::inorden(){
	cout<<"\n\tInorden: ";
	bool terminado = false;
	Nodo *nodo = raiz; // apuntar a la ra�z del �rbol sin perder la referencia original
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

/*	Muestra el recorrido en postorden del �rbol (Nodo Izquierdo, Nodo Derecho, Ra�z)
	0:	Revisa si el nodo tiene hijo izquierdo, si lo tiene, avanza a ese nodo.
		Si el nodo no lo tiene, solo cambia su revisi�n a 1, indicando que se debe revisar su hijo derecho
	1:	Revisa si el nodo actual tiene hijo derecho, si lo tiene avanza a este nodo.
		Si no lo tiene, revisi�n cambia a 2, en donde se indica que ya se han revisado ambos lados del nodo.
	2:	Se analiza el tipo de nodo:
		a)	Si el nodo es la ra�z del �rbol, entonces el termina su ejecuci�n al estar analizados ambos lados del �rbol.
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
	el valor del nodo actual, iniciando desde la ra�z, Si el valor del nodo
	es menor al valor del usuario, se busca avanzar al hijo izquierdo del
	nodo actual. Si el valor que busca el usuario es mayor al valor del nodo
	actual, se busca avanzar al hijo derecho. Si el nodo al que se debe avanzar
	no existiera, entonces el dato buscado no se encontrar�a en el �rbol, por lo que
	la bandera fallo tomar�a el valor true. 
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

/*	Funci�n para eliminar un nodo seleccionado por el usuario.
	Se llama a la funci�n buscarNodo y el resultado si es distinto de NULL se
	apunta mediante la variable nodo.
	Despu�s se procede a hacer la eliminaci�n del nodo en base a las reglas de
	�rboles binarios.
*/
void Arbol::borrarNodo(int info){
	Nodo *nodo = buscarNodo(info);
	Nodo *sustituto, *aux;
	if(nodo==NULL){
		cout<<"\n\tNo se pudo eliminar el nodo."<<endl;
		cout<<"\n\tEl nodo no est\xa0 en el \xa0rbol..."<<endl;
	}else{
		if(nodo->getDer()==NULL&nodo->getIzq()==NULL){ // si el nodo no tiene hijos
			if(nodo->getTipo()==1){  // si el nodo es un hijo izquierdo
				nodo->getPadre()->setIzq(NULL);
			}else if(nodo->getTipo()==2){ // si el nodo es un hijo derecho
				nodo->getPadre()->setDer(NULL);
			}else{
				raiz = NULL;
			}
		}else if((nodo->getIzq()!=NULL&&nodo->getDer()==NULL)||(nodo->getIzq()==NULL&&nodo->getDer()!=NULL)){ 
			// si el nodo s�lo tiene un hijo
			if(nodo->getIzq()!=NULL){
				nodo->setInfo(nodo->getIzq()->getInfo());
				nodo = nodo->getIzq();
				nodo->getPadre()->setIzq(NULL);
			}else if(nodo->getDer()!=NULL){
				nodo->setInfo(nodo->getDer()->getInfo());
				nodo = nodo->getDer();
				nodo->getPadre()->setDer(NULL);
			}		
		}else{ // el nodo tiene ambos hijos
			// Buscar el nodo mayor del lado izquierdo o el menor del lado derecho
			// En este caso se utiliza el nodo de mayor valor del sub�rbol izquierdo
			sustituto = buscarMayorIzq(nodo);
			// Reemplazar el nodo encontrado por el que se quiere borrar
			//cout<<"el mayor de la izquierda es: "<<sustituto->getInfo()<<endl;
			nodo->setInfo(sustituto->getInfo());
			if(nodo->getIzq()==sustituto){
				if(sustituto->getIzq()!=NULL){
					sustituto->getIzq()->setPadre(nodo);
					nodo->setIzq(sustituto->getIzq());
				}else{
					nodo->setIzq(NULL);
				}
			}else{
				if(sustituto->getIzq()!=NULL){
					aux = sustituto->getIzq();
					sustituto->getPadre()->setDer(aux);
					aux->setPadre(sustituto->getPadre());
					aux->setTipo(2);
				}else{
					sustituto->getPadre()->setDer(NULL);
				}
			}
			nodo = sustituto;
		}
		delete nodo;
		nodo = NULL;
		if(raiz!=NULL){
			Nodo *nodoAux = calcularEquilibrio();
			if(nodoAux!=NULL){
				restructurar(nodoAux);
			}
		}
		cout<<"Nodo eliminado."<<endl;
	}
}

/*	Busca el nodo de mayor valor del sub�rbol izquierdo.
	El nodo siempre ser� encontrado avanzando al nodo izquierdo del padre del sub�rbol
	y despues avanzando por el hijo derecho mientras este sea distinto de NULL
*/
Nodo* Arbol::buscarMayorIzq(Nodo *n){
	Nodo *nodo = n->getIzq();
	while(nodo->getDer()!=NULL){
		nodo = nodo->getDer();
	}
	return nodo;
}

/*	El factor de equilibrio se debe calcular para cada nodo del �rbol.
	Para un nodo T del �rbol la altura de los sub�rboles izquierdo y derecho no deben
	diferir en m�s de una unidad.
*/
Nodo* Arbol::calcularEquilibrio(){
	Nodo *nodo = raiz;
	bool fallo = false;
	int altura;
	while(raiz->getRevision()<=2&&!fallo){
		switch(nodo->getRevision()){
			case 0: 
				// revisa si el nodo tiene hijo izquierdo
				nodo->setRevision(1);
				if(nodo->getIzq()!=NULL){
					nodo = nodo->getIzq();
				}else{
					nodo->setAlturaIzq(0);
				}
			break;
			case 1:
				// revisa si el nodo tiene hijo derecho
				nodo->setRevision(2);
				if(nodo->getDer()!=NULL){
					nodo = nodo->getDer();
				}else{
					nodo->setAlturaDer(0);
				}
			break;
			case 2:
				// calcula el factor de equilibrio del nodo
				nodo->setEquilibrio(nodo->getAlturaDer()-nodo->getAlturaIzq());
				if(abs(nodo->getEquilibrio())>1){ // El arbol no esta equilibrado
					fallo = true;
				}else{
					// regresar la altura del �rbol m�s grande
					altura = (nodo->getAlturaIzq()>=nodo->getAlturaDer())?nodo->getAlturaIzq():nodo->getAlturaDer();
					altura++;
					if(nodo->getTipo()==0){
						raiz->setRevision(3);
					}else{
						nodo->setRevision(0);
						nodo = notificarNodoPadre(nodo,altura);
					}
				}
			break;
		}
	}
	// Reiniciar el atributo revisi�n a 0 para los padres del nodo desequilibrado
	Nodo *aux = nodo;
	while(fallo&&aux!=raiz){
		aux->setRevision(0);
		aux = aux->getPadre();
	}
	if(!fallo){
		nodo = NULL;
	}
	raiz->setRevision(0);
	//regresar nodo no balanceado
	return nodo;
}

/*	Actualizar el nodo ra�z del sub�rbol con los valores de la altura del su�rbol izquierdo
	y derecho 
*/
Nodo* Arbol::notificarNodoPadre(Nodo *n,int altura){
	if(n->getTipo()==1){
		// mandar altura del sub�rbol izquierdo al nodo raiz
		n->getPadre()->setAlturaIzq(altura);
	}else if(n->getTipo()==2){
		// mandar altura del sub�rbol derecho al nodo raiz
		n->getPadre()->setAlturaDer(altura);
	}
	return n->getPadre();
}

/*	Hacer el intercambio entre el nodo desequilibrado y sus nodos
	hijos de acuerdo a las reglas de intercambio de �rboles binarios
	y seg�n el tipo de desequilibrio.
*/
void Arbol::restructurar(Nodo *n){
	int tipo; // tipo de equilibrio a hacer
	Nodo *nodo1 = n;
	Nodo *nodo2, *nodo3;
	if(nodo1->getEquilibrio()<=0){
		nodo2 = n->getIzq();
		if(nodo2->getEquilibrio()<=0){
			tipo = 1;
			nodo3 = nodo2->getIzq(); // Izq-Izq
		}else{
			tipo = 2;
			nodo3 = nodo2->getDer(); // Izq-Der
		}
	}else{
		nodo2 = n->getDer();
		if(nodo2->getEquilibrio()<=0){
			tipo = 3;
			nodo3 = nodo2->getIzq(); // Der-Izq
		}else{
			tipo = 4;
			nodo3 = nodo2->getDer(); // Der-Der
		}
	}
	Nodo *aux; // apuntador auxiliar para el intercambio de nodos
	switch(tipo){
		case 1:
			//cout<<"II"<<endl;
			if(nodo1==raiz){
				raiz = nodo2;
				nodo2->setTipo(0);
				nodo2->setPadre(NULL);
			}else{
				aux = nodo1->getPadre();
				nodo2->setPadre(aux);
				nodo2->setTipo(nodo1->getTipo());
				if(nodo1->getTipo()==1){
					aux->setIzq(nodo2);
				}else{
					aux->setDer(nodo2);
				}
			}
			// si nodo2 tiene un hijo derecho, convertirlo en hijo izquierdo de nodo1
			if(nodo2->getDer()!=NULL){
				nodo1->setIzq(nodo2->getDer());
				nodo1->getIzq()->setTipo(1);
				nodo1->getIzq()->setPadre(nodo1);
			}else{
				nodo1->setIzq(NULL);
			}
			// Convertir nodo1 en hijo derecho de nodo2
			nodo1->setPadre(nodo2);
			nodo1->setTipo(2);
			nodo2->setDer(nodo1);
		break;
		case 2:
			//cout<<"ID"<<endl;
			// Determinar los nuevos enlaces para el nodo padre del sub�rbol
			if(nodo1==raiz){
				raiz = nodo3;
				nodo3->setTipo(0);
				nodo3->setPadre(NULL);
			}else{
				aux = nodo1->getPadre();
				nodo3->setPadre(aux);
				nodo3->setTipo(nodo1->getTipo());
				if(nodo1->getTipo()==1){
					aux->setIzq(nodo3);
				}else{
					aux->setDer(nodo3);
				}
			}
			// si nodo3 tiene hijo derecho, este pasa como hijo izquierdo de nodo1
			if(nodo3->getDer()!=NULL){
				nodo1->setIzq(nodo3->getDer());
				nodo1->getIzq()->setTipo(1);
				nodo3->getDer()->setPadre(nodo1);
			}else{
				nodo1->setIzq(NULL);
			}
			// si nodo3 tiene hijo izquierdo, este pasa como hijo derecho de nodo2
			if(nodo3->getIzq()!=NULL){
				nodo2->setDer(nodo3->getIzq());
				nodo2->getDer()->setTipo(2);
				nodo3->getIzq()->setPadre(nodo2);
			}else{
				nodo2->setDer(NULL);
			}
			// establecer los enlaces entre los nodos nodo1 a nodo3
			nodo1->setPadre(nodo3);
			nodo3->setDer(nodo1);
			nodo1->setTipo(2);
			
			nodo2->setPadre(nodo3);
			nodo3->setIzq(nodo2);
		break;
		case 3:
			// verificar si el nodo1 corresponde a la ra�z del �rbol o es hijo de otro nodo
			//cout<<"DI"<<endl;
			if(nodo1==raiz){
				raiz = nodo3;
				nodo3->setTipo(0);
				nodo3->setPadre(NULL);
			}else{
				aux = nodo1->getPadre();
				nodo3->setPadre(aux);
				nodo3->setTipo(nodo1->getTipo());
				if(nodo1->getTipo()==1){
					aux->setIzq(nodo3);
				}else{
					aux->setDer(nodo3);
				}
			}
			// si el nodo3 tiene hijo derecho, ese hijo se convierte en hijo izquierdo de nodo2
			if(nodo3->getDer()!=NULL){
				nodo2->setIzq(nodo3->getDer());
				nodo3->getDer()->setPadre(nodo2);
				nodo2->getIzq()->setTipo(1);
			}else{
				nodo2->setIzq(NULL);
			}
			// si el nodo3 tiene hijo izquierdo, ese hijo se convierte en hijo derecho de nodo1
			if(nodo3->getIzq()!=NULL){
				nodo1->setDer(nodo3->getIzq());
				nodo3->getIzq()->setPadre(nodo1);
				nodo1->getDer()->setTipo(2);
			}else{
				nodo1->setDer(NULL);
			}
			// establecer los nuevos enlaces entre los nodos nodo1 a nodo3
			nodo1->setTipo(1);
			nodo1->setPadre(nodo3);
			nodo3->setIzq(nodo1);
			
			nodo2->setPadre(nodo3);
			nodo3->setDer(nodo2);
		break;
		case 4:
			//cout<<"DD"<<endl;
			if(nodo1==raiz){
				raiz = nodo2;
				nodo2->setTipo(0);
				nodo2->setPadre(NULL);
			}else{
				aux = nodo1->getPadre();
				nodo2->setPadre(aux);
				nodo2->setTipo(nodo1->getTipo());
				if(nodo1->getTipo()==1){
					aux->setIzq(nodo2);
				}else if(nodo1->getTipo()==2){
					aux->setDer(nodo2);
				}
			}
			// si nodo2 tiene un hijo izquierdo, el hijo se convierte en hijo derecho de nodo1
			if(nodo2->getIzq()!=NULL){
				nodo1->setDer(nodo2->getIzq());
				nodo1->getDer()->setTipo(2);
				nodo1->getDer()->setPadre(nodo1);
			}else{
				nodo1->setDer(NULL);
			}
			// Convertir nodo1 en hijo izquierdo de nodo2
			nodo1->setPadre(nodo2);
			nodo1->setTipo(1);
			nodo2->setIzq(nodo1);
		break; 
	}
}

/*	Mostrar un representaci�n del �rbol en pantalla
	La variable nivel se utiliza para indentar cada elemento del �rbol. Se inicializa a 0,
	representando la ra�z del �rbol.
	El recorrido es similar al recorrido en preorden, pero en cada salto de nodo, se incrementa
	o decrementa la variable nivel.
*/
void Arbol::mostrarArbol(){
	cout<<endl;
	Nodo *nodo = raiz; // hacer que la variable nodo apunte a la ra�z del �rbol, para no perder la referencia
	int nivel = 0; // usada para la indentaci�n de los nodos
	while(raiz->getRevision()<3){
		switch(nodo->getRevision()){
			case 0:
				nodo->setRevision(1);
				cout<<"\t";
				if(nivel>0){
					cout<<"\xb0\xb0\xb0"; // mostrar desplazamiento
					for(int i=1;i<nivel;i++){
						//cout<<"|\xdb\xdb";
						cout<<"|\xb0\xb0";
					}
				}
				// Imprimir los s�mbolos que aparecen junto a la informaci�n del nodo
				cout<<"\xcc\xcd "<<nodo->getInfo()<<endl;
			break;
			case 1:
				nodo->setRevision(2);
				if(nodo->getIzq()!=NULL){
					nodo = nodo->getIzq();
					nivel++;
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
						nivel--;
					}
				}else{
					nodo = nodo->getDer();
					nivel++;
				}
			break;
			case 3:
				nodo->setRevision(0);
				if(nodo->getTipo()==2){
					nodo->getPadre()->setRevision(3);
				}
				nodo = nodo->getPadre();	
				nivel--;	
			break;
		}
	}
	raiz->setRevision(0);
}
