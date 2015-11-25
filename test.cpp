//#include "CampusSeguro.h"
//#include "Campus.h"
//#include "DiccNombres.h"
#include "DiccAgentes.h"
#include "mini_test.h"

#include <string>
#include <iostream>

using namespace std;
using namespace aed2;

void DiccAgentesCrear(){
    DiccAgentes d(0,100);
    d.~DiccAgentes();
}

void DiccAgentesDefinir(){
    //Definiendo agentes
    DiccAgentes d(0,4);
    d.Definir(0,Posicion(0,1));
    d.Definir(1,Posicion(1,2));
    d.Definir(2,Posicion(2,3));
    //d.Definir(3,Posicion(3,4));
    //d.Definir(4,Posicion(4,5));
    cout << d.Claves().Cardinal() << endl;
}

// ---------------------------------------------------------------------

int main(int argc, char **argv)
{
    RUN_TEST(DiccAgentesCrear);
    RUN_TEST(DiccAgentesDefinir);
	return 0;
}
