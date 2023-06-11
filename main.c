#include <stdio.h>
#include "src/interface.h"
#include "src/heroes.h"

int main(int argc, void *argv)
{
    params_t params;
    heroes_t heroes;

    read_params(argc, argv, &params);
    read_input(&heroes);

    // print_heroes(&heroes);

    heroes_destroy(&heroes);
    return 0;
}