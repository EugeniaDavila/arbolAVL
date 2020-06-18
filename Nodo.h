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
		int alturaIzq;
		int alturaDer;
		
	public:
		// Constructores
		Nodo ();
		Nodo(int dato,int type);
		Nodo(int dato);
		
		// Métodos set()
		void setInfo(int dato);
		void setTipo(int t);	
		void setRevision(int rev);
		void setIzq(Nodo *i);
		void setDer(Nodo *d);
		void setPadre(Nodo *p);
		void setAlturaIzq(int i);
		void setAlturaDer(int d);
		
		// Métodos get()
		int getInfo();
		int getTipo();
		int getRevision();
		Nodo* getDer();
		Nodo* getIzq();
		Nodo* getPadre();
		int getAlturaIzq();
		int getAlturaDer();			
};

#endif
