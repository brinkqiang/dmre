
#include "dmre.h"

int main( int argc, char* argv[] ) {

    Idmre* module = dmreGetModule();
    if (module)
    {
        module->Test();
        module->Release();
    }
    return 0;
}
