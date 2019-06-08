#include <iostream>
#include "veritiontest.h"

using namespace std;

int main( int argc, char** argv ) {

    if ( argc != 3 ) {
        cerr << "Usage verition_test <quote_file> <trade_file>" << endl;
        exit(1);
    }

    VeritionTest vt( argv[1], argv[2]);
    vt.run();
    vt.results();
}
