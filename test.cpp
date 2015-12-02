
#include "Driver.h"
#include "mini_test.h"

#include <string>
#include <iostream>

using namespace aed2;


// ---------------------------------------------------------------------

void test_agregar_obstaculos() {

	Driver campus;


	/*campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	campus.comenzarRastrillaje(agentes);


	Posicion p;
	p.x = 2;
	p.y = 3;

	campus.agregarObstaculo(p);


	ASSERT(campus.ocupada(p) == true);

	Posicion p2;
	p2.x = 1;
	p2.y = 1;

	ASSERT(campus.ocupada(p2) == false);*/


}

void test_ingresa_estudiante(){
	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	campus.comenzarRastrillaje(agentes);

	Posicion p2;
	p2.x = 1;
	p2.y = 1;

	Nombre s = "pepe";
	campus.ingresarEstudiante(s,p2);

	//ASSERT(campus.ocupada(p2) == true);

	Posicion p3 = campus.posEstudianteYHippie(s);
	ASSERT(p3.x == p2.x && p3.y == p3.x);
}

// DIFICIL
void test_ingresa_hippie_y_convierte() {
	// Testea que cuando ingresa un hippie y esta rodeado de estudiantes se convierte
	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	campus.comenzarRastrillaje(agentes);

	Posicion p1;
	p1.x = 1;
	p1.y = 1;

	Posicion p2;
	p2.x = 2;
	p2.y = 1;


	Posicion p3;
	p3.x = 3;
	p3.y = 1;

	Nombre s1 = "pepe";
	Nombre s2 = "pepo";
	Nombre s3 = "pepa";

	// Ingreso 3 estudiantes uno al lado del otro
	campus.ingresarEstudiante(s1,p1);
	campus.ingresarEstudiante(s2,p2);
	campus.ingresarEstudiante(s3,p3);

	// Avanzo el estudiante del medio
	campus.moverEstudiante(s2,abajo);

	// Ahora hago ingresar un hippie,se tiene que convertir a estudiante
	Nombre h1 = "wololoHippie";
	campus.ingresarHippie(h1,p2);
	ASSERT(campus.cantEstudiantes() == 4);
	ASSERT(campus.cantHippies() == 0);
}

// DIFICIL
void test_mueve_estudiante_y_convierte() {
	// Testea que cuando se mueve un estudiante y rodea a un hippie se convierte
	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	campus.comenzarRastrillaje(agentes);

	Posicion p1;
	p1.x = 1;
	p1.y = 1;

	Posicion p2;
	p2.x = 2;
	p2.y = 1;


	Posicion p3;
	p3.x = 3;
	p3.y = 1;

	Nombre s1 = "pepe";
	Nombre s2 = "pepo";
	Nombre s3 = "pepa";

	// Ingreso 3 estudiantes uno al lado del otro
	campus.ingresarEstudiante(s1,p1);
	campus.ingresarEstudiante(s2,p2);
	campus.ingresarEstudiante(s3,p3);

	// Avanzo el estudiante del medio
	campus.moverEstudiante(s2,abajo);
	campus.moverEstudiante(s2,abajo);

	// Ahora hago ingresar un hippie Y NO SE TIENE QUE CONVERTIR
	Nombre h1 = "wololoHippie";
	campus.ingresarHippie(h1,p2);

	ASSERT(campus.cantEstudiantes() == 3);
	ASSERT(campus.cantHippies() == 1);

	// Muevo el estudiante hacia arriba y tiene que convertir talannnn
	campus.moverEstudiante(s2,arriba);

	ASSERT(campus.cantEstudiantes() == 4);
	ASSERT(campus.cantHippies() == 0);

}

void test_mover_estudiante() {
	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	campus.comenzarRastrillaje(agentes);

	Posicion p2;
	p2.x = 1;
	p2.y = 1;

	Nombre s = "pepe";
	campus.ingresarEstudiante(s,p2);
	campus.moverEstudiante(s, abajo);

	Posicion p3;
	p3.x = 1;
	p3.y = 2;

	//ASSERT(campus.ocupada(p2) == false);
	//ASSERT(campus.ocupada(p3) == true);

	Posicion p = campus.posEstudianteYHippie(s);
	ASSERT(p3.x == p.x && p3.y == p.y);

}

void test_mover_estudiante_fuera() {
	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	campus.comenzarRastrillaje(agentes);

	Posicion p2;
	p2.x = 1;
	p2.y = 1;

	Nombre s = "pepe";
	campus.ingresarEstudiante(s,p2);
	campus.moverEstudiante(s, arriba);

	ASSERT(campus.ocupada(p2) == false);
	ASSERT(campus.cantEstudiantes() == 0);
}

void test_ingresa_hippie() {
	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	campus.comenzarRastrillaje(agentes);

	Posicion p2;
	p2.x = 1;
	p2.y = 1;

	Nombre s = "pepe";
	campus.ingresarHippie(s,p2);

	//ASSERT(campus.ocupada(p2) == true);

	Posicion p = campus.posEstudianteYHippie(s);
	ASSERT(p2.x == p.x && p2.y == p.y);

}

void test_ingresa_hippie_y_estudiante() {
	// Idea de este test es probar el funcionamiento del Trie
	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	campus.comenzarRastrillaje(agentes);

	Posicion p2;
	p2.x = 1;
	p2.y = 1;

	Nombre s = "pepe";
	campus.ingresarHippie(s,p2);

	Posicion p3;
	p3.x = 1;
	p3.y = 2;

	Nombre t = "pepa";
	campus.ingresarEstudiante(t,p3);

	Posicion p;
	p.x = 1;
	p.y = 3;

	Nombre r = "pepen";
	campus.ingresarEstudiante(r,p);


	ASSERT(campus.iesimoHippie(0) == s);

	// No importa el orden, pero tienen que estar los dos
	ASSERT(campus.iesimoEstudiante(0) == t || campus.iesimoEstudiante(1) == t);
	ASSERT(campus.iesimoEstudiante(0) == r || campus.iesimoEstudiante(1) == r);

}


void test_mover_hippie_a_estudiante() {
	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	campus.comenzarRastrillaje(agentes);

	Posicion p;
	p.x = 1;
	p.y = 1;

	Nombre t = "pepa";
	campus.ingresarEstudiante(t,p);

	campus.moverEstudiante(t, abajo);
	campus.moverEstudiante(t, abajo);
	campus.moverEstudiante(t, abajo);
	campus.moverEstudiante(t, abajo);
	campus.moverEstudiante(t, abajo);

	// Baja el estudiante
	Posicion p3 = campus.posEstudianteYHippie(t);
	ASSERT(p3.x == 1 && p3.y == 6);

	Posicion p2;
	p2.x = 1;
	p2.y = 1;

	Nombre s = "pepe";
	campus.ingresarHippie(s,p2);
	campus.moverHippie(s);

	// El hippie se mueve hacia abajo
	Posicion p4 = campus.posEstudianteYHippie(s);
	ASSERT(p4.x == 1 && p4.y == 2);

	Posicion p5;
	p5.x = 3;
	p5.y = 1;

	Nombre r = "pepo";
	campus.ingresarEstudiante(r,p5);

	// El hippie se mueve hacia el nuevo estudiante
	campus.moverHippie(s);
	p4 = campus.posEstudianteYHippie(s);
	ASSERT((p4.x == 1 && p4.y == 1) || (p4.x == 2 && p4.y == 2) );

}


void test_mover_hippie_a_ingreso() {
	// Idea del test: el hippie se mueve hacia el estudiante
	// Luego el estudiante se borra
	// Luego el hippie se mueve al ingreso mas cercano

	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	campus.comenzarRastrillaje(agentes);


	Posicion p;
	p.x = 1;
	p.y = 1;

	Nombre t = "pepa";
	campus.ingresarEstudiante(t,p);

	for (int i=0; i < 5; i++) {
		campus.moverEstudiante(t, abajo);
	}

	// Baja el estudiante
	Posicion p3 = campus.posEstudianteYHippie(t);
	ASSERT(p3.x == 1 && p3.y == 6);

	Posicion p2;
	p2.x = 1;
	p2.y = 1;

	Nombre s = "pepe";
	campus.ingresarHippie(s,p2);
	campus.moverHippie(s);
	campus.moverHippie(s);

	// El hippie se mueve hacia abajo
	Posicion p4 = campus.posEstudianteYHippie(s);
	ASSERT(p4.x == 1 && p4.y == 3);

	// Hago salir al estudiante, lo muevo a la derecha para no pisar el hippie
	campus.moverEstudiante(t, der);
	for (int i=0; i < 6; i++) {
		campus.moverEstudiante(t, arriba);
	}

	ASSERT(campus.cantEstudiantes() == 0);

	// Muevo al hippie , tiene que ir al ingreso mas cercano
	campus.moverHippie(s);
	p4 = campus.posEstudianteYHippie(s);

	ASSERT(p4.x == 1 && p4.y == 2);

}


void test_comenzar_rastrillaje_simple() {
	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	Agente a = 1;

	Posicion p;
	p.x = 1;
	p.y = 1;

	agentes.Definir(a,p);

	campus.comenzarRastrillaje(agentes);
	ASSERT(campus.cantAgentes() == 1);
}


void test_rastrillaje_mover_hacia_hippie() {
	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	Agente a = 1;

	Posicion p;
	p.x = 1;
	p.y = 1;

	agentes.Definir(a,p);

	campus.comenzarRastrillaje(agentes);

	Posicion ph;
	ph.x = 5;
	ph.y = 1;

	Nombre h = "hippie";
	campus.ingresarHippie(h,ph);

	campus.moverAgente(a);

	Posicion p4 = campus.posAgente(a);

	ASSERT(p4.x == 2 && p4.y == 1);

}


void test_captura_hippie_entre_agentes()
{
	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	Agente a = 1;
	Agente a2 = 2;
	Agente a3 = 3;

	Posicion p;
	p.x = 1;
	p.y = 1;

	Posicion p2;
	p2.x = 2;
	p2.y = 2;

	Posicion p3;
	p3.x = 3;
	p3.y = 1;

	agentes.Definir(a,p);
	agentes.Definir(a2,p2);
	agentes.Definir(a3,p3);

	campus.comenzarRastrillaje(agentes);

	Posicion ph;
	ph.x = 2;
	ph.y = 1;

	Nombre h = "hippie";

	campus.ingresarHippie(h,ph);

	ASSERT(campus.cantHippiesAtrapados(a) == 1);
	ASSERT(campus.cantHippiesAtrapados(a2) == 1);
	ASSERT(campus.cantHippiesAtrapados(a3) == 1);

	ASSERT(campus.masVigilante() == a || campus.masVigilante() == a2 || campus.masVigilante() == a3);

}

void test_captura_estudiante()
{
	Driver campus;
	campus.crearCampus(10,10);

	Dicc<Agente,Posicion> agentes;
	Agente a = 1;
	Agente a2 = 2;
	Agente a3 = 3;

	Posicion p;
	p.x = 1;
	p.y = 1;

	Posicion p2;
	p2.x = 2;
	p2.y = 2;

	Posicion p3;
	p3.x = 3;
	p3.y = 1;

	agentes.Definir(a,p);
	agentes.Definir(a2,p2);
	agentes.Definir(a3,p3);

	campus.comenzarRastrillaje(agentes);

	Posicion pe;
	pe.x = 2;
	pe.y = 1;

	Nombre e = "pepe";
	campus.ingresarEstudiante(e,pe);

	ASSERT(campus.conMismasSanciones(a).Cardinal() == 3 );
	ASSERT(campus.conMismasSanciones(a2).Cardinal() == 3 );
	ASSERT(campus.conMismasSanciones(a3).Cardinal() == 3 );
	Nat c = campus.conKSanciones(1).Cardinal();
	ASSERT(c == 3);

	Nat c2 = campus.conKSanciones(0).Cardinal();
	ASSERT(c2 == 0 );


}

void test_mas_vigilante()
{
// 3 primeras lineas antes de que ingresen los estudiantes
//     1   2   3   4   5
// 1 | A |   | A |   | O
// 2 |   | A |   | O |
// 3 ...
// Los hippies ingresan en (2,1) y (4,1) los huecos. El Agente en (3,1) se transforma en el mas vigilante
	Driver campus;
	campus.crearCampus(10,10);

	Posicion o;
	o.x = 4;
	o.y = 2;

	campus.agregarObstaculo(o);

	Posicion o2;
	o2.x = 5;
	o2.y = 1;

	campus.agregarObstaculo(o2);


	Dicc<Agente,Posicion> agentes;
	Agente a = 1;
	Agente a2 = 2;
	Agente a3 = 3;

	Posicion p;
	p.x = 1;
	p.y = 1;

	Posicion p2;
	p2.x = 2;
	p2.y = 2;

	Posicion p3;
	p3.x = 3;
	p3.y = 1;

	agentes.Definir(a,p);
	agentes.Definir(a2,p2);
	agentes.Definir(a3,p3);

	campus.comenzarRastrillaje(agentes);

	Posicion ph;
	ph.x = 2;
	ph.y = 1;

	Nombre h = "hippie";
	campus.ingresarHippie(h,ph);

	Posicion ph2;
	ph2.x = 4;
	ph2.y = 1;

	Nombre h2 = "hippie2";
	campus.ingresarHippie(h2,ph2);


	ASSERT(campus.cantHippiesAtrapados(a) == 1);
	ASSERT(campus.cantHippiesAtrapados(a2) == 1);
	ASSERT(campus.cantHippiesAtrapados(a3) == 2);

	ASSERT(campus.masVigilante() == a3);

}








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
    Dicc<Agente,Posicion> da;
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
    Dicc<Agente,Posicion> da;
    da.Definir(1,Posicion(1,1));
    da.Definir(2,Posicion(3,1));
    da.Definir(3,Posicion(2,2));
    da.Definir(4,Posicion(1,3));
    da.Definir(5,Posicion(3,3));
    CampusSeguro cs1(c,da);
    CampusSeguro cs;
    cs = cs1;
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
    Dicc<Agente,Posicion> da;
    da.Definir(1,Posicion(3,3));
    CampusSeguro cs1(c,da);
    CampusSeguro cs;
    cs = cs1;
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

void MemoryTest(){
    //DiccNombres
    diccNombres dN;

    dN.Definir("esto es un texto mas largo",Posicion(3,3));
    dN.Definir("esto es un texto",Posicion(2,2));
    dN.Definir("esto es un",Posicion(4,4));

}

int main(int argc, char **argv)
{
    //RUN_TEST(test_agregar_obstaculos);
	/*RUN_TEST(test_ingresa_estudiante);
	RUN_TEST(test_mover_estudiante);
	RUN_TEST(test_mover_estudiante_fuera);
	RUN_TEST(test_ingresa_hippie);
	RUN_TEST(test_ingresa_hippie_y_estudiante);
	RUN_TEST(test_mover_hippie_a_estudiante);
	RUN_TEST(test_mover_hippie_a_ingreso);
	RUN_TEST(test_ingresa_hippie_y_convierte);
	RUN_TEST(test_mueve_estudiante_y_convierte);
	RUN_TEST(test_comenzar_rastrillaje_simple);
	RUN_TEST(test_rastrillaje_mover_hacia_hippie);
	RUN_TEST(test_captura_hippie_entre_agentes);
	RUN_TEST(test_captura_estudiante);
	RUN_TEST(test_mas_vigilante);*/

	//RUN_TEST(CampusSeguroIniciar);
    //cout << endl;
    //RUN_TEST(CampusSeguroSancionesYCapturas);
    //cout << endl;
    //RUN_TEST(CampusSeguroMover);
    //RUN_TEST(MegaTest);

    RUN_TEST(MemoryTest);

	return 0;
}

