#ifndef AED2_CAMPUSSEGURO_H_
#define AED2_CAMPUSEGURO_H_

#include <ostream>
#include "Campus.h"
#include "diccNombres.h"
#include "diccAgentes.h"
#include "Tipos.h"
#include "aed2.h"

namespace aed2
{
    struct Celda{
        String tipo;
        Conj<Nombre>::const_Iterador estudiante;
        Conj<Nombre>::const_Iterador hippie;
        DiccAgentes::Iterador agente;

        Celda() : tipo("") , estudiante(Conj<Nombre>().CrearIt()) , hippie(Conj<Nombre>().CrearIt()) , agente(DiccAgentes().CrearIt()){}
    };

	class CampusSeguro{
		public:

			//Constructor
			CampusSeguro();

			//Destructor
			~CampusSeguro();

			//Constructor por parámetros
			CampusSeguro(const Campus& c,Dicc<Agente,Posicion> da);

			CampusSeguro& operator=(const CampusSeguro& otro);

			//Devuelve el campus
			Campus suCampus();

			//Devuelve un iterador al conjunto de estudiantes del campus.
			Conj<Nombre>::const_Iterador Estudiantes() const;

			//Devuelve un iterador al conjunto de hippies del campus
			const Conj<Nombre>::const_Iterador Hippies() const;


			//Devuelve un iterador al conjunto de agentes del campus.
			const Conj<Agente> Agentes() const;

			//Devuelve la posicion del estudiante o hippie pasado por parametro.
			//Pre:Nombre pertenece al diccionario de hipies o estudiantes.
			Posicion PosicionEstudianteYHippie(Nombre nombre) const;

			//Devuelve la posicion del agente pasado por parametro.
			//Pre: as pertenece al diccionario de agentes.
			Posicion PosAgente(Nat as) const;

			//Devuelve la cantidad de sanciones que tiene el agente pasado por parametro.
			//Pre: as pertenece al diccionario de agentes.
			Nat CantSanciones(Nat as) const;

			//Devuelve la cantidad de hippies que atrapo el agente pasado por parametro.
			//Pre: as pertenece al diccionario de agentes.
			Nat CantHippiesAtrapados(Nat as) const;

			//Ingresa un estudiante al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en
			//la grilla con respecto a sus vecinos.
			//Pre: p debe ser una posicion de ingreso y debe estar desocupada, est no debe estar definido ni como
			//estudiante ni como hippie
			void IngresarEstudiante(Nombre est, Posicion p);

			//Ingresa un hippie al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en la
			//grilla con respecto a sus vecinos.
			//Pre: p debe ser una posicion de ingreso y debe estar desocupada, hip no debe estar definido ni como
			//estudiante ni como hippie
			void IngresarHippie(Nombre hip, Posicion p);

			//Mueve al estudiante pasado por parametro dentro de campus hacia la direccion pasada por
			//parametro y realiza los cambios necesarios de acuerdo a la nueva situacion en la grilla con respecto a
			//sus vecinos.
			//Pre: est debe pertenecer a estudiantes y o bien la posicion a la q se mueve es una posicion valida o el
			//estudiante se retira.
			void MoverEstudiante(Nombre est, Direccion d);

			//Mueve al hippie pasado por parametro dentro de campus y realiza los cambios necesarios de
			//acuerdo a la nueva situacion en la grilla con respecto a sus vecinos.
			//Pre: hip debe pertenecer a hippies y debe existir una posicion vacia entre las posiciones vecinas
			void MoverHippie(Nombre hip);

			//Mueve a un agente dentro del campus y realiza los cambios necesarios de acuerdo a la nueva
			//situacion en la grilla con respecto a sus vecinos.
			//Pre: as debe pertenecer a gentes. Luego la cantidad de sanciones debe ser <= 3 y debe existir una
			//posicion vacia entre las posiciones vecinas
			void MoverAgente(Nat as);

			//Devuelve la cantidad de hippies que estan presentes en el campus.
			Nat CantHippies() const;

			//Devuelve la cantidad de estudiantes que estan presentes en el campus.
			Nat CantEstudiantes() const;

			//Devuelve el agente que atrapo la mayor cantidad de hippies.
			Nat MasVigilante() const;

			//Devuelve el conjunto de agentes que tiene la misma cantidad de sanciones que el agente pasado por
			//parametro.
			//Pre: as debe pertenecer al diccionario de agentes
			const Conj<Nat> ConMismasSanciones(Nat as) const;

			//Devuelve el conjunto de agentes que tiene k sanciones
			//parametro.
			const Conj<Nat> ConKSanciones(Nat k);

		private:

            struct MaxVigilante{
                Agente placa;
                Nat capturas;

                MaxVigilante(): placa(0) , capturas(0) {}
                MaxVigilante(Agente p, Nat c) : placa(p) , capturas(c) {}
            };

    		Campus 					    campusObstaculos;
    		Vector<Vector<Celda>>  		campusCompleto;
    		diccNombres 				estudiantes;
    		diccNombres 				hippies;
    		DiccAgentes 				diccAg;
    		MaxVigilante				masVigilante;
    		bool 					    huboSanciones;

            //friend typename diccNombres::Claves();// o friend class diccNombres;

            void ActualizarCampusSeguro(const Posicion p);
            void ChequearEstudiantes(const Posicion p,Conj<Nombre>& estudiantesAconvertir);
            void ChequearHippies(const Posicion p,Conj<Nombre>& hippiesAeliminar,Dicc<Nombre,Posicion>& estudiantesAagregar);
            Conj<Posicion> FiltrarAdyacentes(String filtro,Posicion p);
            void PremiarAlrededor(Posicion p);
            bool Rodeado(Posicion p);
            void SancionarAlrededor(Posicion p);
            bool TodosEstudiantes(Posicion p);
            Posicion BuscarEstudianteMasCercano(Posicion p);
            Posicion BuscarHippieMasCercano(Posicion p);

	};

    Nat calcularMin(Dicc<Agente,Posicion> da){
        Dicc<Agente,Posicion>::Iterador it = da.CrearIt();
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

    Nat calcularMax(Dicc<Agente,Posicion> da){
        Dicc<Agente,Posicion>::Iterador it = da.CrearIt();
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

    CampusSeguro::CampusSeguro(){
        Dicc<Agente,Posicion> d;
        Campus c(3,3);
        CampusSeguro(c,d);
    }
	
    
	CampusSeguro::~CampusSeguro(){
		Nat i = campusObstaculos.Columnas();
	    while(i > 0)
	    {
            Nat j = campusObstaculos.Filas();
            
            while(j > 0)
            {
                campusCompleto[i-1].Eliminar(j-1);
                j--;
            }
            campusCompleto.Eliminar(i);
            i--;
        }
	}
    //Instancia un nuevo Campus Seguro ubicando a los agentes pasados por parametro en sus posiciones
	//correspondientes.
	//Pre:
	CampusSeguro::CampusSeguro(const Campus& c,Dicc<Agente,Posicion> da){
        campusObstaculos = c;
		Nat i=0;
		Nat j=0;
		while (i<this->campusObstaculos.Columnas())
		{
		    j = 0;
		    Vector<Celda> v;
			while (j<this->campusObstaculos.Filas()){
                Celda celda;
				if (this->campusObstaculos.EstaOcupada(Posicion(i+1,j+1)))
				{
					celda.tipo = "obstaculo";
				}
				else
				{
                    celda.tipo = "libre";
				}
				v.AgregarAtras(celda);
				j++;
			}
			campusCompleto.AgregarAtras(v);
			i++;
		}
		estudiantes = diccNombres();
		hippies = diccNombres();
		Dicc<Agente,Posicion>::Iterador itAgentes = da.CrearIt();
		if(da.CantClaves() > 0){
            masVigilante = MaxVigilante(itAgentes.SiguienteClave(),0);
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
                this->campusCompleto[p.x-1][p.y-1].tipo = "agente";
                this->campusCompleto[p.x-1][p.y-1].agente = itDiccAgentes;
                itDiccAgentes.Avanzar();
            }
		}
		this->huboSanciones = true;
	}

    CampusSeguro& CampusSeguro::operator=(const CampusSeguro& otro){
        campusObstaculos = otro.campusObstaculos;
    	estudiantes = otro.estudiantes;
    	hippies = otro.hippies;
    	diccAg = otro.diccAg;
    	masVigilante = otro.masVigilante;
    	campusCompleto = otro.campusCompleto;
    	huboSanciones = otro.huboSanciones;
    	DiccAgentes::Iterador itDiccAgentes = diccAg.CrearIt();
    	//Reasigno las posiciones donde hay agentes para que el iterador apunte de manera indicada.
        while(itDiccAgentes.HaySiguiente()){
            Posicion p = itDiccAgentes.Siguiente().pos;
            this->campusCompleto[p.x-1][p.y-1].tipo = "agente";
            this->campusCompleto[p.x-1][p.y-1].agente = itDiccAgentes;
            itDiccAgentes.Avanzar();
        }
    	return *this;
    }

	Campus CampusSeguro::suCampus(){
		return this->campusObstaculos;
	}


	//CampusSeguro::~CampusSeguro(){
	//}

	//Devuelve un conjunto de iteradores a los estudiantes del campus.
	Conj<Nombre>::const_Iterador CampusSeguro::Estudiantes() const{
		return this->estudiantes.Claves();
	}

	//Devuelve un conjunto de iteradores a los hippies del campus
	const Conj<Nombre>::const_Iterador CampusSeguro::Hippies() const{
		return this->hippies.Claves();
	}


	//Devuelve un conjunto de iteradores a los agentes del campus.
	const Conj<Agente> CampusSeguro::Agentes() const{
		return this->diccAg.Claves();
	}

	//Devuelve la posicion del estudiante o hippie pasado por parametro.
	//Pre:
	Posicion CampusSeguro::PosicionEstudianteYHippie(Nombre nombre) const{
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
	Posicion CampusSeguro::PosAgente(Nat as) const{
		return diccAg.Obtener(as).pos;
	}

	//Devuelve la cantidad de sanciones que tiene el agente pasado por parametro.
	//Pre:
	Nat CampusSeguro::CantSanciones(Nat as) const{
		return diccAg.Obtener(as).sanciones;
	}

	//Devuelve la cantidad de hippies que atrapo el agente pasado por parametro.
	//Pre:
	Nat CampusSeguro::CantHippiesAtrapados(Nat as) const{
		return diccAg.Obtener(as).capturas;
	}

	//Ingresa un estudiante al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en
	//la grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::IngresarEstudiante(Nombre est, Posicion p){
		this->campusCompleto[p.x-1][p.y-1].tipo = "estudiante";
		this->campusCompleto[p.x-1][p.y-1].estudiante = estudiantes.Definir(est,p);
		this->campusCompleto[p.x-1][p.y-1].hippie = Conj<Nombre>().CrearIt();
		this->campusCompleto[p.x-1][p.y-1].agente = DiccAgentes().CrearIt();
		ActualizarCampusSeguro(p);
	}

	//Ingresa un hippie al campus y realiza los cambios necesarios de acuerdo a la nueva situacion en la
	//grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::IngresarHippie(Nombre hip, Posicion p){
		this->campusCompleto[p.x-1][p.y-1].tipo = "hippie";
		this->campusCompleto[p.x-1][p.y-1].estudiante = Conj<Nombre>().CrearIt();
		this->campusCompleto[p.x-1][p.y-1].hippie = hippies.Definir(hip,p);
		this->campusCompleto[p.x-1][p.y-1].agente = DiccAgentes().CrearIt();
		ActualizarCampusSeguro(p);
	}

	//Mueve al estudiante pasado por parametro dentro de campus hacia la direccion pasada por
	//parametro y realiza los cambios necesarios de acuerdo a la nueva situacion en la grilla con respecto a
	//sus vecinos.
	//Pre:
	void CampusSeguro::MoverEstudiante(Nombre est, Direccion d){
		Posicion p = this->estudiantes.Obtener(est);
		this->campusCompleto[p.x-1][p.y-1].tipo = "libre";
		this->campusCompleto[p.x-1][p.y-1].estudiante = Conj<Nombre>().CrearIt();
		this->campusCompleto[p.x-1][p.y-1].hippie = Conj<Nombre>().CrearIt();
		this->campusCompleto[p.x-1][p.y-1].agente = DiccAgentes().CrearIt();
		if (d==izq) p.x= p.x-1;
		if (d==der) p.x= p.x+1;
		if (d==arriba) p.y= p.y-1;
		if (d==abajo) p.y= p.y+1;
		if (this->campusObstaculos.posValida(p))
		{
			this->campusCompleto[p.x-1][p.y-1].tipo = "estudiante";
			this->campusCompleto[p.x-1][p.y-1].estudiante= estudiantes.Definir(est,p);
			this->campusCompleto[p.x-1][p.y-1].hippie = Conj<Nombre>().CrearIt();
			this->campusCompleto[p.x-1][p.y-1].agente = DiccAgentes().CrearIt();
			this->ActualizarCampusSeguro(p);
		}
		else this->estudiantes.Borrar(est);
	}

	//Mueve al hippie pasado por parametro dentro de campus y realiza los cambios necesarios de
	//acuerdo a la nueva situacion en la grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::MoverHippie(Nombre hip){
		Posicion pInicial = this->hippies.Obtener(hip);
		Posicion pFinal = this->BuscarEstudianteMasCercano(pInicial);
		this->campusCompleto[pFinal.x-1][pFinal.y-1].tipo = "hippie";
		this->campusCompleto[pFinal.x-1][pFinal.y-1].estudiante= Conj<Nombre>().CrearIt();
		this->campusCompleto[pFinal.x-1][pFinal.y-1].hippie = hippies.Definir(hip,pFinal);
		this->campusCompleto[pFinal.x-1][pFinal.y-1].agente = DiccAgentes().CrearIt();
		this->campusCompleto[pInicial.x-1][pInicial.y-1].tipo = "libre";
		this->campusCompleto[pInicial.x-1][pInicial.y-1].estudiante= Conj<Nombre>().CrearIt();;
		this->campusCompleto[pInicial.x-1][pInicial.y-1].hippie = Conj<Nombre>().CrearIt();
		this->campusCompleto[pInicial.x-1][pInicial.y-1].agente = DiccAgentes().CrearIt();
		this->ActualizarCampusSeguro(pFinal);
	}

	//Mueve a un agente dentro del campus y realiza los cambios necesarios de acuerdo a la nueva
	//situacion en la grilla con respecto a sus vecinos.
	//Pre:
	void CampusSeguro::MoverAgente(Nat as){
		Posicion pInicial = this->diccAg.ObtenerLog(as).pos;
		Posicion pFinal = BuscarHippieMasCercano(pInicial);

		this->campusCompleto[pFinal.x-1][pFinal.y-1].tipo = "agente";
		this->campusCompleto[pFinal.x-1][pFinal.y-1].estudiante = Conj<Nombre>().CrearIt();
		this->campusCompleto[pFinal.x-1][pFinal.y-1].hippie = Conj<Nombre>().CrearIt();
		this->campusCompleto[pFinal.x-1][pFinal.y-1].agente = this->campusCompleto[pInicial.x-1][pInicial.y-1].agente.Mover(pFinal);
		this->campusCompleto[pInicial.x-1][pInicial.y-1].tipo = "libre";
		this->campusCompleto[pInicial.x-1][pInicial.y-1].estudiante = Conj<Nombre>().CrearIt();
		this->campusCompleto[pInicial.x-1][pInicial.y-1].hippie = Conj<Nombre>().CrearIt();
		this->campusCompleto[pInicial.x-1][pInicial.y-1].agente = DiccAgentes().CrearIt();
		this->ActualizarCampusSeguro(pFinal);
	}
	//Modificada para que sea correcta (se invirtió el orden de las asignaciones de posiciones).

	//Devuelve la cantidad de hippies que estan presentes en el campus.
	//Pre:
	Nat CampusSeguro::CantHippies() const{
		Conj<Nombre>::const_Iterador it = Hippies();
		Nat cuenta = 0;
		while(it.HaySiguiente()){
            it.Avanzar();
            cuenta++;
		}
        return cuenta;
	}

	//Devuelve la cantidad de estudiantes que estan presentes en el campus.
	//Pre:
	Nat CampusSeguro::CantEstudiantes() const{
		Conj<Nombre>::const_Iterador it = Estudiantes();
		Nat cuenta = 0;
		while(it.HaySiguiente()){
            it.Avanzar();
            cuenta++;
		}
        return cuenta;
	}

	//Devuelve el agente que atrapo la mayor cantidad de hippies.
	//Pre:
	Nat CampusSeguro::MasVigilante() const{
		return this->masVigilante.placa;
	}

	//Devuelve el conjunto de agentes que tiene la misma cantidad de sanciones que el agente pasado por
	//parametro.
	//Pre:
	const Conj<Nat> CampusSeguro::ConMismasSanciones(Nat as) const{
		return this->diccAg.ConMismasSanciones(as);
	}

	//Devuelve el conjunto de agentes que tiene k sanciones
	//parametro.
	//Pre:
	const Conj<Nat> CampusSeguro::ConKSanciones(Nat k){
		Conj<Agente> res;
		if (this->huboSanciones)
		{
			res = this->diccAg.conKSancionesLineal(k);
			this->huboSanciones = false;
		}
		else res = this->diccAg.conKSancionesLog(k);
		return res;
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

    void CampusSeguro::ChequearEstudiantes(const Posicion p,Conj<Nombre>& estudiantesAconvertir){
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

    void CampusSeguro::ChequearHippies(const Posicion p,Conj<Nombre>& hippiesAeliminar,Dicc<Nombre,Posicion>& estudiantesAagregar){
        Conj<Posicion> ps = FiltrarAdyacentes("hippie",p);
        if(campusCompleto[p.x-1][p.y-1].tipo == "hippie")
            ps.AgregarRapido(p);
        Conj<Posicion>::Iterador itPos = ps.CrearIt();
        Nat i = 0;
        Nat j = 0;
        Posicion posActual = Posicion(0,0);
        while(itPos.HaySiguiente()){
            posActual = itPos.Siguiente();
            i = posActual.x-1;
            j = posActual.y-1;
            if(Rodeado(posActual) && FiltrarAdyacentes("agente",posActual).Cardinal() >= 1){
                PremiarAlrededor(posActual);
                hippiesAeliminar.AgregarRapido(campusCompleto[i][j].hippie.Siguiente());
            }
            if(Rodeado(posActual) && TodosEstudiantes(posActual)){
                hippiesAeliminar.AgregarRapido(campusCompleto[i][j].hippie.Siguiente());
                estudiantesAagregar.DefinirRapido(campusCompleto[i][j].hippie.Siguiente(),posActual);
            }
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
            if(campusCompleto[i][j].agente.Siguiente().capturas > masVigilante.capturas)
                masVigilante = MaxVigilante(campusCompleto[i][j].agente.SiguienteClave(),campusCompleto[i][j].agente.Siguiente().capturas);
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
            Conj<Posicion> conjPos = estudiantes.Significados();
            Conj<Posicion>::Iterador it = conjPos.CrearIt();
            candidato = it.Siguiente();
            while(it.HaySiguiente()){
                if(campusObstaculos.Distancia(p,it.Siguiente()) <= campusObstaculos.Distancia(p,candidato))
                    candidato = it.Siguiente();
                it.Avanzar();
            }
        }else{
            Conj<Posicion>::Iterador it = campusObstaculos.IngresosMasCercanos(p).CrearIt();
            candidato = it.Siguiente();
        }
        //Agregado fragmento que decide en qué dirección debe ir
        //Una vez encontrado el más cercano
        Posicion res = Posicion(0,0);
        Conj<Posicion> conjVecinos = FiltrarAdyacentes("libre",p);
        if(!conjVecinos.EsVacio()){
            Conj<Posicion>::Iterador itVecinos = conjVecinos.CrearIt();
            res = itVecinos.Siguiente();
            while(itVecinos.HaySiguiente()){
                if(campusObstaculos.Distancia(itVecinos.Siguiente(),candidato) < campusObstaculos.Distancia(res,candidato))
                    res = itVecinos.Siguiente();
                itVecinos.Avanzar();
            }
        }
        return res;
    }



    Posicion CampusSeguro::BuscarHippieMasCercano(Posicion p){
        Posicion candidato = Posicion(0,0);
        if(!hippies.DiccVacio()){
            Conj<Posicion> conjPos = hippies.Significados();
            Conj<Posicion>::Iterador it = conjPos.CrearIt();
            candidato = it.Siguiente();
            while(it.HaySiguiente()){
                if(campusObstaculos.Distancia(p,it.Siguiente()) <= campusObstaculos.Distancia(p,candidato))
                    candidato = it.Siguiente();
                it.Avanzar();
            }
        }else{
            Conj<Posicion>::Iterador it = campusObstaculos.IngresosMasCercanos(p).CrearIt();
            candidato = it.Siguiente();
        }
        //Agregado fragmento que decide en qué dirección debe ir
        //Una vez encontrado el más cercano
        Posicion res = Posicion(0,0);
        Conj<Posicion> conjVecinos = FiltrarAdyacentes("libre",p);
        if(!conjVecinos.EsVacio()){
            Conj<Posicion>::Iterador itVecinos = conjVecinos.CrearIt();
            res = itVecinos.Siguiente();
            while(itVecinos.HaySiguiente()){
                if(campusObstaculos.Distancia(itVecinos.Siguiente(),candidato) < campusObstaculos.Distancia(res,candidato))
                    res = itVecinos.Siguiente();
                itVecinos.Avanzar();
            }
        }
        return res;
    }

}

#endif
