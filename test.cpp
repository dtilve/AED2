//#include "CampusSeguro.h"
#include "Campus.h"
//#include "DiccNombres.h"
//#include "DiccAgentes.h"
#include "mini_test.h"

#include <string>
#include <iostream>

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

int main(int argc, char **argv)
{
    //Campus Seguro


    //Campus

    RUN_TEST(CampusCrear);
    RUN_TEST(CampusAgregarObstaculo);
    RUN_TEST(CampusIngreso);


    //DiccNombres


    //DiccAgentes


	return 0;
}
