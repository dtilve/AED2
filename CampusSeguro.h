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
			//Devuelve el campus por referencia.
			CampusSeguro();

			//Devuelve un conjunto de iteradores a los estudiantes del campus.
			Conj<Nombre> Estudiantes(const CampusSeguro& cs);//¿"Estudiantes" es un string no?

			//Devuelve un conjunto de iteradores a los hippies del campus
			Conj<Nombre> Hippies(const CampusSeguro& cs);


			//Devuelve un conjunto de iteradores a los agentes del campus.
			Conj<Placa> Agentes(const CampusSeguro& cs);//

			//Devuelve la posicion del estudiante o hippie pasado por parametro.
			//Pre:
			Posicion PosicionEstudianteYHippie(Arreglo<char> nombre, const CampusSeguro& cs);

			//Devuelve la posicion del agente pasado por parametro.
			//Pre:
			Posicion PosAgente(const CampusSeguro& cs, Nat as);

			//Devuelve la cantidad de sanciones que tiene el agente pasado por parametro.
			//Pre:
			Nat CantSanciones(const CampusSeguro& cs, Nat as);

			//Devuelve la cantidad de hippies que atrapo el agente pasado por parametro.
			//Pre:
			Nat CantHippiesAtrapados(const Campus& c, Nat as);

			//Instancia un nuevo Campus Seguro ubicando a los agentes pasados por parametro en sus posiciones
			//correspondientes.
			//Pre:
			CampusSeguro ComenzarRastrillaje(Dicc<Placa,Posicion> da, const Campus& c);

			//Ingresa un estudiante al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en
			//la grilla con respecto a sus vecinos.
			//Pre:
			void IngresarEstudiante(Arreglo<char> est, Posicion p, CampusSeguro& cs);

			//Ingresa un hippie al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en la
			//grilla con respecto a sus vecinos.
			//Pre:
			void IngresarHippie(Arreglo<char> hip, Posicion p, CampusSeguro& cs);

			//Mueve al estudiante pasado por parametro dentro de campus hacia la direccion pasada por
			//parametro y realiza los cambios necesarios de acuerdo a la nueva situacion en la grilla con respecto a
			//sus vecinos.
			//Pre:
			void MoverEstudiante(Arreglo<char> est, Direccion d, CampusSeguro& cs);

			//Mueve al hippie pasado por parametro dentro de campus y realiza los cambios necesarios de
			//acuerdo a la nueva situacion en la grilla con respecto a sus vecinos.
			//Pre:
			void MoverHippie(Arreglo<char> hip, CampusSeguro& cs);

			//Mueve a un agente dentro del campus y realiza los cambios necesarios de acuerdo a la nueva
			//situacion en la grilla con respecto a sus vecinos.
			//Pre:
			void MoverAgente(Nat as, CampusSeguro& cs);

			//Devuelve la cantidad de hippies que estan presentes en el campus.
			//Pre:
			Nat CantHippies(const CampusSeguro& cs);

			//Devuelve la cantidad de estudiantes que estan presentes en el campus.
			//Pre:
			Nat CantEstudiantes(const CampusSeguro& cs);

			//Devuelve el agente que atrapo la mayor cantidad de hippies.
			//Pre:
			Nat MasVigilante(const CampusSeguro& cs);

			//Devuelve el conjunto de agentes que tiene la misma cantidad de sanciones que el agente pasado por
			//parametro.
			//Pre:
			Conj<Nat> ConMismasSanciones(Nat as,const CampusSeguro& cs);

			//Devuelve el conjunto de agentes que tiene k sanciones
			//parametro.
			//Pre:
			Conj<Nat> ConKSanciones(Nat k,const CampusSeguro& cs);

		private:

    		Campus 					campusObstaculos;
    		Vector<Vector<Celda>>  	campusCompleto;
    		diccNombres 			estudiantes;
    		diccNombres 			hippies;
    		diccAgentes 			diccAg;
    		Placa 					masVigilante;
    		bool 					huboSanciones;


	};
}

#endif
