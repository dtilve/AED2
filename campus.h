#ifndef AED2_CAMPUS_H_
#define AED2_CAMPUS_H_

#include <ostream>
#include "TiposBasicos.h"

namespace aed2
{
	class Campus{
		public:
			//devuelve el campus
			Campus();//<<<<------------------------------------------------------------------- Faltan parametros

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
			struct Grilla{
    			vector<vector<bool>> matriz;
    			nat filas;
    			nat columnas;
    		};

	};
}
