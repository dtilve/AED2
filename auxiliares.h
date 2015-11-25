#include <ostream>
#include "aed2.h"

struct Posicion{
   			Nat x;
   			Nat y;
            Posicion() : x(1), y(1) {}
            Posicion(Nat x0, Nat y0) : x(x0), y(y0) {}
};

bool operator==(const Posicion& p1, const Posicion& p2){
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const Posicion& p1, const Posicion& p2){
    return !(p1 == p2);
}
