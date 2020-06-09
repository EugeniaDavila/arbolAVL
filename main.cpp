#include <iostream>
#include <cstdlib>
#include "arbol.cpp"

using namespace std;

// prototipos de funciones
void menu();

int main(int argc, char** argv) {
	int op; // opción del menú seleccionada por el usuario
	int info; // entero que el usuario añade al árbol 
	Arbol a;
	do{
		menu();
		cin>>op;
		switch(op){
			case 1:
				cout<<"\tDato a ingresar: ";
				cin>>info;
				a.insertarNodo(info);
			break;
			case 2:
			
			break;
			case 3:
				
			break;
			case 4:
				
			break;
			case 5:
				a.preorden();
			break;
			case 0:
				cout<<"\n\tSaliendo del programa..."<<endl;
				cout<<"\t";
				system("PAUSE");
				return 0;
			break;
			default:
				cout<<"\n\tOpcion no valida.\n\tPor favor intentalo de nuevo"<<endl;
			break;
		}
		cout<<"\n\t";
		system("pause");
		system("cls");
	}while(op!=0);
	return 0;
}

/* Función que muestra el menú para el usuario*/
void menu(){
	cout<<"\n\t\t\t=== ARBOLES BALANCEADOS ==="<<endl<<endl;
	cout<<"\tInsertar nodo.........................................[1]"<<endl;
	cout<<"\tBorrar nodo...........................................[2]"<<endl;
	cout<<"\tBuscar nodo...........................................[3]"<<endl;
	cout<<"\tMostrar arbol.........................................[4]"<<endl;
	cout<<"\tMostrar recorridos (inorden, preorden, postorden).....[5]"<<endl;
	cout<<"\tSalir.................................................[6]"<<endl;
	cout<<"\n\tSeleccione una opcion: ";
}
