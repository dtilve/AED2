//#include "CampusSeguro.h"
//#include "Campus.h"
//#include "DiccNombres.h"
#include "DiccAgentes.h"
#include "mini_test.h"

#include <string>
#include <iostream>

using namespace std;
using namespace aed2;

void DiccAgentesModificar(Nat i){
    cout << "Test numero " << i << endl;
    Nat maximo = 4*i+1;
    Nat minimo = i/4;
    DiccAgentes d(minimo,maximo);
    Nat j = 0;
    while (j <= i){
        d.Definir(minimo+j,Posicion(j,j+1));
        j++;
    }
    ASSERT_EQ(d.Definido(minimo+j+1),false);
    ASSERT_EQ(d.Definido(minimo+j-1),true);

    j = 0;
    while(j < i){
        Nat k = 0;
        DiccAgentes::Iterador it1 = d.CrearIt();
        DiccAgentes::Iterador it2 = d.CrearIt();
        while(k <= j){
            cout << "agente numero: " << it1.SiguienteClave() << endl;
            cout << "sanciones: " << it1.Siguiente().sanciones << endl;
            it1.Sancionar();
            ASSERT_EQ(d.Definido(minimo+k),true);
            cout << "sanciones: " << d.Obtener(minimo+k).sanciones << endl;
            it1.Avanzar();
            k++;
        }
        cout << "al final las sancoines son: " << d.Obtener(minimo+j).sanciones << endl;
        j++;
    }
    cout << endl;

}

void MegaTest(){

    Conj<Nat> c;
    c.AgregarRapido(1);

    Conj<Nat>::Iterador itc = c.CrearIt();
    cout << itc.Siguiente() << endl;

    Nat i = 0;
    while(i <= 10){
        DiccAgentesModificar(i);
        i++;
    }
}

void DiccAgentesTestVacio(){
    DiccAgentes d(32,57);

    DiccAgentes::Iterador it = d.CrearIt();

    ASSERT_EQ(it.HaySiguiente(),false);

    cout << "Claves: " << d.Claves() << endl;

    ASSERT_EQ(d.Definido(56),false);

    cout << "Con K sanciones lineal: " << d.conKSancionesLineal(5) << endl;

    cout << "Con K sanciones log: " <<  d.conKSancionesLog(7) << endl;
}

// ---------------------------------------------------------------------

int main(int argc, char **argv)
{
    RUN_TEST(MegaTest);
    RUN_TEST(DiccAgentesTestVacio)
	return 0;
}
