#ifndef AED2_CAMPUSSEGURO_H_
#define AED2_CAMPUSEGURO_H_

#include <ostream>
#include "Campus.h"
#include "DiccNombres.h"
#include "DiccAgentes.h"
#include "aed2.h"

namespace aed2
{
    typedef String Nombre;
    typedef Nat Placa;

    struct Celda{
        String tipo;
        Conj<Nombre>::Iterador estudiante;
        Conj<Nombre>::Iterador hippie;
        DiccAgentes::Iterador agente;
    };

	class CampusSeguro{
		public:
			//Constructor
			CampusSeguro();

			//Constructor por parámetros
			CampusSeguro(const Campus& c,Dicc<Placa,Posicion> da);

			//Devuelve el campus
			Campus suCampus();

			//Devuelve un iterador al conjunto de estudiantes del campus.
			Iterado<Conj<Nombre>> Estudiantes();

			//Devuelve un iterador al conjunto de hippies del campus
			Conj<Nombre> Hippies();


			//Devuelve un iterador al conjunto de agentes del campus.
			Conj<Placa> Agentes();

			//Devuelve la posicion del estudiante o hippie pasado por parametro.
			//Pre:
			Posicion PosicionEstudianteYHippie(Nombre nombre);

			//Devuelve la posicion del agente pasado por parametro.
			//Pre:
			Posicion PosAgente(Nat as);

			//Devuelve la cantidad de sanciones que tiene el agente pasado por parametro.
			//Pre:
			Nat CantSanciones(Nat as);

			//Devuelve la cantidad de hippies que atrapo el agente pasado por parametro.
			//Pre:
			Nat CantHippiesAtrapados(Nat as);

			//Instancia un nuevo Campus Seguro ubicando a los agentes pasados por parametro en sus posiciones
			//correspondientes.
			//Pre:
			CampusSeguro ComenzarRastrillaje(Dicc<Placa,Posicion> da);

			//Ingresa un estudiante al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en
			//la grilla con respecto a sus vecinos.
			//Pre:
			void IngresarEstudiante(Nombre est, Posicion p);

			//Ingresa un hippie al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en la
			//grilla con respecto a sus vecinos.
			//Pre:
			void IngresarHippie(Nombre hip, Posicion p);

			//Mueve al estudiante pasado por parametro dentro de campus hacia la direccion pasada por
			//parametro y realiza los cambios necesarios de acuerdo a la nueva situacion en la grilla con respecto a
			//sus vecinos.
			//Pre:
			void MoverEstudiante(Nombre est, Direccion d);

			//Mueve al hippie pasado por parametro dentro de campus y realiza los cambios necesarios de
			//acuerdo a la nueva situacion en la grilla con respecto a sus vecinos.
			//Pre:
			void MoverHippie(Nombre hip);

			//Mueve a un agente dentro del campus y realiza los cambios necesarios de acuerdo a la nueva
			//situacion en la grilla con respecto a sus vecinos.
			//Pre:
			void MoverAgente(Nat as);

			//Devuelve la cantidad de hippies que estan presentes en el campus.
			//Pre:
			Nat CantHippies();

			//Devuelve la cantidad de estudiantes que estan presentes en el campus.
			//Pre:
			Nat CantEstudiantes();

			//Devuelve el agente que atrapo la mayor cantidad de hippies.
			//Pre:
			Nat MasVigilante();

			//Devuelve el conjunto de agentes que tiene la misma cantidad de sanciones que el agente pasado por
			//parametro.
			//Pre:
			Conj<Nat> ConMismasSanciones(Nat as);

			//Devuelve el conjunto de agentes que tiene k sanciones
			//parametro.
			//Pre:
			Conj<Nat> ConKSanciones(Nat k);

		private:

    		Campus 					campusObstaculos;
    		Vector<Vector<Celda>>  			campusCompleto;
    		diccNombres 				estudiantes;
    		diccNombres 				hippies;
    		DiccAgentes 				diccAg;
    		Placa 					masVigilante;
    		bool 					huboSanciones;


	};

//	CampusSeguro::CampusSeguro(){
//	}

    Nat calcularMin(Dicc<Placa,Posicion> da){
        Dicc<Placa,Posicion>::Iterador it = da.CrearIt();
        Nat candidato;
        if(da.CantClaves() > 0)
            candidato = it.SiguienteClave();
        else
            candidato = 0;
        while(it.HaySiguiente()){
            if(it.SiguienteClave() < candidato)
                candidato = it.SiguienteClave();
            it.Avanzar();
        }
        return candidato;
    }

    Nat calcularMax(Dicc<Placa,Posicion> da){
        Dicc<Placa,Posicion>::Iterador it = da.CrearIt();
        Nat candidato;
        if(da.CantClaves() > 0)
            candidato = it.SiguienteClave();
        else
            candidato = 1;
        while(it.HaySiguiente()){
            if(it.SiguienteClave() > candidato)
                candidato = it.SiguienteClave();
            it.Avanzar();
        }
        return candidato;
    }

    //Instancia un nuevo Campus Seguro ubicando a los agentes pasados por parametro en sus posiciones
	//correspondientes.
	//Pre:
	CampusSeguro::CampusSeguro(const Campus& c,Dicc<Placa,Posicion> da){
		Nat i=0;
		Nat j=0;
		while (i<this->campusObstaculos.Columnas())
		{
			while (j<this->campusObstaculos.Filas()){
				if (this->campusObstaculos.EstaOcupada(Posicion(i,j)))
				{
					this->campusCompleto[i][j].tipo = "obstaculo";
				}
				else
				{
                    this->campusCompleto[i][j].tipo = "libre";

				}
				this->campusCompleto[i][j].estudiante = Conj<Nombre>().CrearIt();
				this->campusCompleto[i][j].hippie = Conj<Nombre>().CrearIt();
				this->campusCompleto[i][j].agente = DiccAgentes().CrearIt();
				j++;
			}
			i++;
		}
		estudiantes = diccNombres();
		hippies = diccNombres();
		Dicc<Placa,Posicion>::Iterador itAgentes = da.CrearIt();
		masVigilante = itAgentes.SiguienteClave();
		Nat minimo = calcularMin(da);
		Nat maximo = calcularMax(da);
		diccAg = DiccAgentes(minimo,maximo);
		while(itAgentes.HaySiguiente()){
            diccAg.Definir(itAgentes.SiguienteClave(),itAgentes.SiguienteSignificado());
            itAgentes.Avanzar();
		}
		DiccAgentes::Iterador itDiccAgentes = diccAg.CrearIt();
		while(itDiccAgentes.HaySiguiente()){
            Posicion p = itDiccAgentes.Siguiente().pos;
            this->campusCompleto[p.x][p.y].tipo = "agente";
            this->campusCompleto[p.x][p.y].agente = itDiccAgentes;
		}
		this->huboSanciones = false;
	}

	Campus CampusSeguro::suCampus(){
		return this->campusObstaculos;
	}

	//Devuelve un conjunto de iteradores a los estudiantes del campus.
	Conj<Nombre> CampusSeguro::Estudiantes(){
		//return this->estudiantes.Claves();
	}

	//Devuelve un conjunto de iteradores a los hippies del campus
	Conj<Nombre> CampusSeguro::Hippies(){
		//return this->hippies.Claves();
	}


	//Devuelve un conjunto de iteradores a los agentes del campus.
	Conj<Placa> CampusSeguro::Agentes(){
		return this->diccAg.Claves();
	}

	//Devuelve la posicion del estudiante o hippie pasado por parametro.
	//Pre:
	Posicion CampusSeguro::PosicionEstudianteYHippie(Nombre nombre){
		Posicion res;
		if (this->estudiantes.Definido(nombre))
		{
			res= this->estudiantes.Obtener(nombre);
		}
		else res= this->hippies.Obtener(nombre);
		return res;

	}

	//Devuelve la posicion del agente pasado por parametro.
	//Pre:
	Posicion CampusSeguro::PosAgente(Nat as){
		return diccAg.Obtener(as).pos;
	}

	//Devuelve la cantidad de sanciones que tiene el agente pasado por parametro.
	//Pre:
	Nat CampusSeguro::CantSanciones(Nat as){
		return diccAg.Obtener(as).sanciones;
	}

	//Devuelve la cantidad de hippies que atrapo el agente pasado por parametro.
	//Pre:
	Nat CampusSeguro::CantHippiesAtrapados(Nat as){
		return diccAg.Obtener(as).capturas;
	}

	//Ingresa un estudiante al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en
	//la grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::IngresarEstudiante(Nombre est, Posicion p){

	}

	//Ingresa un hippie al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en la
	//grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::IngresarHippie(Nombre hip, Posicion p){

	}

	//Mueve al estudiante pasado por parametro dentro de campus hacia la direccion pasada por
	//parametro y realiza los cambios necesarios de acuerdo a la nueva situacion en la grilla con respecto a
	//sus vecinos.
	//Pre:
	void CampusSeguro::MoverEstudiante(Nombre est, Direccion d){

	}

	//Mueve al hippie pasado por parametro dentro de campus y realiza los cambios necesarios de
	//acuerdo a la nueva situacion en la grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::MoverHippie(Nombre hip){

	}

	//Mueve a un agente dentro del campus y realiza los cambios necesarios de acuerdo a la nueva
	//situacion en la grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::MoverAgente(Nat as){

	}

	//Devuelve la cantidad de hippies que estan presentes en el campus.
	//Pre:
	Nat CampusSeguro::CantHippies(){

	}

	//Devuelve la cantidad de estudiantes que estan presentes en el campus.
	//Pre:
	Nat CampusSEguro::CantEstudiantes(){

	}

	//Devuelve el agente que atrapo la mayor cantidad de hippies.
	//Pre:
	Nat CampusSeguro::MasVigilante(){

	}

	//Devuelve el conjunto de agentes que tiene la misma cantidad de sanciones que el agente pasado por
	//parametro.
	//Pre:
	Conj<Nat> CampusSeguro::ConMismasSanciones(Nat as){

	}

	//Devuelve el conjunto de agentes que tiene k sanciones
	//parametro.
	//Pre:
	Conj<Nat> CampusSeguro::ConKSanciones(Nat k){

	}

}

#endif
