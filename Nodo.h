#ifndef Nodo_h_included
#define Nodo_h_included

class Nodo{
	private:
		int info; // el n�mero entero que va a tener el nodo
		int tipo; // 1->izquierdo, 2->derecho, 0->raiz
		int revision; // n�mero de veces que se ha pasado por un nodo al recorrer el �rbol
		Nodo izq; // enlace al hijo izquierdo
		Nodo der; // enlace al hijo derecho
		Nodo padre; // enlace al padre del nodo
		
	public:
		// Constructores
		Nodo(int info);
		
		// M�todos set()
		void setInfo(int dato);
		void setTipo(int t);	
		void setRevision(int rev);
		void setIzq(Nodo i);
		void setDer(Nodo d);
		void setPadre(Nodo p);
		
		// M�todos get()
		int getInfo();
		int getTipo();
		int getRevision();
		Nodo getDer();
		Nodo getIzq();
		Nodo getPadre();
};

#endif
