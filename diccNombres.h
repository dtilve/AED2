#include "aed2.h"
#include "Tipos.h"
#include "iostream"

using namespace aed2;
using namespace std;

class diccNombres
{
  public:

    diccNombres();

    void Definir(Nombre n, Posicion p);
    void Borrar(const Nombre n);
    Posicion Obtener(Nombre n);
    bool Definido(Nombre n);
    Conj<Nombre>::Iterador Claves();
    bool DiccVacio();

  private:

    struct info{
    	Posicion pos;
    	Conj<Nombre>::Iterador clave;

    	bool operator != (const info& i2) const{
            return (pos != i2.pos) || !(clave == i2.clave);
        }
    };

    struct Nodo{
    	Arreglo<Nodo*> alfabeto;
    	Conj<info>::Iterador* significado;
    	Nodo* anterior;
    	bool esNombre;
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
	Nodo* actual = this->_primero;
	Nat i;
	for(i = 0; i < n.length() && actual!= NULL; i++)
	{
		int indice = (int) n[i];
		actual =  actual->alfabeto[indice];
	}
	if (actual == NULL || actual->significado == NULL)
	{
		return false;
	}
	else return true;
}

void diccNombres::Definir(Nombre n, Posicion p){
	Nat i;
	Nodo* actual = this->_primero;
	Nat indice;
	if (!this->Definido(n))
	{
		Conj<Nombre>::Iterador itClaveNueva = this->_claves.AgregarRapido(n);
		info definicion;
		definicion.clave = itClaveNueva;
		definicion.pos = p;
		Conj<info>::Iterador itInfoNueva = this->_definiciones.AgregarRapido(definicion);

		Conj<info>::Iterador* infoPointer = &itInfoNueva;
		Nodo* proximo;

		for(i = 0; i < n.length(); i++)
		{
			indice = (int) n[i];
			if (actual->alfabeto[indice] == NULL)
			{
				proximo = new Nodo;
				actual->alfabeto[indice] = proximo;
				Arreglo<Nodo*> array;
				proximo->alfabeto = crearArregloVacio();
				proximo->anterior = actual;
				proximo->significado = NULL;
				if (i == n.length() - 1)
				{
					proximo->esNombre = true;
				}
				else
				{
					proximo->esNombre = false;
				}

				actual = proximo;
			}
			else
			{
				if (i == n.length() - 1)
				{
					proximo->esNombre = true;
				}
				else
				{
				int indice = (int) n[i];
				proximo = actual->alfabeto[indice];
				}
				actual = proximo;
			}
		}
		proximo = new Nodo;
		actual->alfabeto[indice] = proximo;
		Arreglo<Nodo*> array;
		proximo->alfabeto = crearArregloVacio();
		proximo->anterior = actual;
		proximo->significado = infoPointer;
		proximo->esNombre = false;
	}
	else
	{
		for(i = 0; i < n.length() ; i++)
		{
			Arreglo<Nodo*> array = actual->alfabeto;
			int indice = (int) n[i];
			actual = array[indice];
		}
		Conj<info>::Iterador itInfo = *actual->significado;
		info informacion= itInfo.Siguiente();
		informacion.pos = p;
	}
}


Posicion diccNombres::Obtener(Nombre n){
	Nodo* actual = this->_primero;
	Nat i = 0;
	for(i = 0; i <= n.length(); i++)
	{
		Arreglo<Nodo*> array = actual->alfabeto;
		int indice = (int) n[i];
		actual = array[indice];
	}
	Conj<info>::Iterador itInfo = *actual->significado;
	return itInfo.Siguiente().pos;
}

void diccNombres::Borrar(const Nombre n){
	Nodo* actual = this->_primero;
	Nodo* proximo;
	Nat i;
	for (i = 0; i < n.length(); i++)
	{
		int indice = (int) n[i];
		Arreglo<Nodo*> array = actual->alfabeto;
		proximo = array[indice];
		actual = proximo;
	}
	Conj<info>::Iterador itI = *actual->significado;
	Conj<Nombre>::Iterador itK = itI.Siguiente().clave;
	itK.EliminarSiguiente();
	itI.EliminarSiguiente();
	actual->significado = NULL;
	actual->anterior = NULL;
	for (i = 0; i < n.length(); i++)
	{
		int indice = (int) n[i];
		Arreglo<Nodo*> array = actual->alfabeto;
		proximo = array[indice];
		actual = proximo;
	}
	if (esArregloDeNULL(actual->alfabeto))
	{
		for (i = n.length() -1; 0 <= i && !actual->esNombre; i--)
		{
			Arreglo<Nodo*> array = actual->alfabeto;
			int indice = (int) n[i];
			array[indice] = NULL;
			Nodo* previo;
			previo = actual->anterior;
			delete actual;
			actual = previo;
		}
	}
	else actual->esNombre = false;
}

Conj<Nombre>::Iterador diccNombres::Claves(){
	return this->_claves.CrearIt();
}

bool diccNombres::DiccVacio(){
	return this->_claves.EsVacio();
}


