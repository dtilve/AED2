#include "mini_test.h"
#include "diccNombres.h"

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

    Nombre d = "Dana";
    Posicion p;
    p.x = 5;
    p.y = 1;
    hippies.Definir("Dana",p);
    //ASSERT(hippies.Definido(d));
  //  ASSERT(not(hippies.Definido(c)))
}

int main(int argc, char **argv)
{
    RUN_TEST(test_simple);
	return 0;
}
