#ifndef DRIVER_H_
#define DRIVER_H_

#include "Tipos.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Dicc.h"

//#include ...

namespace aed2 {

class Driver
{
    public:

        Driver();
        ~Driver();

        /// Generadores del Campus
		void crearCampus(Nat ancho, Nat alto);
		void agregarObstaculo(Posicion p);

        /// Observadores del Campus
		Nat filas() const;
		Nat columnas() const;
		bool ocupada(Posicion p) const;

        /// Generadores de CampusSeguro
		void comenzarRastrillaje(const Dicc<Agente,Posicion>& d);
		void ingresarEstudiante(Nombre n, Posicion p);
		void ingresarHippie(Nombre n, Posicion p); 
		void moverEstudiante(Nombre n, Direccion d);
		void moverHippie(Nombre n);
		void moverAgente(Agente pl);
		
        /// Observadores de CampusSeguro
		Nombre iesimoEstudiante(Nat i) const;
		Nombre iesimoHippie(Nat i) const;
		Nat iesimoAgente(Nat i) const;
 
  		Nat cantEstudiantes() const;
 		Nat cantHippies() const;
 		Nat cantAgentes() const;

		Posicion posEstudianteYHippie(Nombre n) const;
		Posicion posAgente(Agente pl) const;
		Nat cantSanciones(Agente pl) const;
		Nat cantHippiesAtrapados(Agente pl) const;

		/// Otras operaciones de CampusSeguro
		Agente masVigilante() const;
		const Conj<Agente> conMismasSanciones(Agente a) const;
		const Conj<Agente> conKSanciones(Nat k);

   
    private:

    /************************************************************************
     * TODO: Va a ser necesario instanciar privadamente el Modulo principal *
     * con el cuál interactuar. Además, pueden declarar todas las           *
     * funciones auxiliares que les hagan falta.                            *
     ************************************************************************/

}; // class Driver


} // namespace aed2

#endif // DRIVER_H_
