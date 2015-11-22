//#include "CampusSeguro.h"
#include "Campus.h"
//#include "DiccNombres.h"
//#include "DiccAgentes.h"
#include "mini_test.h"

#include <string>
#include <iostream>

using namespace std;
using namespace aed2;


// ---------------------------------------------------------------------


void CampusCrear(){
    Campus c1 = Campus(1,1);
    ASSERT_EQ(c1.Filas(),1);
    ASSERT_EQ(c1.Columnas(),1);
    Campus c2 = Campus(2,1);
    ASSERT_EQ(c2.Filas(),1);
    ASSERT_EQ(c2.Columnas(),2);
    Campus c3 = Campus(1,2);
    ASSERT_EQ(c3.Filas(),2);
    ASSERT_EQ(c3.Columnas(),1);
    Campus c4 = Campus(13,7);
    ASSERT_EQ(c4.Filas(),7);
    ASSERT_EQ(c4.Columnas(),13);
}

void CampusAgregarObstaculo(){
    Campus c = Campus(9,9);
    Posicion p1;
    p1.x = 1;
    p1.y = 1;
    Posicion p2;
    p2.x = 2;
    p2.y = 1;
    Posicion p3;
    p3.x = 1;
    p3.y = 2;
    Posicion p4;
    p4.x = 9;
    p4.y = 1;
    Posicion p5;
    p5.x = 9;
    p5.y = 9;
    Posicion p6;
    p6.x = 9;
    p6.y = 1;
    ASSERT(!c.EstaOcupada(p1));
    ASSERT(!c.EstaOcupada(p6));
    c.AgregarObstaculo(p1);
    ASSERT(c.EstaOcupada(p1));
    c.AgregarObstaculo(p2);
    ASSERT(c.EstaOcupada(p2));
    c.AgregarObstaculo(p3);
    ASSERT(c.EstaOcupada(p3));
    c.AgregarObstaculo(p4);
    ASSERT(c.EstaOcupada(p4));
    c.AgregarObstaculo(p5);
    ASSERT(c.EstaOcupada(p5));
    c.AgregarObstaculo(p6);
    ASSERT(c.EstaOcupada(p6));
}

void CampusIngreso(){
    Campus c = Campus(9,9);
    Posicion p1;
    p1.x = 1;
    p1.y = 1;
    Posicion p2;
    p2.x = 9;
    p2.y = 1;
    Posicion p3;
    p3.x = 1;
    p3.y = 9;
    Posicion p4;
    p4.x = 9;
    p4.y = 9;
    Posicion p5;
    p5.x = 5;
    p5.y = 5;
    Posicion p6;
    p6.x = 1;
    p6.y = 2;
    ASSERT(c.EsIngreso(p1));
    ASSERT(c.EsIngreso(p2));
    ASSERT(c.EsIngreso(p3));
    ASSERT(c.EsIngreso(p4));
    ASSERT(!c.EsIngreso(p5));
    ASSERT(!c.EsIngreso(p6));
}

void CampusVecinos(){
    Campus c = Campus(9,7);
    //Test 1: (1,2)
    Conj<Posicion> test1;
    test1.Agregar(Posicion(1,3));
    test1.Agregar(Posicion(2,2));
    test1.Agregar(Posicion(1,1));
    ASSERT(c.Vecinos(Posicion(1,2)) == test1);
    //Test 2: (5,5)
    Conj<Posicion> test2;
    test2.Agregar(Posicion(5,4));
    test2.Agregar(Posicion(4,5));
    test2.Agregar(Posicion(6,5));
    test2.Agregar(Posicion(5,6));
    ASSERT(c.Vecinos(Posicion(5,5)) == test2);
    //Test 3: (1,1)
    Conj<Posicion> test3;
    test3.Agregar(Posicion(1,2));
    test3.Agregar(Posicion(2,1));
    ASSERT(c.Vecinos(Posicion(1,1)) == test3);
    //Test 4: (9,7)
    Conj<Posicion> test4;
    test4.Agregar(Posicion(8,7));
    test4.Agregar(Posicion(9,6));
    ASSERT(c.Vecinos(Posicion(9,7)) == test4);
}

void CampusPosiciones(){
    Campus c(5,13);
    ASSERT(c.ProxPosicion(Posicion(2,2),izq) == Posicion(1,2))
    ASSERT(c.ProxPosicion(Posicion(2,2),der) == Posicion(3,2))
    ASSERT(c.ProxPosicion(Posicion(2,2),arriba) == Posicion(2,1))
    ASSERT(c.ProxPosicion(Posicion(2,2),abajo) == Posicion(2,3))
    ASSERT_EQ(c.Distancia(Posicion(1,1),Posicion(5,13)),16)
    ASSERT_EQ(c.Distancia(Posicion(5,13),Posicion(1,1)),16)
    ASSERT_EQ(c.Distancia(Posicion(2,2),Posicion(2,2)),0)
    ASSERT_EQ(c.Distancia(Posicion(2,3),Posicion(2,1)),2)
}

int main(int argc, char **argv)
{
    //Campus Seguro


    //Campus

    RUN_TEST(CampusCrear);
    RUN_TEST(CampusAgregarObstaculo);
    RUN_TEST(CampusIngreso);
    RUN_TEST(CampusVecinos);
    RUN_TEST(CampusPosiciones);

    //DiccNombres


    //DiccAgentes


	return 0;
}
