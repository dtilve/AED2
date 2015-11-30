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
    ASSERT(hippies.Definido(d));
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
    cout << endl;
    cout << "Paso 1: Creo CampusSeguro" << endl;
    Campus c(5,4);
    c.AgregarObstaculo(Posicion(3,3));
    Dicc<Placa,Posicion> da;
    da.Definir(1,Posicion(2,2));
    da.Definir(2,Posicion(4,2));
    CampusSeguro cs(c,da);
    cout << endl;

    cout << "Paso 2: Ingreso hippies" << endl;
    cs.IngresarHippie("h1",Posicion(2,1));
    cs.IngresarHippie("h2",Posicion(4,1));
    cout << "Cantidad de Estudiantes: " << cs.CantEstudiantes() << endl;
    cout << "Cantidad de Hippies: " << cs.CantHippies() << endl << endl;

    cout << "Paso 3: Ingreso un estudiante (deberia convertirse en hippie)" << endl;
    cs.IngresarEstudiante("e1",Posicion(3,1));
    cout << "ahora su posicion es: " << cs.PosicionEstudianteYHippie("e1") << endl;
    cout << "Cantidad de Estudiantes: " << cs.CantEstudiantes() << endl;
    cout << "Cantidad de Hippies: " << cs.CantHippies() << endl << endl;

    cout << "Paso 4: Ingreso un estudiante como seniuelo" << endl;
    cs.IngresarEstudiante("e2",Posicion(3,4));
    cout << "ahora su posicion es: " << cs.PosicionEstudianteYHippie("e2") << endl;
    cout << "Cantidad de Estudiantes: " << cs.CantEstudiantes() << endl;
    cout << "Cantidad de Hippies: " << cs.CantHippies() << endl << endl;

    cout << "Paso 5: Muevo el hippie convertido (deberia moverse hacia el seniuelo)" << endl;
    cs.MoverHippie("e1");
    cout << "ahora su posicion es: " << cs.PosicionEstudianteYHippie("e1") << endl;
    cout << "Cantidad de Estudiantes: " << cs.CantEstudiantes() << endl;
    cout << "Cantidad de Hippies: " << cs.CantHippies() << endl << endl;

    cout << "Paso 6: Ingreso un hippie que acorrala al que movi, eliminandolo del mapa" << endl;
    cs.IngresarHippie("h3",Posicion(3,1));
    cout << "Cantidad de Estudiantes: " << cs.CantEstudiantes() << endl;
    cout << "Cantidad de Hippies: " << cs.CantHippies() << endl;
    cout << "Capturas de a1: " << cs.CantHippiesAtrapados(1) << endl;
    cout << "Capturas de a2: " << cs.CantHippiesAtrapados(2) << endl;
    cout << "Mas vigilante: " << cs.MasVigilante() << endl;
    cout << "Con 0 sanciones: " << cs.ConKSanciones(0) << endl;
    cout << "Con 1 sancion: " << cs.ConKSanciones(1) << endl << endl;

    cout << "Test de posiciones" << endl;
    cout << "Posicion de e2: " << cs.PosicionEstudianteYHippie("e2") << endl;
    cout << "Posicion de h1: " << cs.PosicionEstudianteYHippie("h1") << endl;
    cout << "Posicion de h2: " << cs.PosicionEstudianteYHippie("h2") << endl;
    cout << "Posicion de h3: " << cs.PosicionEstudianteYHippie("h3") << endl;
    cout << "Posicion de a1: " << cs.PosAgente(1) << endl;
    cout << "Posicion de a2: " << cs.PosAgente(2) << endl;
    cout << endl;
}

void CampusSeguroSancionesYCapturas(){
    cout << endl;
    cout << "Paso 1: Creo CampusSeguro" << endl;
    Campus c(3,3);
    Dicc<Placa,Posicion> da;
    da.Definir(1,Posicion(1,1));
    da.Definir(2,Posicion(3,1));
    da.Definir(3,Posicion(2,2));
    da.Definir(4,Posicion(1,3));
    da.Definir(5,Posicion(3,3));
    CampusSeguro cs(c,da);
    cout << "Mas vigilante: " << cs.MasVigilante() << endl;
    cout << endl;

    cout << "Paso 2: Ingreso un estudiante" << endl;
    cs.IngresarEstudiante("e1",Posicion(2,3));
    cout << "Con 0 sanciones: " << cs.ConKSanciones(0) << endl;
    cout << "Con 1 sancion: " << cs.ConKSanciones(1) << endl;
    cout << "ConMismasSanciones(1) = " << cs.ConMismasSanciones(1) << endl;
    cout << "Sanciones del agente 1: " << cs.CantSanciones(1) << endl;
    cout << "Sanciones del agente 2: " << cs.CantSanciones(2) << endl;
    cout << "Sanciones del agente 3: " << cs.CantSanciones(3) << endl;
    cout << "Sanciones del agente 4: " << cs.CantSanciones(4) << endl;
    cout << "Sanciones del agente 5: " << cs.CantSanciones(5) << endl;
    cout << endl;

    cout << "Paso 3: Ingreso un hippie que deberia desaparecer al instante" << endl;
    cs.IngresarHippie("h1",Posicion(2,1));
    cout << "Cantidad de hippies: " << cs.CantHippies() << endl;
    cout << "Con 0 sanciones: " << cs.ConKSanciones(0) << endl;
    cout << "Con 1 sancion: " << cs.ConKSanciones(1) << endl;
    cout << "Capturas del agente 1: " << cs.CantHippiesAtrapados(1) << endl;
    cout << "Capturas del agente 2: " << cs.CantHippiesAtrapados(2) << endl;
    cout << "Capturas del agente 3: " << cs.CantHippiesAtrapados(3) << endl;
    cout << "Capturas del agente 4: " << cs.CantHippiesAtrapados(4) << endl;
    cout << "Capturas del agente 5: " << cs.CantHippiesAtrapados(5) << endl;
    cout << "Mas vigilante: " << cs.MasVigilante() << endl;
    cout << endl;

    cout << "Paso 4: Retiro al estudiante" << endl;
    cs.MoverEstudiante("e1",abajo);
    cout << "Cantidad de estudiantes: " << cs.CantEstudiantes() << endl;
    cout << endl;

    cout << "Paso 5: Ingreso a otro hippie que deberia desaparecer al instante. El mas vigilante deberia ser ahora el agente 3" << endl;
    cs.IngresarHippie("h2",Posicion(2,3));
    cout << "Cantidad de hippies: " << cs.CantHippies() << endl;
    cout << "Con 0 sanciones: " << cs.ConKSanciones(0) << endl;
    cout << "Con 1 sancion: " << cs.ConKSanciones(1) << endl;
    cout << "Capturas del agente 1: " << cs.CantHippiesAtrapados(1) << endl;
    cout << "Capturas del agente 2: " << cs.CantHippiesAtrapados(2) << endl;
    cout << "Capturas del agente 3: " << cs.CantHippiesAtrapados(3) << endl;
    cout << "Capturas del agente 4: " << cs.CantHippiesAtrapados(4) << endl;
    cout << "Capturas del agente 5: " << cs.CantHippiesAtrapados(5) << endl;
    cout << "Mas vigilante: " << cs.MasVigilante() << endl;
    cout << endl;
}

void CampusSeguroMover(){
    cout << endl;
    cout << "Paso 1: Creo CampusSeguro con un solo agente (a1)" << endl;
    Campus c(5,5);
    Dicc<Placa,Posicion> da;
    da.Definir(1,Posicion(3,3));
    CampusSeguro cs(c,da);
    cout << endl;

    cout << "Paso 2: Muevo al agente dos veces" << endl;
    cs.MoverAgente(1);
    cout << "Posicion de a1: " << cs.PosAgente(1) << endl;
    cs.MoverAgente(1);
    cout << "Posicion de a1: " << cs.PosAgente(1) << endl;
    cout << endl;

    cout << "Paso 3: Ingreso a un hippie y muevo al agente a hl" << endl;
    cout << "Inrgeso al hippie h1" << endl;
    cs.IngresarHippie("h1",Posicion(1,5));
    cout << "Posicion de h1: " << cs.PosicionEstudianteYHippie("h1") << endl;
    cout << "Muevo a a1" << endl;
    cs.MoverAgente(1);
    cout << "Posicion de a1: " << cs.PosAgente(1) << endl;

    cout << "Paso 4: Ingreso un estudiante e1 y muevo al hippie hacia el" << endl;
    cout << "Inrgeso al estudiante e1" << endl;
    cs.IngresarEstudiante("e1",Posicion(5,1));
    cout << "Posicion de e1: " << cs.PosicionEstudianteYHippie("e1") << endl;
    cout << "Muevo a h1" << endl;
    cs.MoverHippie("h1");
    cout << "Posicion de h1: " << cs.PosicionEstudianteYHippie("h1") << endl;
    cout << "Muevo a h1" << endl;
    cs.MoverHippie("h1");
    cout << "Posicion de h1: " << cs.PosicionEstudianteYHippie("h1") << endl;
    Nat i = 0;
    while(i < 9){
        cout << "Muevo a h1" << endl;
        cs.MoverHippie("h1");
        cout << "Posicion de h1: " << cs.PosicionEstudianteYHippie("h1") << endl;
        i++;
    }
    cout << endl;

    cout << "Paso 5: e1 no quiere ser convertido y escapa de la perdicion porque quiere aprobar Algo2" << endl;
    cout << "Muevo a e1 hacia abajo" << endl;
    cs.MoverEstudiante("e1",abajo);
    cout << "Posicion de e1: " << cs.PosicionEstudianteYHippie("e1") << endl;
    cout << "Muevo a e1 hacia la izquierda" << endl;
    cs.MoverEstudiante("e1",izq);
    cout << "Posicion de e1: " << cs.PosicionEstudianteYHippie("e1") << endl;
    cout << "Muevo a e1 hacia abajo" << endl;
    cs.MoverEstudiante("e1",abajo);
    cout << "Posicion de e1: " << cs.PosicionEstudianteYHippie("e1") << endl;
    cout << "Muevo a e1 hacia la derecha" << endl;
    cs.MoverEstudiante("e1",der);
    cout << "Posicion de e1: " << cs.PosicionEstudianteYHippie("e1") << endl;
    cout << "Muevo a e1 hacia arriba" << endl;
    cs.MoverEstudiante("e1",arriba);
    cout << "Posicion de e1: " << cs.PosicionEstudianteYHippie("e1") << endl;
    cout << endl;
}

int main(int argc, char **argv)
{
    RUN_TEST(CampusSeguroIniciar);
    cout << endl;
    RUN_TEST(CampusSeguroSancionesYCapturas);
    cout << endl;
    RUN_TEST(CampusSeguroMover);
    //RUN_TEST(MegaTest);
}
