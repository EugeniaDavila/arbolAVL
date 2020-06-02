#include "Nodo.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Nodo::Nodo(int dato,int type){
	info = dato;
	izq = NULL;
	der = NULL;
	padre = NULL;
	revision = 0;
	tipo = type;
}
