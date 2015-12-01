#ifndef AED2_DICCAGENTES_H_
#define AED2_DICCAGENTES_H_

#include <iostream>
#include "aed2.h"
#include "tipos.h"

using namespace std;

namespace aed2
{
	typedef Nat Agente;

	struct Info{
		Posicion pos;
		Nat sanciones;
		Nat capturas;
	};

	class DiccAgentes{
	private:

		struct NodoLista{
			Nat sanciones;
			Conj<Agente> sancionados;

			NodoLista(Nat s, Conj<Agente> conjSancionados) : sanciones(s), sancionados(conjSancionados){}
		};

		struct NodoVector{
			Nat sanciones;
			Lista<NodoLista>::const_Iterador sancionados;
		};

		struct InfoAgente{
			Posicion pos;
			Nat sanciones;
			Nat capturas;
			Lista<NodoLista>::Iterador its;
			Conj<Agente>::Iterador itcs;
			bool operator == (const InfoAgente otro) const{
				return pos == otro.pos && sanciones == otro.sanciones && capturas == otro.capturas && its == otro.its && itcs == otro.itcs;
			}
		};

		struct AgenteCompleto{
			Agente placa;
			InfoAgente info;
			bool operator == (const AgenteCompleto otro) const{
				return placa == otro.placa && info == otro.info;
			}
			bool operator != (const AgenteCompleto otro) const{
				return !(this->operator==(otro));
			}
		};

    public:

        class Iterador;

        class const_Iterador;

	    DiccAgentes();
        //Constructor por defecto. Crea un diccionario nuevo vacío con máximo 1 y mínimo 0..

        DiccAgentes(Nat minimo,Nat maximo);
        //Crea un diccionario nuevo vacío con el rango de agentes especificado en los parámetros.

		~DiccAgentes();
		//Destructor por defecto.

		DiccAgentes& operator=(const DiccAgentes& otro);
        //Constructor por copia.

		Iterador CrearIt();
		//Crea un iterador del diccionario.

		const_Iterador CrearIt() const;
		//Crea un iterador del diccionario.

		const Conj<Agente> Claves() const;
		//Devuelve el conjunto de claves, es decir, las placas.

		void Definir(Agente a,Posicion p);
        //Define un agente en el diccionario.

		Info Obtener(Nat a) const;
		//Devuelve la información de un agente

		Info ObtenerLog(Nat a) const;
		//Devuelve la información de un agente

		bool Definido(Nat a);
		//Chequea si el agente pasado por parametro está definido en el diccionario.

        const Conj<Agente> conKSancionesLineal(Nat k);
        //Devuelve el conjunto de agentes que poseen k sanciones con complejidad lineal.

        const Conj<Agente> conKSancionesLog(Nat k);
        //Devuelve el conjunto de agentes que poseen k sanciones con complejidad logarítmica.

		Conj<Nat> ConMismasSanciones(Nat as) const;

		class Iterador
		{
			public:

			Iterador();
			//Constructor por defecto.

			Iterador(const Iterador& otro);

			Iterador& operator = (const Iterador& otro);

			bool HayAnterior() const;
			//Devuelve true si y sólo si en el iterador todavía quedan elementos para retroceder.

			bool HaySiguiente() const;
			//Devuelve true si y sólo si en el iterador todavía quedan elementos para avanzar.

			const Info Anterior() const;
			//Devuelve el elemento anterior del iterador.

			const Info Siguiente() const;
			//Devuelve el elemento siguiente a la posición del iterador.

			Agente SiguienteClave() const;
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

			Iterador Mover(Posicion p);
			//Mueve al agente apuntado por el iterador.

			const Conj<Agente> ConMismasSancionesIt() const;
			//Devuelve el conjunto de los que tienen las mismas sanciones que el agente actual.

        private:

            Vector<AgenteCompleto>* arregloDeAgentesIt;
            Nat act;

            Iterador(Nat i,Vector<AgenteCompleto>* vec);
            //Función privada que asigna directamente los argumentos a su parte privada

            friend Iterador DiccAgentes::CrearIt();

        };

        class const_Iterador
		{
			public:

			const_Iterador();
			//Constructor por defecto.

			const_Iterador(const const_Iterador& otro);

			const_Iterador& operator = (const const_Iterador& otro);

			bool HayAnterior() const;
			//Devuelve true si y sólo si en el iterador todavía quedan elementos para retroceder.

			bool HaySiguiente() const;
			//Devuelve true si y sólo si en el iterador todavía quedan elementos para avanzar.

			const Info Anterior() const;
			//Devuelve el elemento anterior del iterador.

			const Info Siguiente() const;
			//Devuelve el elemento siguiente a la posición del iterador.

			Agente SiguienteClave() const;
			//Devuelve la placa que le corresponde al agente que se está apuntando.

			void Avanzar();
			//Avanza el iterador a la posición siguiente.

			void Retroceder();
			//Retrocede el iterador a la posición anterior.

			bool operator == (const typename DiccAgentes::const_Iterador& otro) const;
			//Operador de igualdad.

			bool operator != (const typename DiccAgentes::const_Iterador& otro) const;
			//Operador de desigualdad.

			const Conj<Agente> ConMismasSancionesIt() const;
			//Devuelve el conjunto de los que tienen las mismas sanciones que el agente actual.

        private:

            const Vector<AgenteCompleto>* arregloDeAgentesIt;
            Nat act;

            const_Iterador(Nat i,const Vector<AgenteCompleto>* vec);
            //Función privada que asigna directamente los argumentos a su parte privada

            friend const_Iterador DiccAgentes::CrearIt() const;

        };

        private:

            Conj<Agente>	                  conjuntoDeAgentes;
            Vector<AgenteCompleto>            arregloDeAgentes;
            Vector<Conj<Iterador>>            tablaHash;
            Nat                               mayor;
            Nat                               menor;
            Lista<NodoLista>                  ListasSanciones;
            Vector<NodoVector>                ArregloDeSanciones;

            Nat FuncionDeHash(Agente Agente) const{
                return ((Agente - menor) *(arregloDeAgentes.Longitud())) /  ((mayor - menor + 1));
            }
            //Modificada un poco para que sea correcta para todos los valores
            //(Antes se podía dividir por 0) y para que C++ no provoque
            //Errores de redondeo.
    };

DiccAgentes::DiccAgentes(){
	conjuntoDeAgentes = Conj<Agente>();
	arregloDeAgentes = Vector<AgenteCompleto>();
	tablaHash = Vector<Conj<Iterador>>();
	mayor = 1;
	menor = 0;
	ListasSanciones = Lista<NodoLista>();
	ArregloDeSanciones = Vector<NodoVector>();
}
//Modificada para que sea correcta.

DiccAgentes::DiccAgentes(Nat minimo,Nat maximo){
	conjuntoDeAgentes = Conj<Agente>();
	arregloDeAgentes = Vector<AgenteCompleto>();
	tablaHash = Vector<Conj<Iterador>>();
	mayor = maximo;
	menor = minimo;
	ListasSanciones = Lista<NodoLista>();
	ArregloDeSanciones = Vector<NodoVector>();
}

DiccAgentes::~DiccAgentes(){
	conjuntoDeAgentes.~Conj();
	while(tablaHash.Longitud() > 0){
		tablaHash.Eliminar(0);
	}
	ListasSanciones.~Lista();
}

DiccAgentes& DiccAgentes::operator=(const DiccAgentes& otro){
    //Dejo todo vacío
    conjuntoDeAgentes = Conj<Agente>();
	arregloDeAgentes = Vector<AgenteCompleto>();
	tablaHash = Vector<Conj<Iterador>>();
	mayor = otro.mayor;
	menor = otro.menor;
	ListasSanciones = Lista<NodoLista>();
	ArregloDeSanciones = Vector<NodoVector>();
	//Empiezo a definir uno a uno
	const_Iterador it1 = otro.CrearIt();
	while(it1.HaySiguiente()){
        Definir(it1.SiguienteClave(),it1.Siguiente().pos);
        it1.Avanzar();
	}
	//Les agrego las sanciones y capturas que hagan falta
	Iterador itThis = this->CrearIt();
	const_Iterador itOtro = otro.CrearIt();
	while(itThis.HaySiguiente()){
        while(itThis.Siguiente().capturas < itOtro.Siguiente().capturas)
            itThis.Premiar();
        while(itThis.Siguiente().sanciones < itOtro.Siguiente().sanciones)
            itThis.Sancionar();
        itThis.Avanzar();
        itOtro.Avanzar();
	}
    return *this;
}

const Conj<Agente> DiccAgentes::Claves() const{
	return conjuntoDeAgentes;
}

void DiccAgentes::Definir(Agente a, Posicion p){
	//Agrego a Claves
	conjuntoDeAgentes.AgregarRapido(a);
	//Agrego a ListaSanciones y su conjunto
	Lista<NodoLista>::Iterador itLista = ListasSanciones.CrearIt();
	if (!itLista.HaySiguiente() || itLista.Siguiente().sanciones != 0){
	        Conj<Agente> conjSancionados;
	        const NodoLista n(0,conjSancionados);
	        itLista.AgregarComoSiguiente(n);
	}
	itLista.Siguiente().sancionados.AgregarRapido(a);
	Conj<Agente>::Iterador itConj = itLista.Siguiente().sancionados.CrearIt();
	while(itConj.Siguiente() != a){
		itConj.Avanzar();
	}
	//Agrego al vector con toda la info
	AgenteCompleto nuevoAgente;
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

Info DiccAgentes::Obtener(Agente a) const{
	Nat n = FuncionDeHash(a);
	Conj<Iterador>::const_Iterador itConjIt = tablaHash[n].CrearIt();
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

Info DiccAgentes::ObtenerLog(Agente a) const{
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

bool DiccAgentes::Definido(Agente a){
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

const Conj<Agente> DiccAgentes::conKSancionesLineal(Nat k){
	Lista<NodoLista>::const_Iterador it = ListasSanciones.CrearIt();
	Conj<Agente> agentesConKSanciones;
	Vector<NodoVector> vectorNuevo;
	while(it.HaySiguiente()){
	        Lista<NodoLista>::const_Iterador itAux = it;
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

const Conj<Agente> DiccAgentes::conKSancionesLog(Nat k){
    Conj<Agente> res;
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
        res = Conj<Agente>();
    }
    return res;
}

Conj<Nat> DiccAgentes::ConMismasSanciones(Agente as) const{
	Nat i = FuncionDeHash(as);
	Conj<Iterador>::const_Iterador it = tablaHash[i].CrearIt();
	while(it.HaySiguiente() && it.Siguiente().SiguienteClave() != as)
		it.Avanzar();
	return it.Siguiente().ConMismasSancionesIt();
}

//Modificada para que sea correcta.

DiccAgentes::Iterador DiccAgentes::CrearIt(){
    return Iterador(0,&arregloDeAgentes);
}

DiccAgentes::const_Iterador DiccAgentes::CrearIt() const{
    return const_Iterador(0,&arregloDeAgentes);
}

///implementacion iterador

DiccAgentes::Iterador::Iterador(){
	Vector<AgenteCompleto> v;
	arregloDeAgentesIt = &v;
	act = 0;
}

DiccAgentes::Iterador::Iterador(Nat i,Vector<AgenteCompleto>* vec){
    arregloDeAgentesIt = vec;
    act = i;
}

DiccAgentes::Iterador::Iterador(const Iterador& otro){
    arregloDeAgentesIt = otro.arregloDeAgentesIt;
    act = otro.act;
}

DiccAgentes::Iterador &DiccAgentes::Iterador::operator = (const Iterador& otro){
    this->arregloDeAgentesIt = otro.arregloDeAgentesIt;
    this->act = otro.act;
    return *this;
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

const Info DiccAgentes::Iterador::Siguiente() const{
	Info info;
	info.pos = arregloDeAgentesIt->operator[](act).info.pos;
	info.sanciones = arregloDeAgentesIt->operator[](act).info.sanciones;
	info.capturas = arregloDeAgentesIt->operator[](act).info.capturas;
	return info;
}

Agente DiccAgentes::Iterador::SiguienteClave() const{
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
	    NodoLista n(arregloDeAgentesIt->operator[](act).info.sanciones,Conj<Agente>());
        arregloDeAgentesIt->operator[](act).info.its.AgregarComoSiguiente(n);
        arregloDeAgentesIt->operator[](act).info.its.Siguiente().sancionados.AgregarRapido(arregloDeAgentesIt->operator[](act).placa);
        arregloDeAgentesIt->operator[](act).info.itcs = arregloDeAgentesIt->operator[](act).info.its.Siguiente().sancionados.CrearIt();
	}
}
//Agregadas un par de cosas para que el algoritmo sea correcto.

DiccAgentes::Iterador DiccAgentes::Iterador::Mover(Posicion p){

	arregloDeAgentesIt->operator[](act).info.pos = p;
	return *this;
}


const Conj<Agente> DiccAgentes::Iterador::ConMismasSancionesIt() const{
    return arregloDeAgentesIt->operator[](act).info.its.Siguiente().sancionados;
}

///implementacion const iterador

DiccAgentes::const_Iterador::const_Iterador(){
	Vector<AgenteCompleto> v;
	arregloDeAgentesIt = &v;
	act = 0;
}

DiccAgentes::const_Iterador::const_Iterador(Nat i,const Vector<AgenteCompleto>* vec){
    arregloDeAgentesIt = vec;
    act = i;
}

DiccAgentes::const_Iterador::const_Iterador(const const_Iterador& otro){
    arregloDeAgentesIt = otro.arregloDeAgentesIt;
    act = otro.act;
}

DiccAgentes::const_Iterador &DiccAgentes::const_Iterador::operator = (const const_Iterador& otro){
    this->arregloDeAgentesIt = otro.arregloDeAgentesIt;
    this->act = otro.act;
    return *this;
}

bool DiccAgentes::const_Iterador::HayAnterior() const{
	return (this->act != 0);
}

bool DiccAgentes::const_Iterador::HaySiguiente() const{
	return (this->act < (this->arregloDeAgentesIt->Longitud()));
}

const Info DiccAgentes::const_Iterador::Anterior() const{
	Info info;
	info.pos = arregloDeAgentesIt->operator[](act-1).info.pos;
	info.sanciones = arregloDeAgentesIt->operator[](act-1).info.sanciones;
	info.capturas = arregloDeAgentesIt->operator[](act-1).info.capturas;
	return info;
}

const Info DiccAgentes::const_Iterador::Siguiente() const{
	Info info;
	info.pos = arregloDeAgentesIt->operator[](act).info.pos;
	info.sanciones = arregloDeAgentesIt->operator[](act).info.sanciones;
	info.capturas = arregloDeAgentesIt->operator[](act).info.capturas;
	return info;
}

Agente DiccAgentes::const_Iterador::SiguienteClave() const{
    return arregloDeAgentesIt->operator[](act).placa;
}

void DiccAgentes::const_Iterador::Avanzar(){
	act++;
}

void DiccAgentes::const_Iterador::Retroceder(){
	act--;
}

bool DiccAgentes::const_Iterador::operator == (const typename DiccAgentes::const_Iterador& otro) const{
	Nat i = 0;
	while(i < arregloDeAgentesIt->Longitud() && arregloDeAgentesIt->operator[](i) == otro.arregloDeAgentesIt->operator[](i)){
            i++;
	}
	return act == otro.act && i == arregloDeAgentesIt->Longitud();
}

bool DiccAgentes::const_Iterador::operator != (const typename DiccAgentes::const_Iterador& otro) const{
    return !(this->operator==(otro));
}

const Conj<Agente> DiccAgentes::const_Iterador::ConMismasSancionesIt() const{
    return arregloDeAgentesIt->operator[](act).info.its.Siguiente().sancionados;
}

}

#endif
