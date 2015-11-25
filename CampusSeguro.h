#ifndef AED2_CAMPUSSEGURO_H_
#define AED2_CAMPUSEGURO_H_

#include <ostream>
#include "Campus.h"
#include "aed2/TiposBasicos.h"
#include "aed2/Vector.h"
#include "aed2/Conj.h"
#include "aed2/Dicc.h"

namespace aed2
{
    typedef String Nombre;
    typedef Nat Placa;

    struct Celda{
        String tipo;
        Iterador<Nombre> estudiante;
        Iterador<Nombre> hippie;
        Iterador<Placa> agente;
    };

	class CampusSeguro{
		public:
			//Constructor
			CampusSeguro();
			
			//Devuelve el campus
			Campus();

			//Devuelve un iterador al conjunto de estudiantes del campus.
			Iterador<Conj<Nombre>> Estudiantes();

			//Devuelve un iterador al conjunto de hippies del campus
			Iterador<Conj<Nombre>> Hippies();


			//Devuelve un iterador al conjunto de agentes del campus.
			Iterador<Conj<Placa>> Agentes();

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
    		diccAgentes 				diccAg;
    		Placa 					masVigilante;
    		bool 					huboSanciones;


	};
	
	CampusSeguro::CampusSeguro();
	
	Campus CampusSeguro::Campus(){
		return this.campusObstaculos;
	}

	//Devuelve un conjunto de iteradores a los estudiantes del campus.
	Iterador<Conj<Nombre>> CampusSeguro::Estudiantes(){
		return this.estudiantes.Claves();
	}

	//Devuelve un conjunto de iteradores a los hippies del campus
	Iterador<Conj<Nombre>> CampusSeguro::Hippies(){
		return this.hippies.Claves();
	}


	//Devuelve un conjunto de iteradores a los agentes del campus.
	Iterador<Conj<Placa>> CampusSeguro::Agentes(){
		return this.diccAg.Claves();
	}

	//Devuelve la posicion del estudiante o hippie pasado por parametro.
	//Pre:
	Posicion CampusSeguro::PosicionEstudianteYHippie(Nombre nombre){
		Posicion res;
		if this.estudiantes.Definido(nombre)
		{
			res= this.estudiante.Obtener;	
		}
		else res= this.hippies.Obtener;
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

	//Instancia un nuevo Campus Seguro ubicando a los agentes pasados por parametro en sus posiciones
	//correspondientes.
	//Pre:
	CampusSeguro CampusSeguro::ComenzarRastrillaje(diccAgentes da, const Campus& c){
		Nat i=0;
		Nat j=0;
		while (i<this.campusObstaculos.Columnas)
		{
			while (j<this.campusObstaculos.Filas){
				if this.campusObstaculos.estaOcupada(Posicion(i,j))
				{
					this.campusCompleto[i][j].tipo = "obstaculo";
				}
				else
				{
					if da.Claves().Pertenece(Posicion(i,j)) 
					{
						this.campusCompleto[i][j].tipo = "agente";
						//this.campusCompleto[i][j].agente = Iterador(Obtener())
					}
					else
					{
						this.campusComple[i][j].agente = Iterador();
						this.campusCompleto[i][j].tipo = "libre";
					}	
				}
				this.campusCompleto[i][j].estudiante = Iterador();
				this.campusCompleto[i][j].hippie = Iterador();
				j++;
			}
			i++;
		}
		//this.diccAg = una copia de da; haces un while y vas iterando y agregando 
		this.estudiantes = diccNombres();
		this.hippies = diccNombres();
		this.huboSanciones = false;
		return this;
	}

	//Ingresa un estudiante al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en
	//la grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::IngresarEstudiante(Nombre est, Posicion p, CampusSeguro& cs){

	}

	//Ingresa un hippie al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en la
	//grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::IngresarHippie(Nombre hip, Posicion p, CampusSeguro& cs){

	}

	//Mueve al estudiante pasado por parametro dentro de campus hacia la direccion pasada por
	//parametro y realiza los cambios necesarios de acuerdo a la nueva situacion en la grilla con respecto a
	//sus vecinos.
	//Pre:
	void CampusSeguro::MoverEstudiante(Nombre est, Direccion d, CampusSeguro& cs){

	}

	//Mueve al hippie pasado por parametro dentro de campus y realiza los cambios necesarios de
	//acuerdo a la nueva situacion en la grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::MoverHippie(Nombre hip, CampusSeguro& cs){

	}

	//Mueve a un agente dentro del campus y realiza los cambios necesarios de acuerdo a la nueva
	//situacion en la grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::MoverAgente(Nat as, CampusSeguro& cs){

	}

	//Devuelve la cantidad de hippies que estan presentes en el campus.
	//Pre:
	Nat CampusSeguro::CantHippies(const CampusSeguro& cs){

	}

	//Devuelve la cantidad de estudiantes que estan presentes en el campus.
	//Pre:
	Nat CampusSEguro::CantEstudiantes(const CampusSeguro& cs){

	}

	//Devuelve el agente que atrapo la mayor cantidad de hippies.
	//Pre:
	Nat CampusSeguro::MasVigilante(const CampusSeguro& cs){

	}

	//Devuelve el conjunto de agentes que tiene la misma cantidad de sanciones que el agente pasado por
	//parametro.
	//Pre:
	Conj<Nat> CampusSeguro::ConMismasSanciones(Nat as,const CampusSeguro& cs){

	}

	//Devuelve el conjunto de agentes que tiene k sanciones
	//parametro.
	//Pre:
	Conj<Nat> CampusSeguro::ConKSanciones(Nat k,const CampusSeguro& cs){

	}

}

#endif
