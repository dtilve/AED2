#ifndef AED2_CAMPUS_H_
#define AED2_CAMPUS_H_

#include <iostream>
#include "aed2.h"
#include "auxiliares.h"

using namespace std;

namespace aed2
{
    typedef Nat Placa;

    struct Info{
        Posicion pos;
        Nat sanciones;
        Nat capturas;
    };

    struct NodoLista{
            Nat sanciones;
            Conj<Placa> sancionados;

            NodoLista(Nat s, Conj<Placa> conjSancionados) : sanciones(s), sancionados(conjSancionados){}
        };

    struct NodoVector{
        Nat sanciones;
        Lista<NodoLista>::Iterador sancionados;
    };

    struct InfoAgente{
        Posicion pos;
        Nat sanciones;
        Nat capturas;
        Lista<NodoLista>::Iterador its;
        Conj<Placa>::Iterador itcs;

        bool operator == (const InfoAgente otro) const{
            return pos == otro.pos && sanciones == otro.sanciones && capturas == otro.capturas && its == otro.its && itcs == otro.itcs;
        }
    };

    struct Agente{
        Placa placa;
        InfoAgente info;

        bool operator == (const Agente otro) const{
            return placa == otro.placa && info == otro.info;
        }

        bool operator != (const Agente otro) const{
        return !(this->operator==(otro));
        }
    };

    }

	class DiccAgentes{
	public:

        class Iterador;

		DiccAgentes(); //vacio

        DiccAgentes(Nat minimo,Nat maximo);

		~DiccAgentes();

		Iterador CrearIt();

		Conj<Placa> Claves();
		//\InterfazFuncion{Claves}{\In{da}{diccAgentes}}{itConj(Agente)}
		//[Devuelve un iterador al conjunto de claves, es decir, las placas.]
		//[Se genera aliasing porque el iterador apunta a las claves del diccionario. El iterador no tiene la capacidad de modificar el conjunto.]
		void Definir(Placa a,Posicion p);
		//\InterfazFuncion{Definir}{\In{a}{Agente},}}{}
		//[Define un agente en el diccionario.]
		Info Obtener(Nat a);
		//\InterfazFuncion{Obtener}{\In{a}{Agente}, }}{$\langle Agente,Info \rangle$}
		//[Devuelve la informacion de un agente]
		Info ObtenerLog(Nat a);
		//\InterfazFuncion{ObtenerLog}{\In{a}{Agente}, }}{$\langle Agente,Info \rangle$}
		//[Devuelve la informacion de un agente]
		bool Definido(Nat a);
		//\InterfazFuncion{Definido?}{\In{a}{Agente}, }}{bool}
		//[Chequea si el agente pasado por parametro esta definido en el diccionario.]

		class Iterador
		{
			public:
			Iterador();

			Iterador(Nat i,Vector<Agente> vec);
			// \InterfazFuncion{CrearIt}{\In{da}{diccAgentes}}{itDiccAgentes(act,arr)}
			// [Crea un iterador]
			// [El iterador se inv\'alida si y s\'olo si se elimina el elemento siguiente del iterador sin utilizar la funcion \NombreFuncion{EliminarSiguiente}.]
            ~Iterador();
			// Iterador(const typename Lista<T>::Iterador& otro); ///esto va????
			// Iterador& operator = (const typename Lista<T>::Iterador& otro); ///esto va????
			bool HayAnterior() const;
			// \InterfazFuncion{HayAnterior}{\In{it}{itDiccAgentes(act,arr)}}{bool}
			// [Devuelve \texttt{true} si y s\'olo si en el iterador todavía quedan elementos para retroceder.]
			bool HaySiguiente() const;
			// \InterfazFuncion{HaySiguiente}{\In{it}{itDiccAgentes(act,arr)}}{bool}
			// [Devuelve \texttt{true} si y s\'olo si en el iterador todavía quedan elementos para avanzar.]
			Info& Anterior() const;  //// van los dos CONST????
			// \InterfazFuncion{Anterior}{\In{it}{itDiccAgentes(act,arr)}}{nodo}
			// [Devuelve el elemento anterior del iterador.]
			// [$res$ es modificable si y slo si $it$ es modificable.]
			Info& Siguiente() const;  //// van los dos CONST????
			// \InterfazFuncion{siguiente}{\In{it}{itDiccAgentes(act,arr)}}{nodo}
			// [Devuelve el elemento siguiente a la posici\'on del iterador.]
			// [$res$ es modificable si y s\'olo si $it$ es modificable.]
			Placa SiguienteClave() const;
			void Avanzar();
			// \InterfazFuncion{Avanzar}{\Inout{it}{itDiccAgentes(act,arr)}}{}
			// [Avanza el iterador a la posici\'on siguiente.]
			void Retroceder();
			// \InterfazFuncion{Retroceder}{\Inout{it}{itDiccAgentes(act,arr)}}{}
			// [Retrocede el iterador a la posici\'on anterior.]
			void AgregarComoAnterior(const Agente elem);
			// \InterfazFuncion{AgregarComoAnterior}{\Inout{it}{itDiccAgentes(act,arr)}, \In{a}{$\langle Agente,Info \rangle$}}{}
			// [agrega el elemento $a$ a la lista iterada, entre las posici\'ones anterior y siguiente del iterador, dejando al iterador posici\'onado de forma tal que al llamar a \NombreFuncion{Anterior} se obtenga $a$.]
			// [el elemento $a$ se agrega por referencia.]
			void AgregarComoSiguiente(const Agente elem);
			// \InterfazFuncion{AgregarComoSiguiente}{\Inout{it}{itDiccAgentes(act,arr)}, \In{a}{$\langle Agente,Info \rangle$}}{}
			// [agrega el elemento $a$ a la lista iterada, entre las posici\'ones anterior y siguiente del iterador, dejando al iterador posici\'onado de forma tal que al llamar a \NombreFuncion{Siguiente} se obtenga $a$.]
			// [el elemento $a$ se agrega por referencia.]
			bool operator == (const typename DiccAgentes::Iterador& otro) const;
			bool operator != (const typename DiccAgentes::Iterador& otro) const;
			DiccAgentes Premiar(DiccAgentes d);
			// \InterfazFuncion{Premiar}{\In{it}{itDiccAgentes(act,arr)}, \Inout{da}{diccAgentes}}{}
			// [Agrega una captura al agente apuntado por el iterador.]
			// [Se genera aliasing por el iterador que esta apuntando a un agente de la estructura.]
			void Premiar();
			void Sancionar();
			void Mover(Posicion p);
			// \InterfazFuncion{Sacionar}{\In{it}{itDiccAgentes(act,arr)},\Inout{e}{estr}}{}
			DiccAgentes Mover(DiccAgentes);
			// \InterfazFuncion{Mover}{\In{it}{itDiccAgentes(act,arr)}, \Inout{da}{diccAgentes}}{}
			// [Mueve al agente apuntado por el iterador.]
			// [Se genera aliasing por el iterador que esta apuntando a un agente de la estructura.]


            private:

                Vector<Agente> arregloDeAgentesIt;
                Nat act;

        };



        private:

            Conj<Placa>	                      conjuntoDeAgentes;
            Vector<Agente>                    arregloDeAgentes;
            Vector<Conj<Iterador>>            tablaHash;
            Nat                               mayor;
            Nat                               menor;
            Lista<NodoLista>                  ListasSanciones;
            Vector<NodoVector>                ArregloDeSanciones;

            Nat FuncionDeHash(Placa Agente){
                return (Agente - menor)  /  ((mayor - menor + 1) / (arregloDeAgentes.Longitud()));
            }
            // \InterfazFuncion{funcionDEhash}{\In{Agente}{nat},\In{e}{estr}}{nat}
            // [Devuelve la posicion donde se va a guardar el iterador de la tabla de hash]
    };

DiccAgentes::DiccAgentes(){
    conjuntoDeAgentes = Conj<Placa>();
    arregloDeAgentes = Vector<Agente>();
    tablaHash = Vector<Conj<Iterador>>();
    mayor = 1;
    menor = 0;
    ListasSanciones = Lista<NodoLista>();
    ArregloDeSanciones = Vector<NodoVector>();
}

DiccAgentes::DiccAgentes(Nat minimo,Nat maximo){
    conjuntoDeAgentes = Conj<Placa>();
    arregloDeAgentes = Vector<Agente>();
    tablaHash = Vector<Conj<Iterador>>();
    mayor = maximo;
    menor = minimo;
    ListasSanciones = Lista<NodoLista>();
    ArregloDeSanciones = Vector<NodoVector>();
}

DiccAgentes::~DiccAgentes(){
    conjuntoDeAgentes.~Conj();
    Nat i = 0;
    while(i < tablaHash.Longitud()){
        tablaHash[i].~Conj();
        i++;
    }
    ListasSanciones.~Lista();
}
Conj<Placa> DiccAgentes::Claves(){
	return conjuntoDeAgentes;
}

void DiccAgentes::Definir(Placa a, Posicion p){
    //Agrego a Claves
    conjuntoDeAgentes.AgregarRapido(a);
    //Agrego a ListaSanciones y su conjunto
    Lista<NodoLista>::Iterador itLista = ListasSanciones.CrearIt();
    if (!itLista.HaySiguiente() || itLista.Siguiente().sanciones != 0){
        Conj<Placa> conjSancionados;
        const NodoLista n(0,conjSancionados);
        itLista.AgregarComoSiguiente(n);
    }
    itLista.Siguiente().sancionados.AgregarRapido(a);
    Conj<Placa>::Iterador itConj = itLista.Siguiente().sancionados.CrearIt();
    while(itConj.Siguiente() != a){
        itConj.Avanzar();
    }
    //Agrego al vector con toda la info
    Agente nuevoAgente;
    nuevoAgente.placa = a;
    nuevoAgente.info.pos = p;
    nuevoAgente.info.capturas = 0;
    nuevoAgente.info.sanciones = 0;
    nuevoAgente.info.its = itLista;
    nuevoAgente.info.itcs = itConj;
    Nat i = 0;
    while(i < arregloDeAgentes.Longitud() && a < arregloDeAgentes[i].placa){
        i++;
    }
    arregloDeAgentes.Agregar(i,nuevoAgente);
    //Armando una nueva tabla de Hash
    Vector<Conj<Iterador>> nuevaTabla;
    Nat cantAgentes = conjuntoDeAgentes.Cardinal();
    while(nuevaTabla.Longitud() < cantAgentes){
        nuevaTabla.AgregarAtras(Conj<Iterador>());
    }
    //Agregando a los agentes a esta
    Iterador it = CrearIt();
    i = 0;
    while(i < arregloDeAgentes.Longitud()){
        Nat indice = FuncionDeHash(arregloDeAgentes[i].placa);
        Iterador itAux(it);
        nuevaTabla[indice].AgregarRapido(itAux);
        it.Avanzar();
        i++;
    }
    tablaHash = nuevaTabla;
}

Info DiccAgentes::Obtener(Placa a){
	Nat n = FuncionDeHash(a);
	Conj<Iterador>::Iterador itConjIt = tablaHash[n].CrearIt();
	while(itConjIt.HaySiguiente() && (itConjIt.Siguiente().SiguienteClave() != a)){
		itConjIt.Avanzar();
	}
	Info agente;
	agente.pos = itConjIt.Siguiente().Siguiente().pos;
	agente.capturas = itConjIt.Siguiente().Siguiente().capturas;
	agente.capturas = itConjIt.Siguiente().Siguiente().sanciones;
	return agente;
}
Info DiccAgentes::ObtenerLog(Nat a){
	/*Nat ini =0;
	Nat fin =Longitud(arregloDeAgentes)-1;
	Nat medio=0;
	while(ini<fin){
		medio=fin/2;
		if(arregloDeAgentes[medio].placa < a){
			medio=ini;
		}else{
			medio=fin;
		}
	}
	return (arregloDeAgentes[medio]);*/
}
bool DiccAgentes::Definido(Nat a){/*
	Nat ord = FuncionDeHash(a);
	Nat i=0;
	Conj<Nat>::Iterador it1 = tablaHash[ord].CrearIt();
	while(it1.HaySiguiente() && (it1.Siguiente.placa != a)){
		it1.Avanzar();
	}
	return (it1.placa == a);
	*/
}

DiccAgentes::Iterador DiccAgentes::CrearIt(){
    return Iterador(0,arregloDeAgentes);
}

//implementacion iterador
DiccAgentes::Iterador::Iterador(){ //por que esta comentado ? :) just to know.. parece estar bien asi
	Vector<Agente> v;
	arregloDeAgentesIt = v;
	act = 0;
}

DiccAgentes::Iterador::Iterador(Nat i,Vector<Agente> vec){
    arregloDeAgentesIt = vec;
    act = i;
}

DiccAgentes::Iterador::~Iterador(){

}
bool DiccAgentes::Iterador::HayAnterior() const{
	return (this->act != 0);
}
bool DiccAgentes::Iterador::HaySiguiente() const{
	return (this->act != (this->arregloDeAgentesIt.Longitud()-1));
}
Info& DiccAgentes::Iterador::Anterior() const{ //por que esta comentado ? :) just to know.. parece estar bien asi
	// return arregloDeAgentesIt(act-1);
}
Info& DiccAgentes::Iterador::Siguiente() const{ //por que esta comentado ? :) just to know.. parece estar bien asi
	Info info;
	info.pos = arregloDeAgentesIt[act].info.pos;
	info.sanciones = arregloDeAgentesIt[act].info.sanciones;
	info.capturas = arregloDeAgentesIt[act].info.capturas;
	return info;
}
Placa DiccAgentes::Iterador::SiguienteClave() const{
    return arregloDeAgentesIt[act].placa;
}
void DiccAgentes::Iterador::Avanzar(){
	act++;
}
void DiccAgentes::Iterador::Retroceder(){
	act--;
}
void DiccAgentes::Iterador::AgregarComoAnterior(Agente elem){ //por que esta comentado ? :) just to know.. parece estar bien asi
	// arregloDeAgentes[act-1]=elem;
}
void DiccAgentes::Iterador::AgregarComoSiguiente(Agente elem){ //por que esta comentado ? :) just to know.. parece estar bien asi
//	arregloDeAgentes[act+1]=elem;
}

bool DiccAgentes::Iterador::operator == (const typename DiccAgentes::Iterador& otro) const{
	Nat i = 0;
	while(i < arregloDeAgentesIt.Longitud() && arregloDeAgentesIt[i] == otro.arregloDeAgentesIt[i]){
            i++;
	}
	return act == otro.act && i == arregloDeAgentesIt.Longitud();
}

bool DiccAgentes::Iterador::operator != (const typename DiccAgentes::Iterador& otro) const{
    return !(this->operator==(otro));
}

void DiccAgentes::Iterador::Premiar(){
	arregloDeAgentesIt[act].info.capturas++;
}
void DiccAgentes::Iterador::Sancionar(){
	/*this->Siguiente.info.sanciones=this->Siguiente.info.sanciones+1;
	this->Siguiente.info.itcs.borrar();
	if(this->Siguiente.info.its.sancion==this->Siguiente.info.sanciones){
		this->Siguiente.info.its.Avanzar();
		this->Siguiente.info.its.Agregar(this->Siguiente.placa);
	}else{

	}*/
	//         \If{$it.arr_{it.act}.its.avanzar().sancion == it.arr_{it.act}.sanciones$}
			// 	\State $it.arr_{it.act}.its.avanzar()$ \Comment $O(1)$
   //             \State $Agregar(it.arr_{it.act},it.arr_{it.act}.itcs)$ \Comment $O(1)$
   //         \Else
			// 	\State $AgregarComoSiguiente(tupla(it.arr_{it.act}.sanciones,vacio()),it.arr_{it.act}.its)$ \Comment $O(1)$
			// 	\State $it.arr_{it.act}.its.avanzar()$ \Comment $O(1)$
   //             \State $Agregar(it.arr_{it.act},it.arr_{it.act}.itcs)$ \Comment $O(1)$
   //         \EndIf
			// \State \Comment $O(1)$
   //         \State \Comment $O(1)$
			// \Statex \underline{Complejidad:} $O(1)$
}
void DiccAgentes::Iterador::Mover(Posicion p){
//	this->Siguiente.info.pos = p;
}



#endif
