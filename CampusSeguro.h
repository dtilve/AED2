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
    		DiccAgentes 				diccAg;
    		Placa 					masVigilante;
    		bool 					huboSanciones;

            void ActualizarCampusSeguro(const Posicion p);
            void ChequearEstudiantes(const Posicion p,Conj<Nombre> estudiantesAconvertir);
            void ChequearHippies(const Posicion p,Conj<Nombre> hippiesAeliminar,Dicc<Nombre,Posicion> estudiantesAagregar);
            Conj<Posicion> FiltrarAdyacentes(String filtro,Posicion p);
            void PremiarAlrededor(Posicion p);
            bool Rodeado(Posicion p);
            void SancionarAlrededor(Posicion p);
            bool TodosEstudiantes(Posicion p);
            Posicion BuscarEstudianteMasCercano(Posicion p);
            Posicion BuscarHippieMasCercano(Posicion p);

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
	Iterador<Conj<Nombre>> CampusSeguro::Estudiantes(){
		return this->estudiantes.Claves();
	}

	//Devuelve un conjunto de iteradores a los hippies del campus
	Iterador<Conj<Nombre>> CampusSeguro::Hippies(){
		return this->hippies.Claves();
	}


	//Devuelve un conjunto de iteradores a los agentes del campus.
	Iterador<Conj<Placa>> CampusSeguro::Agentes(){
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
		this.campusCompleto[p.x-1][p.y-1].tipo = "estudiante";
		//this.campusCompleto[p.x-1][p.y-1].estudiante = ;
		this.campusCompleto[p.x-1][p.y-1].hippie = Conj<Nombre>().CrearIt();
		this.campusCompleto[p.x-1][p.y-1].agente = DiccAgentes().CrearIt();
		actualizarCampusSeguro(p);
	}

	//Ingresa un hippie al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en la
	//grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::IngresarHippie(Nombre hip, Posicion p){
		this.campusCompleto[p.x-1][p.y-1].tipo = "hippie";
		this.campusCompleto[p.x-1][p.y-1].estudiante = Conj<Nombre>().CrearIt();
		//this.campusCompleto[p.x-1][p.y-1].hippie = ;
		this.campusCompleto[p.x-1][p.y-1].agente = DiccAgentes().CrearIt();
		actualizarCampusSeguro(p);
	}

	//Mueve al estudiante pasado por parametro dentro de campus hacia la direccion pasada por
	//parametro y realiza los cambios necesarios de acuerdo a la nueva situacion en la grilla con respecto a
	//sus vecinos.
	//Pre:
	void CampusSeguro::MoverEstudiante(Nombre est, Direccion d){
		Posicion p = this.estudiantes.Obtener(est);
		this.campusCompleto[p.x-1][p.y-1].tipo = "libre";
		this.campusCompleto[p.x-1][p.y-1].estudiante = Conj<Nombre>().CrearIt();
		this.campusCompleto[p.x-1][p.y-1].hippie = Conj<Nombre>().CrearIt();
		this.campusCompleto[p.x-1][p.y-1].agente = DiccAgentes().CrearIt();
		if (d==izq) p.x= p.x-1;
		if (d==der) p.x= p.x+1;
		if (d==arriba) p.y= p.y-1;
		if (d==abajo) p.y= p.y+1;
		if (this.campusObstaculos.posValida(p))
		{
			this.campusCompleto[p.x-1][p.y-1].tipo = "estudiante";
			//this.campusCompleto[p.x-1][p.y-1].estudiante= ;
			this.campusCompleto[p.x-1][p.y-1].hippie = Conj<Nombre>().CrearIt();
			this.campusCompleto[p.x-1][p.y-1].agente = DiccAgentes().CrearIt();
		}
		else this.estudiantes.Borrar(est);
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
	Nat CampusSeguro::CantEstudiantes(){

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

    Conj<Posicion> CampusSeguro::FiltrarAdyacentes(String filtro,Posicion p){
        Conj<Posicion> res;
        Nat i = p.x-1;
        Nat j = p.y-1;
        if(campusObstaculos.posValida(Posicion(p.x+1,p.y)) && campusCompleto[i+1][j].tipo == filtro)
            res.AgregarRapido(Posicion(p.x+1,p.y));
        if(campusObstaculos.posValida(Posicion(p.x,p.y+1)) && campusCompleto[i][j+1].tipo == filtro)
            res.AgregarRapido(Posicion(p.x,p.y+1));
        if(campusObstaculos.posValida(Posicion(p.x-1,p.y)) && campusCompleto[i-1][j].tipo == filtro)
            res.AgregarRapido(Posicion(p.x-1,p.y));
        if(campusObstaculos.posValida(Posicion(p.x,p.y-1)) && campusCompleto[i][j-1].tipo == filtro)
            res.AgregarRapido(Posicion(p.x,p.y-1));
        return res;
    }

    void CampusSeguro::ChequearEstudiantes(const Posicion p,Conj<Nombre> estudiantesAconvertir){
            Conj<Posicion> ps = FiltrarAdyacentes("estudiante",p);
            if(campusCompleto[p.x-1][p.y-1].tipo == "estudiante")
                ps.AgregarRapido(p);
            Conj<Posicion>::Iterador itPos = ps.CrearIt();
            Nat i = 0;
            Nat j = 0;
            Posicion posActual = Posicion(0,0);
            while(itPos.HaySiguiente()){
                posActual = itPos.Siguiente();
                if(Rodeado(posActual) && FiltrarAdyacentes("agente",posActual).Cardinal() >= 1){
                    SancionarAlrededor(p);
                    huboSanciones = true;
                }
                if(FiltrarAdyacentes("hippie",posActual).Cardinal() >= 2){
                    i = posActual.x-1;
                    j = posActual.y-1;
                    estudiantesAconvertir.AgregarRapido(campusCompleto[i][j].estudiante.Siguiente());
                }
                itPos.Avanzar();
            }
        }

    void CampusSeguro::ChequearHippies(const Posicion p,Conj<Nombre> hippiesAeliminar,Dicc<Nombre,Posicion> estudiantesAagregar){
        Conj<Posicion> ps = FiltrarAdyacentes("hippie",p);
        if(campusCompleto[p.x-1][p.y-1].tipo == "hippie")
            ps.AgregarRapido(p);
        Conj<Posicion>::Iterador itPos = ps.CrearIt();
        Nat i = 0;
        Nat j = 0;
        Posicion posActual = Posicion(0,0);
        while(itPos.HaySiguiente()){
            i = posActual.x-1;
            j = posActual.y-1;
            if(Rodeado(posActual) && FiltrarAdyacentes("agente",posActual).Cardinal() >= 1){
                PremiarAlrededor(p);
                hippiesAeliminar.AgregarRapido(campusCompleto[i][j].hippie.Siguiente());
            }
        if(Rodeado(posActual) && TodosEstudiantes(posActual))
            estudiantesAagregar.DefinirRapido(campusCompleto[i][j].hippie.Siguiente(),posActual);
        itPos.Avanzar();
        }
    }

    void CampusSeguro::ActualizarCampusSeguro(const Posicion p){
        Conj<Nombre> hippiesAeliminar;
        Dicc<Nombre,Posicion> estudiantesAagregar;
        Conj<Nombre> estudiantesAconvertir;
        ChequearEstudiantes(p,estudiantesAconvertir);
        ChequearHippies(p,hippiesAeliminar,estudiantesAagregar);
        Conj<Nombre>::Iterador itNombres1 = estudiantesAconvertir.CrearIt();
        while(itNombres1.HaySiguiente()){
            hippies.Definir(itNombres1.Siguiente(),estudiantes.Obtener(itNombres1.Siguiente()));
            estudiantes.Borrar(itNombres1.Siguiente());
            itNombres1.Avanzar();
        }
        Conj<Nombre>::Iterador itNombres2 = hippiesAeliminar.CrearIt();
        while(itNombres2.HaySiguiente()){
            hippies.Borrar(itNombres2.Siguiente());
            itNombres2.Avanzar();
        }
        Dicc<Nombre,Posicion>::Iterador itNombres3 = estudiantesAagregar.CrearIt();
        while(itNombres3.HaySiguiente()){
            estudiantes.Definir(itNombres3.SiguienteClave(),itNombres3.SiguienteSignificado());
            itNombres3.Avanzar();
        }
    }

    void CampusSeguro::PremiarAlrededor(Posicion p){
        Conj<Posicion> ags = FiltrarAdyacentes("agente",p);
        Conj<Posicion>::Iterador itAgs = ags.CrearIt();
        Nat i = 0;
        Nat j = 0;
        while(itAgs.HaySiguiente()){
            i = itAgs.Siguiente().x-1;
            j = itAgs.Siguiente().y-1;
            campusCompleto[i][j].agente.Premiar();
            itAgs.Avanzar();
        }
    }

    bool CampusSeguro::Rodeado(Posicion p){
        Nat i = p.x-1;
        Nat j = p.y-1;
        bool derecha = !campusObstaculos.posValida(Posicion(p.x+1,p.y)) || campusCompleto[i+1][j].tipo != "libre";
        bool abajo = !campusObstaculos.posValida(Posicion(p.x,p.y+1)) || campusCompleto[i][j+1].tipo != "libre";
        bool izquierda = !campusObstaculos.posValida(Posicion(p.x-1,p.y)) || campusCompleto[i-1][j].tipo != "libre";
        bool arriba = !campusObstaculos.posValida(Posicion(p.x,p.y-1)) || campusCompleto[i][j-1].tipo != "libre";
        return derecha && izquierda && arriba && abajo;
    }

    void CampusSeguro::SancionarAlrededor(Posicion p){
        Conj<Posicion> ags = FiltrarAdyacentes("agente",p);
        Conj<Posicion>::Iterador itAgs = ags.CrearIt();
        Nat i = 0;
        Nat j = 0;
        while(itAgs.HaySiguiente()){
            i = itAgs.Siguiente().x-1;
            j = itAgs.Siguiente().y-1;
            campusCompleto[i][j].agente.Sancionar();
            itAgs.Avanzar();
        }
    }

    bool CampusSeguro::TodosEstudiantes(Posicion p){
        Nat i = p.x-1;
        Nat j = p.y-1;
        bool derecha = !campusObstaculos.posValida(Posicion(p.x+1,p.y)) || campusCompleto[i+1][j].tipo == "estudiante";
        bool abajo = !campusObstaculos.posValida(Posicion(p.x,p.y+1)) || campusCompleto[i][j+1].tipo == "estudiante";
        bool izquierda = !campusObstaculos.posValida(Posicion(p.x-1,p.y)) || campusCompleto[i-1][j].tipo == "estudiante";
        bool arriba = !campusObstaculos.posValida(Posicion(p.x,p.y-1)) || campusCompleto[i][j-1].tipo == "estudiante";
        return derecha && izquierda && arriba && abajo;
    }

    Posicion CampusSeguro::BuscarEstudianteMasCercano(Posicion p){
        Posicion candidato = Posicion(0,0);
        if(!estudiantes.DiccVacio()){
            Conj<Posicion>::Iterador it = estudiantes.Significados().CrearIt();
            Posicion candidato = it.Siguiente();
            while(it.HaySiguiente()){
                if(campusObstaculos.Distancia(p,it.Siguiente()) <= campusObstaculos.Distancia(p,candidato))
                    candidato = it.Siguiente();
                it.Avanzar();
            }
        }else{
            Conj<Posicion>::Iterador it = campusObstaculos.IngresosMasCercanos(p).CrearIt();
            Posicion candidato = it.Siguiente();
        }
        return candidato;
    }



    Posicion CampusSeguro::BuscarHippieMasCercano(Posicion p){
        Posicion candidato = Posicion(0,0);
        if(!hippies.DiccVacio()){
            Conj<Posicion>::Iterador it = hippies.Significados().CrearIt();
            Posicion candidato = it.Siguiente();
            while(it.HaySiguiente()){
                if(campusObstaculos.Distancia(p,it.Siguiente()) <= campusObstaculos.Distancia(p,candidato))
                    candidato = it.Siguiente();
                it.Avanzar();
            }
        }else{
            Conj<Posicion>::Iterador it = campusObstaculos.IngresosMasCercanos(p).CrearIt();
            Posicion candidato = it.Siguiente();
        }
        return candidato;
    }

}

#endif
