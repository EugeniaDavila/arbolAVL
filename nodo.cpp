#include "Nodo.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Constructores
Nodo::Nodo(){
	info = 0;
	izq = NULL;
	der = NULL;
	padre = NULL;
	revision = 0;
	tipo = 0;
}

Nodo::Nodo(int dato,int type){
	info = dato;
	izq = NULL;
	der = NULL;
	padre = NULL;
	revision = 0;
	tipo = type;
}

Nodo::Nodo(int dato){
	info = dato;
	izq = NULL;
	der = NULL;
	padre = NULL;
	revision = 0;
	tipo = 0;
}

// Setters
void Nodo::setInfo(int dato){
	info = dato;
}

void Nodo::setTipo(int t){
	tipo = t;
}

void Nodo::setRevision(int rev){
	revision = rev;
}

void Nodo::setIzq(Nodo *i){
	izq = i;
}

void Nodo::setDer(Nodo *d){
	der = d;
}

void Nodo::setPadre(Nodo *p){
	padre = p;
}

void Nodo::setAlturaIzq(int i){
	alturaIzq = i;
}

void Nodo::setAlturaDer(int d){
	alturaDer = d;
}

// Getters
int Nodo::getInfo(){
	return info;
}

int Nodo::getTipo(){
	return tipo;
}

int Nodo::getRevision(){
	return revision;
}

Nodo* Nodo::getDer(){
	return der;
}

Nodo* Nodo::getIzq(){
	return izq;
}

Nodo* Nodo::getPadre(){
	return padre;
}

int Nodo::getAlturaIzq(){
	return alturaIzq;
}

int Nodo::getAlturaDer(){
	return alturaDer;
}		
