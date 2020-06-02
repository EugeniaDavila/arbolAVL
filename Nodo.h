#ifndef Nodo_h_included
#define Nodo_h_included

class Nodo{
	private:
		int info; // el número entero que va a tener el nodo
		int tipo; // 1->izquierdo, 2->derecho, 0->raiz
		int revision; // número de veces que se ha pasado por un nodo al recorrer el árbol
		Nodo *izq; // enlace al hijo izquierdo
		Nodo *der; // enlace al hijo derecho
		Nodo *padre; // enlace al padre del nodo
		
	public:
		// Constructores
		Nodo(int info,int type);
		
		// Métodos set()
		void setInfo(int dato);
		void setTipo(int t);	
		void setRevision(int rev);
		void setIzq(Nodo i);
		void setDer(Nodo d);
		void setPadre(Nodo p);
		
		// Métodos get()
		int getInfo();
		int getTipo();
		int getRevision();
		Nodo getDer();
		Nodo getIzq();
		Nodo getPadre();
		
		// Métodos generales
		Nodo* insertarNodo(int info,struct Nodo *raiz);
		Nodo* borrarNodo(int info,struct Nodo *raiz);
		void preorden(struct Nodo *raiz);
		void inorden(struct Nodo *raiz);
		void postorden(struct Nodo *raiz);
		void buscarNodo(int n,struct Nodo *raiz);
		void mostrarArbol(struct Nodo *raiz);
			
};

#endif
