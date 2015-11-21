#ifndef CAMPUS_H_
#define CAMPUS_H_

#include <ostream>
#include "TiposBasicos.h"

namespace aed2
{
	class Campus{
		public:
			//devuelve el campus
			Campus(Nat ancho, Nat alto);
			
			//Destructor
			~Campus();

			//Agrega un obstaculo al campus en una posicion valida y desocupada
			//Pre: p es una posicion valida y no esta ocupada
			void AgregarObstaculo(Posicion p, Campus& c);

			//Devuelve la cantidad de filas que tiene el campus
			Nat Filas(const Campus& c);

			//Devuelve la cantidad de columnas que tiene el campus.
			Nat Columnas(const Campus& c);

			//Chequea si la posicion p esta ocupada.
			//Pre: p es una posicion valida de p
			bool EstaOcupada(Posicion p, const Campus& c);

			//Chequea si p pertenece a las posiciones del campus.
			bool posValida(Posicion p, const Campus& c);

			//Chequea si p es una opcion de ingreso para un hippie o un estudiante. 
			//Esa posicion debe estar vacia y en la primera o ultima fila.
			bool EsIngreso(Posicion p, const Campus& c);

			//Chequea si la posicion de ingreso pertenece a la fila superior.
			bool IngresoSuperior(Posicion p, const Campus& c);

			//Chequea si la posicion de ingreso pertenece a la fila inferior.
			bool IngresoInferior(Posicion p, const Campus& c);

			//Devuelve el conjunto de vecinos de p, si es una posicion valida. Son como maximo 4 elementos.
			//Si no hay vecinos devuelve el conjunto vacio.
			//Pre: p debe ser una posicion valida.
			Conj<Posicion> Vecinos(Posicion p, const Campus& c);

			//Devuelve la distancia que hay entre p1 y p2.
			//Pre: tanto p1 como p2 deben ser posiciones validas.
			Nat Distancia(Posicion p1, Posicion p2, const campus& c);

			//Devuelve la proxima posicion que deberia tomar un elemento. No hace distincion en para que tipo
			//se utilizara esta funcion. Seran datos a interpretar por el invocador.
			//Pre: p debe ser una posicion valida.
			Posicion ProxPosicion(Posicion p, Direccion d, const Campus& c);

			//Devuelve el conjunto de posiciones libres del ingreso que esta mas cerca de p. si no hay posiciones
			//libres en el mas cercano, devuelve el otro conjunto.
			//Pre: p debe ser una posicion valida.
			Conj<Posicion> IngresosMasCercanos(Posicion p, const Campus& c);

		private:
		vector<vector<bool>> matriz;
    		Nat filas;
    		Nat columnas;

    		struct Posicion{
    			Nat x;
    			Nat y;
    		};

	};

	Campus::Campus(Nat ancho, Nat alto) : columnas(ancho), filas(alto) {}

	//Agrega un obstaculo al campus en una posicion valida y desocupada
	//Pre: p es una posicion valida y no esta ocupada
	void Campus::AgregarObstaculo(Posicion p, Campus& c){
		c.matriz[p.x -1][p.y -1] = true;
	}

	//Devuelve la cantidad de filas que tiene el campus
	Nat Campus::Filas(const Campus& c){
		return c.filas;
	}

	//Devuelve la cantidad de columnas que tiene el campus.
	Nat Campus::Columnas(const Campus& c){
		return c.columnas;
	}

	//Chequea si la posicion p esta ocupada.
	//Pre: p es una posicion valida de p
	bool Campus::EstaOcupada(Posicion p, const Campus& c){
		return (c.matriz[p.x -1][p.y -1] == true);
	}

	//Chequea si p pertenece a las posiciones del campus.
	bool Campus::posValida(Posicion p, const Campus& c){
		bool valida = false;
		if (p.x > 0 && p.y>0)
		if ((p.y <= c.filas) && (p.x <= c.columnas))
		valida = true;
		return valida; 
	}

	//Chequea si p es una opcion de ingreso para un hippie o un estudiante. 
	//Esa posicion debe estar vacia y en la primera o ultima fila.
	bool Campus::EsIngreso(Posicion p, const Campus& c){ 
		return (c.IngresoSuperior(p,c)||c.IngresoInferior(p,c));
	}

	//Chequea si la posicion de ingreso pertenece a la fila superior.
	bool Campus::IngresoSuperior(Posicion p, const Campus& c){
		return ((p.y=1)&&(c.matriz[p.x -1][p.y-1] == false));
	}

	//Chequea si la posicion de ingreso pertenece a la fila inferior.
	bool Campus::IngresoInferior(Posicion p, const Campus& c){
		return ((p.y = c.filas)&&(c.matriz[p.x -1][p.y-1] == false));
	}

	//Devuelve el conjunto de vecinos de p, si es una posicion valida. Son como maximo 4 elementos.
	//Si no hay vecinos devuelve el conjunto vacio.
	//Pre: p debe ser una posicion valida.
	Conj<Posicion> Campus::Vecinos(Posicion p, const Campus& c){

	}

	//Devuelve la distancia que hay entre p1 y p2.
	//Pre: tanto p1 como p2 deben ser posiciones validas.
	Nat Campus::Distancia(Posicion p1, Posicion p2, const campus& c){

	}

	//Devuelve la proxima posicion que deberia tomar un elemento. No hace distincion en para que tipo
	//se utilizara esta funcion. Seran datos a interpretar por el invocador.
	//Pre: p debe ser una posicion valida.
	Posicion Campus::ProxPosicion(Posicion p, Direccion d, const Campus& c){
		Posicion paux;
		paux=p;
		if ( ( (d==izq)&&(p.x==1) )||( (d==der)&&(p.x==c.columnas) )||( (d==abajo)&&(p.y==c.filas) )||( (d==arriba)&&(p.y==1) ))
				paux = p;
		else
		{
			if (d==izq) paux.x=paux.x-1;
			if (d==der) paux.x=paux.x+1;
			if (d==abajo) paux.y=paux.y+1;
			if (d==arriba) paux.y=paux.y-1;
		}
		return paux;

	}

	//Devuelve el conjunto de posiciones libres del ingreso que esta mas cerca de p. si no hay posiciones
	//libres en el mas cercano, devuelve el otro conjunto.
	//Pre: p debe ser una posicion valida.
	Conj<Posicion> Campus::IngresosMasCercanos(Posicion p, const Campus& c){

	}
	
}
#endif // CAMPUS_H_
