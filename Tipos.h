#ifndef AED2_TIPOS_H_
#define AED2_TIPOS_H_

#include "aed2.h"

namespace aed2{

	typedef enum {izq,der,arriba,abajo} Direccion;
	typedef Nat Agente;
	typedef String Nombre;

    struct Posicion{
   			Nat x;
   			Nat y;
            Posicion() : x(1), y(1) {}
            Posicion(Nat x0, Nat y0) : x(x0), y(y0) {}
};

    std::ostream& operator<<(std::ostream& os, const Posicion& p){
            os << "(" << p.x << "," << p.y << ")" ;
    }

    bool operator==(const Posicion& p1, const Posicion& p2){
        return p1.x == p2.x && p1.y == p2.y;
    }

    bool operator!=(const Posicion& p1, const Posicion& p2){
        return !(p1 == p2);
    }

    template<class T>
    bool operator != (const typename Conj<T>::Iterador& i1,const typename Conj<T>::Iterador& i2){
        return !(i1 ==(i2));
    }
} // namespace aed2

#endif // AED2_TIPOS_H_
