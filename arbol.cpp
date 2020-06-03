#include "Arbol.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Arbol::Arbol(){
	altura = 0;
	lista = NULL;
}

void Arbol::setAltura(int a){
	altura = a;
}

int Arbol::getAltura(){
	return altura;
} 
