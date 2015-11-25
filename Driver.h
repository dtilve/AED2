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
		Campus c;
		CampusSeguro cs;
    /************************************************************************
     * TODO: Va a ser necesario instanciar privadamente el Modulo principal *
     * con el cuál interactuar. Además, pueden declarar todas las           *
     * funciones auxiliares que les hagan falta.                            *
     ************************************************************************/

}; // class Driver

Driver(){
	c=Campus();
	cs=CampusSeguro();
}
~Driver(){
	c.~Campus();
	cs.~CampusSeguro();
}
void crearCampus(Nat ancho, Nat alto){
	c=Campus(ancho,alto);
}
void agregarObstaculo(Posicion p){
	c.AgregarObstaculo(p);
}
Nat filas() const{
	return c.Filas();
}
Nat columnas() const{
	return c.Columnas();
}
bool ocupada(Posicion p) const{
	return c.EstaOcupada(p);
}
void comenzarRastrillaje(const Dicc<Agente,Posicion>& d){
	cs.ComenzarRastrillaje(d);
}
void ingresarEstudiante(Nombre n, Posicion p){
	cs.IngresarEstudiante(n,p);
}
void ingresarHippie(Nombre n, Posicion p){
	cs.IngresarHippie(n,p);
}
void moverEstudiante(Nombre n, Direccion d){
	cs.MoverEstudiante(n,d);
}
void moverHippie(Nombre n){
	cs.MoverHippie(n);		
}
void moverAgente(Agente pl){
	cs.MoverAgente(pl);
}
Nombre iesimoEstudiante(Nat i) const{
	Iterador<Conj<Nombre>> it = cs.Estudiantes();
	int j=0;
	while((j<i) && (it.HaySiguiente())){
		it.Avanzar();
	}
	return it.Siguiente();
}
Nombre iesimoHippie(Nat i) const{
	Iterador<Conj<Nombre>> it = cs.Hippies();
	int j=0;
	while((j<i) && (it.HaySiguiente())){
		it.Avanzar();
	}
	return it.Siguiente();
}
Nat iesimoAgente(Nat i) const{
	Iterador<Conj<Placa>> it = cs.Agentes();
	int j=0;
	while((j<i) && (it.HaySiguiente())){
		it.Avanzar();
	}
	return it.Siguiente();
}
Nat cantEstudiantes() const{
	return cs.CantEstudiantes();
}
Nat cantHippies() const{
	return cs.CantHippies();
}
Nat cantAgentes() const{
	Iterador<Conj<Placa>> it = cs.Agentes();
	int i=0;
	while(it.HaySiguiente()){
		it.Avanzar();
		i++;
	}
	return i;
}
Posicion posEstudianteYHippie(Nombre n) const{
	return cs.PosicionEstudianteYHippie(n);
}
Posicion posAgente(Agente pl) const{
	return cs.PosAgente(pl);
}
Nat cantSanciones(Agente pl) const{
	return cs.CantSanciones(pl);
}
Nat cantHippiesAtrapados(Agente pl) const{
	return cs.CantHippiesAtrapados(pl);
}
Agente masVigilante() const{
	return cs.MasVigilante();
}
const Conj<Agente> conMismasSanciones(Agente a) const{
	return cs.ConMismasSanciones(a);
}
const Conj<Agente> conKSanciones(Nat k){
	return cs.ConKSanciones(k);
}

} // namespace aed2

#endif // DRIVER_H_
