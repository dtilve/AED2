#ifndef AED2_DICCAGENTES_H_
#define AED2_DICCAGENTES_H_

#include <iostream>
#include "aed2.h"
#include "tipos.h"

using namespace std;

namespace aed2
{
	typedef Nat Placa;
	
	struct Info{
		Posicion pos;
		Nat sanciones;
		Nat capturas;
	};

	class DiccAgentes{
	public:

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

	        class Iterador;
	
	        DiccAgentes();
	        //Constructor por defecto. Crea un diccionario nuevo vacío con máximo 1 y mínimo 0..
	
	        DiccAgentes(Nat minimo,Nat maximo);
	        //Crea un diccionario nuevo vacío con el rango de agentes especificado en los parámetros.

		~DiccAgentes();
		//Destructor por defecto.

		Iterador CrearIt();
		//Crea un iterador del diccionario.

		const Conj<Placa> Claves();
		//Devuelve el conjunto de claves, es decir, las placas.

		void Definir(Placa a,Posicion p);
	        //Define un agente en el diccionario.

		const Info Obtener(Nat a);
		//Devuelve la información de un agente

		const Info ObtenerLog(Nat a);
		//Devuelve la información de un agente

		bool Definido(Nat a);
		//Chequea si el agente pasado por parametro está definido en el diccionario.

	        Conj<Placa> conKSancionesLineal(Nat k);
	        //Devuelve el conjunto de agentes que poseen k sanciones con complejidad lineal.
	
	        Conj<Placa> conKSancionesLog(Nat k);
	        //Devuelve el conjunto de agentes que poseen k sanciones con complejidad logarítmica.

		Conj<Nat> ConMismasSanciones(Nat as);
		
		class Iterador
		{
			public:

			Iterador();
			//Constructor por defecto.

			Iterador(const Iterador& otro);
			
			Iterador operator = (const Iterador& otro);
			
			~Iterador();

			bool HayAnterior() const;
			//Devuelve true si y sólo si en el iterador todavía quedan elementos para retroceder.

			bool HaySiguiente() const;
			//Devuelve true si y sólo si en el iterador todavía quedan elementos para avanzar.

			const Info Anterior() const;
			//Devuelve el elemento anterior del iterador.

			const Info Siguiente() const;
			//Devuelve el elemento siguiente a la posición del iterador.

			Placa SiguienteClave() const;
			//Devuelve la placa que le corresponde al agente que se está apuntando.

			void Avanzar();
			//Avanza el iterador a la posición siguiente.

			void Retroceder();
			//Retrocede el iterador a la posición anterior.

			bool operator == (const typename DiccAgentes::Iterador& otro) const;
			//Operador de igualdad.

			bool operator != (const typename DiccAgentes::Iterador& otro) const;
			//Operador de desigualdad.

			void Premiar();
			//Agrega una captura al agente apuntado por el iterador.

			void Sancionar();
			//Agrega una sanción al agente apuntado por el iterador.

			void Mover(Posicion p);
			//Mueve al agente apuntado por el iterador.
			
            private:

                Vector<Agente>* arregloDeAgentesIt;
                Nat act;

                Iterador(Nat i,Vector<Agente>* vec);
                //Función privada que asigna directamente los argumentos a su parte privada

                friend Iterador DiccAgentes::CrearIt();

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
                return ((Agente - menor) *(arregloDeAgentes.Longitud())) /  ((mayor - menor + 1));
            }
            //Modificada un poco para que sea correcta para todos los valores
            //(Antes se podía dividir por 0) y para que C++ no provoque
            //Errores de redondeo.
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
//Modificada para que sea correcta.

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

const Conj<Placa> DiccAgentes::Claves(){
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
	while(i < arregloDeAgentes.Longitud() && a > arregloDeAgentes[i].placa){
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
//Nos vimos obligados a cambiar completamente la función definir
//debido a que en el diseño no agregábamos al respectivo agente
//en la tabla de Hash.

const Info DiccAgentes::Obtener(Placa a){
	Nat n = FuncionDeHash(a);
	Conj<Iterador>::Iterador itConjIt = tablaHash[n].CrearIt();
	while(itConjIt.HaySiguiente() && (itConjIt.Siguiente().SiguienteClave() != a)){
		itConjIt.Avanzar();
	}
	Info agente;
	agente.pos = itConjIt.Siguiente().Siguiente().pos;
	agente.capturas = itConjIt.Siguiente().Siguiente().capturas;
	agente.sanciones = itConjIt.Siguiente().Siguiente().sanciones;
	return agente;
}
//Ligeras modificaciones, pero el algoritmo es el mismo.

const Info DiccAgentes::ObtenerLog(Placa a){
	Nat i =0;
	Nat f = arregloDeAgentes.Longitud()-1;
	if(arregloDeAgentes[f].placa == a)
        i = f;
	while(i+1 < f){
		Nat medio=(i+f)/2;
		if(arregloDeAgentes[medio].placa <= a){
			i = medio;
		}else{
			f = medio;
		}
	}
	Info agente;
	agente.pos = arregloDeAgentes[i].info.pos;
	agente.sanciones = arregloDeAgentes[i].info.sanciones;
	agente.capturas = arregloDeAgentes[i].info.capturas;
	return agente;
}
//Ligeras modificaciones, pero el algoritmo es el mismo.

bool DiccAgentes::Definido(Placa a){
	Nat n = FuncionDeHash(a);
	bool esta = false;
	if (n < tablaHash.Longitud()){
        Conj<Iterador>::Iterador itConjIt = tablaHash[n].CrearIt();
        while(itConjIt.HaySiguiente() && itConjIt.Siguiente().SiguienteClave() != a)
            itConjIt.Avanzar();
        esta = itConjIt.HaySiguiente();

	}
	return esta;
}
//Tuvimos que hacer ligeras modificaciones porque al querer acceder
//a tablaHash[n] se puede querer acceder a un índice no válido
//del vector.

Conj<Placa> DiccAgentes::conKSancionesLineal(Nat k){
	Lista<NodoLista>::Iterador it = ListasSanciones.CrearIt();
	Conj<Placa> agentesConKSanciones;
	Vector<NodoVector> vectorNuevo;
	while(it.HaySiguiente()){
	        Lista<NodoLista>::Iterador itAux = it;
	        NodoVector n;
	        n.sanciones = it.Siguiente().sanciones;
	        n.sancionados = itAux;
	        vectorNuevo.AgregarAtras(n);
	        if(it.Siguiente().sanciones == k)
	            agentesConKSanciones = it.Siguiente().sancionados;
	        it.Avanzar();
	}
	ArregloDeSanciones = vectorNuevo;
	return agentesConKSanciones;
}
//Modificada para que sea correcta.

Conj<Placa> DiccAgentes::conKSancionesLog(Nat k){
    Conj<Placa> res;
    if(!ArregloDeSanciones.EsVacio()){
        Lista<NodoLista> it;
        Nat i = 0;
        Nat f = ArregloDeSanciones.Longitud()-1;
        Nat medio = 0;
        if (ArregloDeSanciones[f].sanciones == k)
            i = f;
        while(i+1 < f){
            medio = (i+f)/2;
            if (ArregloDeSanciones[medio].sanciones <= k)
                i = medio;
            else
                f = medio;
        }
        if (ArregloDeSanciones[i].sanciones == k)
            res = ArregloDeSanciones[i].sancionados.Siguiente().sancionados;
    }else{
        res = Conj<Placa>();
    }
    return res;
}

Conj<Nat> DiccAgentes::ConMismasSanciones(Nat as){
	
}

//Modificada para que sea correcta.

DiccAgentes::Iterador DiccAgentes::CrearIt(){
    return Iterador(0,&arregloDeAgentes);
}

///implementacion iterador

DiccAgentes::Iterador::Iterador(){
	Vector<Agente> v;
	arregloDeAgentesIt = &v;
	act = 0;
}

DiccAgentes::Iterador::Iterador(Nat i,Vector<Agente>* vec){
    arregloDeAgentesIt = vec;
    act = i;
}

DiccAgentes::Iterador::Iterador(const Iterador& otro){
    arregloDeAgentesIt = otro.arregloDeAgentesIt;
    act = otro.act;
}

DiccAgentes::Iterador DiccAgentes::Iterador::operator = (const Iterador& otro){
    arregloDeAgentesIt = otro.arregloDeAgentesIt;
    act = otro.act;
}

DiccAgentes::Iterador::~Iterador(){

}

bool DiccAgentes::Iterador::HayAnterior() const{
	return (this->act != 0);
}

bool DiccAgentes::Iterador::HaySiguiente() const{
	return (this->act < (this->arregloDeAgentesIt->Longitud()));
}

const Info DiccAgentes::Iterador::Anterior() const{
	Info info;
	info.pos = arregloDeAgentesIt->operator[](act-1).info.pos;
	info.sanciones = arregloDeAgentesIt->operator[](act-1).info.sanciones;
	info.capturas = arregloDeAgentesIt->operator[](act-1).info.capturas;
	return info;
}

const Info DiccAgentes::Iterador::Siguiente() const{ //por que esta comentado ? :) just to know.. parece estar bien asi
	Info info;
	info.pos = arregloDeAgentesIt->operator[](act).info.pos;
	info.sanciones = arregloDeAgentesIt->operator[](act).info.sanciones;
	info.capturas = arregloDeAgentesIt->operator[](act).info.capturas;
	return info;
}

Placa DiccAgentes::Iterador::SiguienteClave() const{
    return arregloDeAgentesIt->operator[](act).placa;
}

void DiccAgentes::Iterador::Avanzar(){
	act++;
}

void DiccAgentes::Iterador::Retroceder(){
	act--;
}

bool DiccAgentes::Iterador::operator == (const typename DiccAgentes::Iterador& otro) const{
	Nat i = 0;
	while(i < arregloDeAgentesIt->Longitud() && arregloDeAgentesIt->operator[](i) == otro.arregloDeAgentesIt->operator[](i)){
            i++;
	}
	return act == otro.act && i == arregloDeAgentesIt->Longitud();
}

bool DiccAgentes::Iterador::operator != (const typename DiccAgentes::Iterador& otro) const{
    return !(this->operator==(otro));
}

void DiccAgentes::Iterador::Premiar(){
	arregloDeAgentesIt->operator[](act).info.capturas++;
}

void DiccAgentes::Iterador::Sancionar(){
    arregloDeAgentesIt->operator[](act).info.sanciones++;
	arregloDeAgentesIt->operator[](act).info.itcs.EliminarSiguiente();
	arregloDeAgentesIt->operator[](act).info.its.Avanzar();
	if (arregloDeAgentesIt->operator[](act).info.its.HaySiguiente() && arregloDeAgentesIt->operator[](act).info.its.Siguiente().sanciones == arregloDeAgentesIt->operator[](act).info.sanciones){
        arregloDeAgentesIt->operator[](act).info.its.Siguiente().sancionados.AgregarRapido(arregloDeAgentesIt->operator[](act).placa);
        arregloDeAgentesIt->operator[](act).info.itcs = arregloDeAgentesIt->operator[](act).info.its.Siguiente().sancionados.CrearIt();
	}else{
	    NodoLista n(arregloDeAgentesIt->operator[](act).info.sanciones,Conj<Placa>());
        arregloDeAgentesIt->operator[](act).info.its.AgregarComoSiguiente(n);
        arregloDeAgentesIt->operator[](act).info.its.Siguiente().sancionados.AgregarRapido(arregloDeAgentesIt->operator[](act).placa);
        arregloDeAgentesIt->operator[](act).info.itcs = arregloDeAgentesIt->operator[](act).info.its.Siguiente().sancionados.CrearIt();
	}
}
//Agregadas un par de cosas para que el algoritmo sea correcto.

void DiccAgentes::Iterador::Mover(Posicion p){
	arregloDeAgentesIt->operator[](act).info.pos = p;
}

}

#endif
