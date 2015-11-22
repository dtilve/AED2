#include <iostream>
#include "Campus.h"

using namespace std;
using namespace aed2;

int main(){
    Campus c = Campus(3,3);
    Posicion p;
    p.x = 1;
    p.y = 1;
    c.AgregarObstaculo(p,c);
    p.y = 3;
    cout << c.EstaOcupada(p,c) << endl;
}
