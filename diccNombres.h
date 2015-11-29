#include "aed2.h"
#include "Tipos.h"
#include "iostream"

using namespace aed2;
using namespace std;

class diccNombres
{
  public:

    diccNombres();

    Conj<Nombre>::const_Iterador Definir(Nombre n, Posicion p);
    void Borrar(const Nombre n);
     Posicion Obtener(Nombre n) ;
    bool Definido(Nombre n);
    const Conj<Nombre>::const_Iterador diccNombres::Claves() const;
    bool DiccVacio();

    Conj<Posicion> Significados();

  private:

    struct info{
    	Posicion pos;
    	Conj<Nombre>::Iterador clave;

    	bool operator != (const info& i2) const{
            return (pos != i2.pos) || !(clave == i2.clave);
        }

        info(){
        	cout << "Creamos info: " << this << endl;
        };
        ~info()
        {
        	cout << "Destruimos info: "<< this << endl;
        };
    };

    struct Nodo{
    	Arreglo<Nodo*> alfabeto;
    	Conj<info>::Iterador* significado;
    	Nodo* anterior;
    	bool esNombre;

    	Nodo(){
        	cout << "Creamos nodo: " << this << endl;
        };
        ~Nodo()
        {
        	cout << "Destruimos nodo: "<< this << endl;
        };
    };

  Conj<Nombre> _claves;
  Conj<info> _definiciones;
  Nodo* _primero;

  Arreglo<Nodo*> crearArregloVacio(){
	Arreglo<Nodo*> a(256);
	for( Nat i = 0; i < 256; i++ ){
		a.Definir(i,NULL);
	}
	return a;
}

  bool esArregloDeNULL(Arreglo<Nodo*> a){
	Nat i = 0;
	while(i < a.Tamanho() && a[i] == NULL)
		i++;
	return i == a.Tamanho();
}

};


// definicion del diccionario

diccNombres::diccNombres(){
	this->_claves = Conj<Nombre>();
	this->_definiciones = Conj<info>();

	Nodo* node = new Nodo;
	Arreglo<Nodo*> a;
	node->alfabeto = crearArregloVacio();
	node->significado = NULL;
	node->anterior = NULL;
	node->esNombre = false;

	this->_primero = node;
}

bool diccNombres::Definido(Nombre n){
	cout << n << " esta definido?" << endl;
	cout << "Longitud de n es " << n.length() << endl;
	Nat i = 0;
	int indice = (int) n[i];
	Nodo* actual = this->_primero;
	//actual = actual->alfabeto[indice];

	for(i = 0; (i < n.length()) && (actual->alfabeto[indice] != NULL); i++)
	{
		cout << "La letra es " << n[i] << endl;
		cout << "El valor de i es " << i << endl;
		actual =  actual->alfabeto[indice];
		indice = (int) n[i+1];
		cout << "Es null la posición de la letra? " << (actual->alfabeto[indice] == NULL) << endl;
		cout << "Es null su anterior? " << (actual->anterior == NULL) << endl;
	}
	
	if(i < n.length() || (i==n.length() && actual->significado==NULL))
	{
		cout << "No está definido" << endl;
		return false;
	}
	else
	{	
		cout << "Está definido" << endl;
		return true;	
	}
}

Conj<Nombre>::const_Iterador diccNombres::Definir(Nombre n, Posicion p){
	cout << "Definiendo nombre: " << n << endl;
	Nat i;
	Nodo* actual = this->_primero;
	Nat indice;
	if (!this->Definido(n))
	{	
		cout << "No está definido para Definir" << endl;

		Conj<Nombre>::Iterador* itClaveNuevaPointer = new Conj<Nombre>::Iterador;
		*itClaveNuevaPointer = this->_claves.AgregarRapido(n);
		info* definicion = new info;
		definicion->clave = (*itClaveNuevaPointer);
		definicion->pos = p;

		Conj<info>::Iterador* itInfoPointer = new Conj<info>::Iterador;
		*itInfoPointer = this->_definiciones.AgregarRapido(*definicion);
		
		Nodo* proximo;

		for(i = 0; i < n.length(); i++)
		{
			cout << "i en este momento vale " << i << endl;
			indice = (int) n[i];
			cout << "Letra actual: " << n[i] << endl; 

			cout << "El nodo previo es NULL? " << (actual->anterior == NULL) << endl;
			if (actual->alfabeto[indice] == NULL)
			{
				cout << "Como la letra no tiene nodo siguiente tengo que crear un nuevo nodo" << endl;
				proximo = new Nodo;
				proximo->alfabeto = crearArregloVacio();
				proximo->anterior = actual;
				proximo->esNombre = false;
				proximo->significado = NULL;
				actual->alfabeto[indice] = proximo;

				if (i == n.length() - 1)
				{
				cout << "Ya llegue al final del nombre" << endl;
					proximo->significado = itInfoPointer;
					cout << "El significado asignado fue: " << (*itInfoPointer).Siguiente().pos << endl;
					cout << itInfoPointer << endl;
					actual->esNombre = true;
				}

				actual = proximo;
			}
			else
			{
				if (i == n.length() - 1)
				{
				cout << "Ya llegue al final del nombre" << endl;					
					actual->esNombre = true;
					proximo->significado = itInfoPointer;
					cout << "El significado asignado fue: " << (*itInfoPointer).Siguiente().pos << endl;
				}
				else
				{
				cout << "Aun no llegue al final del nombre; sigo avanzando." << endl;
					proximo = actual->alfabeto[indice];
				}
				actual = proximo;
			}
		}
	}
	else
	{
		for(i = 0; i < n.length(); i++)
		{
			cout << "El valor de i es " << i << endl;
			int indice = (int) n[i];
			actual = actual->alfabeto[indice];
		}
		cout << "Reasigno definicion y elimino anterior" << endl;
		Conj<Nombre>::Iterador laClave = (*actual->significado).Siguiente().clave;
		info informacion;
		informacion.clave = laClave;
		informacion.pos = p;
		(*actual->significado).EliminarSiguiente();
		Conj<info>::Iterador* itInfoPointer = new Conj<info>::Iterador;
		*itInfoPointer = _definiciones.AgregarRapido(informacion);
		actual->significado = itInfoPointer;
		cout << "El significado asignado fue: " << (*itInfoPointer).Siguiente().pos << endl;
	}
	cout << endl << endl;
	Conj<Nombre>::const_Iterador itRet(itClaveNueva);
	return itRet;
}


 Posicion  diccNombres::Obtener(Nombre n){
	cout << "Definido?" << (Definido(n) == true) << endl;
	Nodo* actual = this->_primero;
	int indice;
	Nat i = 0;
	for(i = 0; i < n.length(); i++)
	{
		indice = (int) n[i];
		actual = actual->alfabeto[indice];
		cout << "Letra actual: " << n[i] << endl;
	}
	cout << "Actual es NULL? " << (actual == NULL) << endl;
	cout << "Siguiente: " << (*actual->significado).HaySiguiente() << endl;
	//cout << actual->significado << endl;
	//cout << (*actual->significado).Siguiente().pos << endl;
	return (*actual->significado).Siguiente().pos;
}

void diccNombres::Borrar(const Nombre n){
	cout << "Eliminando nombre: " << n << endl;
	Nodo* actual = this->_primero;
	Nodo* proximo;
	Nat i;
	int indice;
	for (i = 0; i < n.length(); i++)
	{
		indice = (int) n[i];
		proximo = actual->alfabeto[indice];
		actual = proximo;
	}
	Conj<info>::Iterador itI = *actual->significado;
	//	cout << "Se crea iterador de informacion cuyo siguiente es el nombre " << (itI.Siguiente().clave).Siguiente() << " con significado "<< itI.Siguiente().pos << endl;
	Conj<Nombre>::Iterador itK = itI.Siguiente().clave;
	itK.EliminarSiguiente();
	itI.EliminarSiguiente();
	//cout << "Se eliminan los siguientes, el nuevo siguiente es el nombre " << (itI.Siguiente().clave).Siguiente() << " con significado "<< itI.Siguiente().pos << endl;
	actual->significado = NULL;
	actual->anterior = NULL;
	cout << "Bajé la primera vez para borrar de los conjuntos, bajo nuevamente hasta la última letra" << endl;
	
	actual = this->_primero;
	for (i = 0; i < n.length(); i++)
	{
		cout << "Letra actual: " << n[i] << endl;
		indice = (int) n[i];
		actual = actual->alfabeto[indice];
		cout << "El nodo previo es NULL? " << (actual->anterior == NULL) << endl;
	}
	cout << "Terminé de bajar la segunda vez" << endl;
	if (esArregloDeNULL(actual->alfabeto))
	{
		cout << "El nodo actual está vacío" << endl;
		for (i = n.length() -1; 0 < i && !actual->esNombre; i--)
		{
			cout << "El nodo actual no es prefijo de ningún nombre" << endl;
			indice = (int) n[i];
			actual->alfabeto[indice] = NULL;
			cout << "Letra actual: " << n[i] << endl;
			cout << "Delete significado +  actual" << endl;
			proximo = actual->anterior;
			delete actual->significado;
			delete actual;			
			cout << "El nodo previo es NULL? " << (proximo == NULL) << endl;
			actual = proximo;
			cout << "Asignacion done" << endl;
		}
	}
	else 
	{
		cout << "El nombre era prefijo pero como lo borré ya no lo es" << endl;
		actual->esNombre = false;
		delete actual->significado;
	}
}

const Conj<Nombre>::const_Iterador diccNombres::Claves() const{
	return this->_claves.CrearIt();
}

bool diccNombres::DiccVacio(){
	return this->_claves.EsVacio();
}

Conj<Posicion> diccNombres::Significados(){
    Conj<Posicion> res;
    Conj<info>::Iterador it = _definiciones.CrearIt();
    while(it.HaySiguiente()){
        res.AgregarRapido(it.Siguiente().pos);
        it.Avanzar();
    }
    return res;
}

