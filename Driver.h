#ifndef DRIVER_H_
#define DRIVER_H_

#include "Tipos.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/Dicc.h"

#include "CampusSeguro.h"

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

}; // class Driver

Driver::Driver(){
}

Driver::~Driver(){
}

void Driver::crearCampus(Nat ancho, Nat alto){
	c=Campus(ancho,alto);
}

void Driver::agregarObstaculo(Posicion p){
	c.AgregarObstaculo(p);
}

Nat Driver::filas() const{
	return c.Filas();
}

Nat Driver::columnas() const{
	return c.Columnas();
}

bool Driver::ocupada(Posicion p) const{
	return c.EstaOcupada(p);
}

void Driver::comenzarRastrillaje(const Dicc<Agente,Posicion>& d){
	cs = CampusSeguro(c,d);
}

void Driver::ingresarEstudiante(Nombre n, Posicion p){
	cs.IngresarEstudiante(n,p);
}

void Driver::ingresarHippie(Nombre n, Posicion p){
	cs.IngresarHippie(n,p);
}

void Driver::moverEstudiante(Nombre n, Direccion d){
	cs.MoverEstudiante(n,d);
}
void Driver::moverHippie(Nombre n){
	cs.MoverHippie(n);
}
void Driver::moverAgente(Agente pl){
	cs.MoverAgente(pl);
}
Nombre Driver::iesimoEstudiante(Nat i) const{
	Conj<Nombre>::const_Iterador it = cs.Estudiantes();
	Nat j=0;
	while((j<i) && (it.HaySiguiente())){
		it.Avanzar();
		j++;
	}
	return it.Siguiente();
}
Nombre Driver::iesimoHippie(Nat i) const{
	Conj<Nombre>::const_Iterador it = cs.Hippies();
	Nat j=0;
	while((j<i) && (it.HaySiguiente())){
		it.Avanzar();
		j++;
	}
	return it.Siguiente();
}
Nat Driver::iesimoAgente(Nat i) const{
	Conj<Agente> conjAgentes = cs.Agentes();
	Conj<Agente>::const_Iterador it = conjAgentes.CrearIt();
	Nat j=0;
	while((j<i) && (it.HaySiguiente())){
		it.Avanzar();
	}
	return it.Siguiente();
}
Nat Driver::cantEstudiantes() const{
	return cs.CantEstudiantes();
}
Nat Driver::cantHippies() const{
	return cs.CantHippies();
}
Nat Driver::cantAgentes() const{
    Conj<Agente> conjAgentes = cs.Agentes();
	Conj<Agente>::const_Iterador it = conjAgentes.CrearIt();
	int i=0;
	while(it.HaySiguiente()){
		it.Avanzar();
		i++;
	}
	return i;
}
Posicion Driver::posEstudianteYHippie(Nombre n) const{
	return cs.PosicionEstudianteYHippie(n);
}
Posicion Driver::posAgente(Agente pl) const{
	return cs.PosAgente(pl);
}
Nat Driver::cantSanciones(Agente pl) const{
	return cs.CantSanciones(pl);
}
Nat Driver::cantHippiesAtrapados(Agente pl) const{
	return cs.CantHippiesAtrapados(pl);
}
Agente Driver::masVigilante() const{
	return cs.MasVigilante();
}
const Conj<Agente> Driver::conMismasSanciones(Agente a) const{
	return cs.ConMismasSanciones(a);
}
const Conj<Agente> Driver::conKSanciones(Nat k){
	return cs.ConKSanciones(k);
}

} // namespace aed2

#endif // DRIVER_H_
