#include "mini_test.h"
#include "CampusSeguro.h"

#include <string>
#include <iostream>

using namespace aed2;


// ---------------------------------------------------------------------

/**
 * Ejemplo de caso de test, con llamadas a las rutinas de aserción
 * definidas en mini_test.h
 */

void test_simple()
{
    diccNombres hippies = diccNombres();
    diccNombres estudiantes = diccNombres();

    Nombre d = "Ana";
    Posicion p;
    p.x = 5;
    p.y = 1;

    hippies.Definir(d,p);
    //ASSERT(hippies.Definido(d));
    //ASSERT(not(hippies.Definido(c)))
}

void DiccAgentesModificar(Nat i){
    cout << endl;
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
        while(k <= j){
            it1.Sancionar();
            ASSERT_EQ(d.Definido(minimo+k),true);
            it1.Avanzar();
            k++;
        }
        j++;
    }
}

void MegaTest(){

    Conj<Nat> c;
    c.AgregarRapido(1);

    Conj<Nat>::Iterador itc = c.CrearIt();
    cout << itc.Siguiente() << endl;

    Nat i = 0;
    while(i <= 25){
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

void CampusSeguroIniciar(){
    //Paso 1
    Campus c(4,4);
    c.AgregarObstaculo(Posicion(3,3));
    Dicc<Placa,Posicion> da;
    da.Definir(1,Posicion(2,2));
    da.Definir(2,Posicion(4,2));
    CampusSeguro cs(c,da);
    //Paso 2
    cs.IngresarHippie("h1",Posicion(2,1));
    cs.IngresarHippie("h2",Posicion(4,1));
    //Paso 3
    cs.IngresarEstudiante("e1",Posicion(3,1));
    cout << "Cantidad de Hippies: " << cs.CantHippies() << endl;
    //Paso 4
    cs.IngresarEstudiante("e2",Posicion(3,4));
    cout << "Cantidad de Estudiantes: " << cs.CantEstudiantes() << endl;
    //Paso 5
    //cs.MoverHippie("e1");
    //Paso 6
    //cs.IngresarHippie("h3",Posicion(3,1));
}

int main(int argc, char **argv)
{
    RUN_TEST(CampusSeguroIniciar);
}
