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
    Posicion Obtener(Nombre n)  const;
    bool Definido(Nombre n) const;
    const Conj<Nombre>::const_Iterador Claves() const;
    bool DiccVacio();

    Conj<Posicion> Significados() const;

  private:

    struct info{
    	Posicion pos;
    	Conj<Nombre>::Iterador clave;

    	bool operator != (const info& i2) const{
            return (pos != i2.pos) || !(clave == i2.clave);
        }

        info(){

        };
        ~info()
        {

        };
    };

    struct Nodo{
    	Arreglo<Nodo*> alfabeto;
    	Conj<info>::Iterador* significado;
    	Nodo* anterior;
    	bool esNombre;

    	Nodo(){

        };
        ~Nodo()
        {

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

bool diccNombres::Definido(Nombre n) const{


	Nat i = 0;
	int indice = (int) n[i];
	Nodo* actual = this->_primero;
	//actual = actual->alfabeto[indice];

	for(i = 0; (i < n.length()) && (actual->alfabeto[indice] != NULL); i++)
	{


		actual =  actual->alfabeto[indice];
		indice = (int) n[i+1];


	}

	if(i < n.length() || (i==n.length() && actual->significado==NULL))
	{

		return false;
	}
	else
	{

		return true;
	}
}

Conj<Nombre>::const_Iterador diccNombres::Definir(Nombre n, Posicion p){

	Nat i;
	Nodo* actual = this->_primero;
	Nat indice;
	Conj<Nombre>::const_Iterador itRet;
	if (!this->Definido(n))
	{
		Conj<Nombre>::Iterador* itClaveNuevaPointer = new Conj<Nombre>::Iterador;
		*itClaveNuevaPointer = this->_claves.AgregarRapido(n);
		info* definicion = new info;
		definicion->clave = (*itClaveNuevaPointer);
		definicion->pos = p;

		Conj<info>::Iterador* itInfoPointer = new Conj<info>::Iterador;
		*itInfoPointer = this->_definiciones.AgregarRapido(*definicion);



		for(i = 0; i < n.length(); i++)
		{
		    Nodo* proximo;
			indice = (int) n[i];
			if (actual->alfabeto[indice] == NULL)
			{

				proximo = new Nodo;
				proximo->alfabeto = crearArregloVacio();
				proximo->anterior = actual;
				proximo->esNombre = false;
				proximo->significado = NULL;
				actual->alfabeto[indice] = proximo;

				if (i == n.length() - 1)
				{

					proximo->significado = itInfoPointer;


					actual->esNombre = true;
				}

				actual = proximo;
			}
			else
			{
				if (i == n.length() - 1)
				{

					actual->esNombre = true;
					proximo->significado = itInfoPointer;

				}
				else
				{

					proximo = actual->alfabeto[indice];
				}
				actual = proximo;
			}
		}
		itRet = *itClaveNuevaPointer;
	}
	else
	{
		for(i = 0; i < n.length(); i++)
		{

			int indice = (int) n[i];
			actual = actual->alfabeto[indice];
		}

		Conj<Nombre>::Iterador laClave = (*actual->significado).Siguiente().clave;
		info informacion;
		informacion.clave = laClave;
		informacion.pos = p;
		(*actual->significado).EliminarSiguiente();
		Conj<info>::Iterador* itInfoPointer = new Conj<info>::Iterador;
		*itInfoPointer = _definiciones.AgregarRapido(informacion);
		actual->significado = itInfoPointer;
        itRet = (*itInfoPointer).Siguiente().clave;
	}
	return itRet;
}


 Posicion  diccNombres::Obtener(Nombre n) const{

	Nodo* actual = this->_primero;
	int indice;
	Nat i = 0;
	for(i = 0; i < n.length(); i++)
	{
		indice = (int) n[i];
		actual = actual->alfabeto[indice];

	}
	return (*actual->significado).Siguiente().pos;
}

void diccNombres::Borrar(const Nombre n){
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

	Conj<Nombre>::Iterador itK = itI.Siguiente().clave;
	itK.EliminarSiguiente();
	itI.EliminarSiguiente();

	actual->significado = NULL;
	//actual->anterior = NULL;


	actual = this->_primero;
	for (i = 0; i < n.length()-1; i++)
	{
		indice = (int) n[i];
		actual = actual->alfabeto[indice];
	}

	actual->esNombre = false;

	indice = (int) n[i];
    actual = actual->alfabeto[indice];

	if (esArregloDeNULL(actual->alfabeto))
	{

		for (i = n.length() -1; 0 < i && !actual->esNombre; i--)
		{
			indice = (int) n[i];
			actual->alfabeto[indice] = NULL;

			proximo = actual->anterior;
			delete actual->significado;
			delete actual;

			actual = proximo;
		}
	}
	else
	{

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

Conj<Posicion> diccNombres::Significados() const{
    Conj<Posicion> res;
    Conj<info>::const_Iterador it = _definiciones.CrearIt();
    while(it.HaySiguiente()){
        res.AgregarRapido(it.Siguiente().pos);
        it.Avanzar();
    }
    return res;
}

