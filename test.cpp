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

// ---------------------------------------------------------------------

int main(int argc, char **argv)
{
    RUN_TEST(DiccAgentesCrear);
	return 0;
}
