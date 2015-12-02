#ifndef CAMPUS_H_
#define CAMPUS_H_

#include <ostream>
#include <cassert>
#include "aed2.h"
#include "Tipos.h"

namespace aed2
{
	class Campus{
		public:

            //Constructor por defecto
		    Campus();
		    
		    ~Campus();

			//devuelve el campus
			Campus(const Nat ancho, const Nat alto);

			//Agrega un obstaculo al campus en una posicion valida y desocupada
			//Pre: p es una posicion valida y no esta ocupada
			void AgregarObstaculo(Posicion p);

			//Devuelve la cantidad de filas que tiene el campus
			Nat Filas() const;

			//Devuelve la cantidad de columnas que tiene el campus.
			Nat Columnas() const;

			//Chequea si la posicion p esta ocupada.
			//Pre: p es una posicion valida de p
			bool EstaOcupada(Posicion p) const;

			//Chequea si p pertenece a las posiciones del campus.
			bool posValida(Posicion p) const;

			//Chequea si p es una opcion de ingreso para un hippie o un estudiante.
			//Esa posicion debe estar vacia y en la primera o ultima fila.
			bool EsIngreso(Posicion p) const;

			//Chequea si la posicion de ingreso pertenece a la fila superior.
			bool IngresoSuperior(Posicion p) const;

			//Chequea si la posicion de ingreso pertenece a la fila inferior.
			bool IngresoInferior(Posicion p) const;

			//Devuelve el conjunto de vecinos de p, si es una posicion valida. Son como maximo 4 elementos.
			//Si no hay vecinos devuelve el conjunto vacio.
			//Pre: p debe ser una posicion valida.
			Conj<Posicion> Vecinos(Posicion p) const;

			//Devuelve la distancia que hay entre p1 y p2.
			//Pre: tanto p1 como p2 deben ser posiciones validas.
			Nat Distancia(Posicion p1, Posicion p2) const;

			//Devuelve la proxima posicion que deberia tomar un elemento. No hace distincion en para que tipo
			//se utilizara esta funcion. Seran datos a interpretar por el invocador.
			//Pre: p debe ser una posicion valida.
			Posicion ProxPosicion(Posicion p, Direccion d) const;

			//Devuelve el conjunto de posiciones libres del ingreso que esta mas cerca de p. si no hay posiciones
			//libres en el mas cercano, devuelve el otro conjunto.
			//Pre: p debe ser una posicion valida.
			Conj<Posicion> IngresosMasCercanos(Posicion p) const;

		private:
            Vector< Vector<bool> > matriz;
    		Nat filas;
    		Nat columnas;

	};

    Campus::Campus(){
        Campus(1,1);
    }

	Campus::~Campus(){
            Nat i = columnas;
	    while(i > 0){
            	Nat j = filas;
            
            	while(j > 0){
                	matriz[i-1].Eliminar(j-1);
                	j--;
            	}
            	matriz.Eliminar(i);
            	i--;
	    }
       }

	Campus::Campus(const Nat ancho, const Nat alto){
	    Nat i = 0;
	    while(i < ancho){
            Nat j = 0;
            Vector<bool> v;
            matriz.AgregarAtras(v);
            while(j < alto){
                matriz[i].AgregarAtras(false);
                j++;
            }
            i++;
	    }
	    columnas = ancho;
	    filas = alto;
	}

	//Agrega un obstaculo al campus en una posicion valida y desocupada
	//Pre: p es una posicion valida y no esta ocupada
	void Campus::AgregarObstaculo(Posicion p){
		matriz[p.x -1][p.y -1] = true;
	}

	//Devuelve la cantidad de filas que tiene el campus
	Nat Campus::Filas() const{
		return filas;
	}

	//Devuelve la cantidad de columnas que tiene el campus.
	Nat Campus::Columnas() const{
		return columnas;
	}

	//Chequea si la posicion p esta ocupada.
	//Pre: p es una posicion valida de p
	bool Campus::EstaOcupada(Posicion p) const{
        assert(posValida(p));
		return (matriz[p.x-1][p.y-1] == true);
	}

	//Chequea si p pertenece a las posiciones del campus.
	bool Campus::posValida(Posicion p) const{
		return 0 < p.x && p.x <= columnas && 0 < p.y && p.y <= filas;
	}

	//Chequea si p es una opcion de ingreso para un hippie o un estudiante.
	//Esa posicion debe estar vacia y en la primera o ultima fila.
	bool Campus::EsIngreso(Posicion p) const{
		return (IngresoSuperior(p) || IngresoInferior(p));
	}

	//Chequea si la posicion de ingreso pertenece a la fila superior.
	bool Campus::IngresoSuperior(Posicion p) const{
		return p.y == 1;
	}

	//Chequea si la posicion de ingreso pertenece a la fila inferior.
	bool Campus::IngresoInferior(Posicion p) const{
		return p.y == filas;
	}

	//Devuelve el conjunto de vecinos de p, si es una posicion valida. Son como maximo 4 elementos.
	//Si no hay vecinos devuelve el conjunto vacio.
	//Pre: p debe ser una posicion valida.
	Conj<Posicion> Campus::Vecinos(Posicion p) const{
        Conj<Posicion> res;
        if (posValida(Posicion(p.x,p.y-1)))
            res.Agregar(Posicion(p.x,p.y-1));
        if (posValida(Posicion(p.x+1,p.y)))
            res.Agregar(Posicion(p.x+1,p.y));
        if (posValida(Posicion(p.x,p.y+1)))
            res.Agregar(Posicion(p.x,p.y+1));
        if (posValida(Posicion(p.x-1,p.y)))
            res.Agregar(Posicion(p.x-1,p.y));
        return res;
	}

	//Devuelve la distancia que hay entre p1 y p2.
	Nat Campus::Distancia(Posicion p1, Posicion p2) const{
		Nat dist;
		if (p1.x>p2.x) dist= p1.x-p2.x;
			else dist=p2.x-p1.x;
		if (p1.y>p2.y) dist = dist +(p1.y-p2.y);
			else dist= dist + (p2.y-p1.y);
		return dist;
	}

	//Devuelve la proxima posicion que deberia tomar un elemento. No hace distincion en para que tipo
	//se utilizara esta funcion. Seran datos a interpretar por el invocador.
	//Pre: p debe ser una posicion valida.
	Posicion Campus::ProxPosicion(Posicion p, Direccion d) const{
		Posicion res;
		if (d==izq) res = Posicion(p.x-1,p.y);
		if (d==der) res = Posicion(p.x+1,p.y);
        if (d==arriba) res = Posicion(p.x,p.y-1);
		if (d==abajo) res = Posicion(p.x,p.y+1);
		return res;
	}

	//Devuelve el conjunto de posiciones libres del ingreso que esta mas cerca de p. si no hay posiciones
	//libres en el mas cercano, devuelve el otro conjunto.
	//Pre: p debe ser una posicion valida.
	Conj<Posicion> Campus::IngresosMasCercanos(Posicion p) const{
        Conj<Posicion> res;
        if (Distancia(p,Posicion(p.x,1)) <= Distancia(p,Posicion(p.x,filas)))
            res.Agregar(Posicion(p.x,1));
        if (Distancia(p,Posicion(p.x,filas)) <= Distancia(p,Posicion(p.x,1)))
            res.Agregar(Posicion(p.x,filas));
        return res;
	}

}
#endif // CAMPUS_H_
