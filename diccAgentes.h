//REVISAR

//constructor por defecto y con parametros
// tipo info
// tipo itConj
//destructor

#ifndef AED2_CAMPUS_H_
#define AED2_CAMPUS_H_

#include <ostream>
#include "TiposBasicos.h"

namespace aed2
{
	class DiccAgentes{
		public:
			DiccAgentes(); //vacio
			
			DiccAgentes()~;
			
			itConj Claves();
			//\InterfazFuncion{Claves}{\In{da}{diccAgentes}}{itConj(Agente)}
			//[Devuelve un iterador al conjunto de claves, es decir, las placas.]
			//[Se genera aliasing porque el iterador apunta a las claves del diccionario. El iterador no tiene la capacidad de modificar el conjunto.]
			void Definir(Nat a);
			//\InterfazFuncion{Definir}{\In{a}{Agente},}}{}
			//[Define un agente en el diccionario.]
			Info Obtener(Nat a);
			//\InterfazFuncion{Obtener}{\In{a}{Agente}, }}{$\langle Agente,Info \rangle$}
			//[Devuelve la informacion de un agente]
			Info ObtenerLog(Nat a);
			//\InterfazFuncion{ObtenerLog}{\In{a}{Agente}, }}{$\langle Agente,Info \rangle$}
			//[Devuelve la informacion de un agente]
			bool Definido?(Nat a);
			//\InterfazFuncion{Definido?}{\In{a}{Agente}, }}{bool}
			//[Chequea si el agente pasado por parametro esta definido en el diccionario.]
			class Iterador
			{
				public:
				Iterador();
				// \InterfazFuncion{CrearIt}{\In{da}{diccAgentes}}{itDiccAgentes(act,arr)}
				// [Crea un iterador]
				// [El iterador se inv\'alida si y s\'olo si se elimina el elemento siguiente del iterador sin utilizar la funcion \NombreFuncion{EliminarSiguiente}.]

				Iterador()~;

				// Iterador(const typename Lista<T>::Iterador& otro); ///esto va????
				
				// Iterador& operator = (const typename Lista<T>::Iterador& otro); ///esto va????
				
				bool HayAnterior() const;
				// \InterfazFuncion{HayAnterior}{\In{it}{itDiccAgentes(act,arr)}}{bool}
				// [Devuelve \texttt{true} si y s\'olo si en el iterador todavía quedan elementos para retroceder.]
				bool HaySiguiente() const;
				// \InterfazFuncion{HaySiguiente}{\In{it}{itDiccAgentes(act,arr)}}{bool}
				// [Devuelve \texttt{true} si y s\'olo si en el iterador todavía quedan elementos para avanzar.]
				Nodo& Anterior();  //// van los dos CONST????
				// \InterfazFuncion{Anterior}{\In{it}{itDiccAgentes(act,arr)}}{nodo}
				// [Devuelve el elemento anterior del iterador.]
				// [$res$ es modificable si y slo si $it$ es modificable.]
				Nodo& Siguiente();  //// van los dos CONST????
				// \InterfazFuncion{siguiente}{\In{it}{itDiccAgentes(act,arr)}}{nodo}
				// [Devuelve el elemento siguiente a la posici\'on del iterador.]
				// [$res$ es modificable si y s\'olo si $it$ es modificable.]
				void Avanzar();
				// \InterfazFuncion{Avanzar}{\Inout{it}{itDiccAgentes(act,arr)}}{}
				// [Avanza el iterador a la posici\'on siguiente.]
				void Retroceder();
				// \InterfazFuncion{Retroceder}{\Inout{it}{itDiccAgentes(act,arr)}}{}
				// [Retrocede el iterador a la posici\'on anterior.]
				void AgregarComoAnterior(const T& elem);
				// \InterfazFuncion{AgregarComoAnterior}{\Inout{it}{itDiccAgentes(act,arr)}, \In{a}{$\langle Agente,Info \rangle$}}{}
				// [agrega el elemento $a$ a la lista iterada, entre las posici\'ones anterior y siguiente del iterador, dejando al iterador posici\'onado de forma tal que al llamar a \NombreFuncion{Anterior} se obtenga $a$.]
				// [el elemento $a$ se agrega por referencia.]
				void AgregarComoSiguiente(const T& elem);
				// \InterfazFuncion{AgregarComoSiguiente}{\Inout{it}{itDiccAgentes(act,arr)}, \In{a}{$\langle Agente,Info \rangle$}}{}
				// [agrega el elemento $a$ a la lista iterada, entre las posici\'ones anterior y siguiente del iterador, dejando al iterador posici\'onado de forma tal que al llamar a \NombreFuncion{Siguiente} se obtenga $a$.]
				// [el elemento $a$ se agrega por referencia.]
				bool operator == (const typename Lista<T>::Iterador& otro) const;
				DiccAgentes Premiar(DiccAgentes d);	
				// \InterfazFuncion{Premiar}{\In{it}{itDiccAgentes(act,arr)}, \Inout{da}{diccAgentes}}{}
				// [Agrega una captura al agente apuntado por el iterador.]
				// [Se genera aliasing por el iterador que esta apuntando a un agente de la estructura.]
				Sancionar();
				// \InterfazFuncion{Sacionar}{\In{it}{itDiccAgentes(act,arr)},\Inout{e}{estr}}{}
				DiccAgentes Mover(DiccAgentes);
				// \InterfazFuncion{Mover}{\In{it}{itDiccAgentes(act,arr)}, \Inout{da}{diccAgentes}}{}
				// [Mueve al agente apuntado por el iterador.]
				// [Se genera aliasing por el iterador que esta apuntando a un agente de la estructura.] 
			  private:
			
			  };
		private:
	    	struct diccAgentes{
	    		Conj<nat>	conjuntoDeAgentes;
	    		vector<tuplaAg> arregloDeAgentes;
	    		//vector<conj<...>>		  tablaHash;
	    		nat mayor;
	    		nat menor;
	    		Lista<nat,Conj(nat)> ListasSanciones;
	    		vector<nat,itListaSanciones> ArregloDeSanciones;
	    	};
		Nat FuncionDeHash(Nat a);
		// \InterfazFuncion{funcionDEhash}{\In{Agente}{nat},\In{e}{estr}}{nat}
		// [Devuelve la posicion donde se va a guardar el iterador de la tabla de hash]
	};
}
