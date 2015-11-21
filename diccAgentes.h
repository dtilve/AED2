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
	};
}
