#include "Conj.h"
#include "TiposBasicos.h"
#include "Tipos.h"
#include "ArregloDimensionable.h"

using namespace aed2;

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
    };

    struct Nodo{
    	ArregloDimensionable<Nodo*> alfabeto;
    	Conj<info>::Iterador* significado;
    	Nodo* anterior;
    	bool esNombre;
    };

  Conj<Nombre> _claves;
  Conj<info> _definiciones;
  Nodo* _primero;
};

// definicion del diccionario

diccNombres::diccNombres(){
	this->_claves = Conj<Nombre>();
	this->_definiciones = Conj<info>();

	Nodo* node = new Nodo;
	ArregloDimensionable<Nodo*> array;
	node->alfabeto = array.crearArregloDimensionableVacio(256);
	node->significado = NULL;
	node->anterior = NULL;
	node->esNombre = false;

	this->_primero = node;
}

bool diccNombres::Definido(Nombre n){
	Nodo* actual = this->_primero;
	int i;
	for(i = 0; i < n.length() && actual!= NULL; i++)
	{
		int indice = (int) n[i];
		actual =  actual->alfabeto.iesimo(indice);
	}
	if (actual == NULL || actual->significado == NULL)
	{
		return false;
	}
	else return true;
}

void diccNombres::Definir(Nombre n, Posicion p){
	int i;
	Nodo* actual = this->_primero;
	int indice;
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
			if (actual->alfabeto.iesimo(indice) == NULL)
			{
				proximo = new Nodo;
				actual->alfabeto.iesimo(indice) = proximo;
				ArregloDimensionable<Nodo*> array;
				proximo->alfabeto = array.crearArregloDimensionableVacio(256);
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
				proximo = actual->alfabeto.iesimo(indice);
				}
				actual = proximo;
			}
		}
		proximo = new Nodo;
		actual->alfabeto.iesimo(indice) = proximo;
		ArregloDimensionable<Nodo*> array;
		proximo->alfabeto = array.crearArregloDimensionableVacio(256);
		proximo->anterior = actual;
		proximo->significado = infoPointer;
		proximo->esNombre = false;
	}
	else
	{
		for(i = 0; i < n.length() ; i++)
		{
			ArregloDimensionable<Nodo*> array = actual->alfabeto;
			int indice = (int) n[i];
			actual = array.iesimo(indice);
		}
		Conj<info>::Iterador itInfo = *actual->significado;
		info informacion= itInfo.Siguiente();
		informacion.pos = p;
	}
}


Posicion diccNombres::Obtener(Nombre n){
	Nodo* actual = this->_primero;
	int i = 0;
	for(i = 0; i <= n.length(); i++)
	{
		ArregloDimensionable<Nodo*> array = actual->alfabeto;
		int indice = (int) n[i];
		actual = array.iesimo(indice);
	}
	Conj<info>::Iterador itInfo = *actual->significado;
	return itInfo.Siguiente().pos;
}

void diccNombres::Borrar(const Nombre n){
	Nodo* actual = this->_primero;
	Nodo* proximo;
	int i;
	for (i = 0; i < n.length(); i++)
	{
		int indice = (int) n[i];
		ArregloDimensionable<Nodo*> array = actual->alfabeto;
		proximo = array.iesimo(indice);
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
		ArregloDimensionable<Nodo*> array = actual->alfabeto;
		proximo = array.iesimo(indice);
		actual = proximo;
	}
	if (actual->alfabeto.esArregloDeNULL())
	{
		for (i = n.length() -1; 0 <= i && !actual->esNombre; i--)
		{
			ArregloDimensionable<Nodo*> array = actual->alfabeto;
			int indice = (int) n[i];
			array.iesimo(indice) = NULL;
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


