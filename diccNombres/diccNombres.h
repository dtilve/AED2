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
	ArregloDimensionable<Nodo*> array = ArregloDimensionable<Nodo*>(256);
	node->alfabeto.operator =(array) ;
	node->significado = NULL;
	node->anterior = NULL;
	node->esNombre = false;
	this->_primero = node;
}

bool diccNombres::Definido(Nombre n){
	Nodo* actual = this->_primero;
	int j = 0;
	int i = 0;
	for(i = 0 ; i <= n.length() && actual != NULL; i++)
	{
		ArregloDimensionable<Nodo*> array = actual->alfabeto;
		int index = (int) n[i];
		actual = array.iesimo(index);
		j++;
	}
	if (actual->significado == NULL)
	{
		return true;
	}
	else return false;
}

void diccNombres::Definir(Nombre n, Posicion p){
	if (not(this->Definido(n)))
	{
		Conj<Nombre>::Iterador itClaveNueva = this->_claves.AgregarRapido(n);
		info definicion;
		definicion.clave = itClaveNueva;
		definicion.pos = p;
		Conj<info>::Iterador itInfoNueva = this->_definiciones.AgregarRapido(definicion);

		Conj<info>::Iterador* infoPointer = &itInfoNueva;
		Nodo* actual = this->_primero;
		Nodo* proximo = new Nodo;

		int i = 0;
		for(i = 0; i <= n.length(); i++)
		{
			Nodo* actualPointer = actual;
			if (i == n.length())
			{
				proximo->alfabeto = ArregloDimensionable<Nodo*>(256);
				proximo->anterior = actualPointer;
				proximo->significado = infoPointer;
				proximo->esNombre = false;
			}
			else
			{
				if (i == n.length() - 1)
				{
					proximo->alfabeto = ArregloDimensionable<Nodo*>(256);
					proximo->anterior = NULL;
					proximo->significado = infoPointer;
					proximo->esNombre = true;
				}
				else
				{
					proximo->alfabeto = ArregloDimensionable<Nodo*>(256);
					proximo->anterior = NULL;
					proximo->significado = infoPointer;
					proximo->esNombre = false;
				}
			}
			ArregloDimensionable<Nodo*> array = actual->alfabeto;
			int index = (int) n[i];
			array.iesimo(index) = proximo;
			actual = proximo;
		}
		for(i = 0; i <= n.length() ; i++)
		{
			ArregloDimensionable<Nodo*> array = actual->alfabeto;
			int index = (int) n[i];
			actual = array.iesimo(index);
		}
		Conj<info>::Iterador itInfo = *actual->significado;
		info informacion= itInfo.Siguiente();
		informacion.pos = p;
	}
}

void Borrar(const Nombre n);
Posicion diccNombres::Obtener(Nombre n){
	Nodo* actual = this->_primero;
	int i = 0;
	for(i = 0; i <= n.length(); i++)
	{
		ArregloDimensionable<Nodo*> array = actual->alfabeto;
		int index = (int) n[i];
		actual = array.iesimo(index);
	}
	Conj<info>::Iterador itInfo = *actual->significado;
	return itInfo.Siguiente().pos;
}

Conj<Nombre>::Iterador diccNombres::Claves(){
	return this->_claves.CrearIt();
}

bool diccNombres::DiccVacio(){
	return this->_claves.EsVacio();
}



