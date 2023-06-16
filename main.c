#include <stdio.h>
#include "src/interface.h"
#include "src/heroes.h"
#include "src/optimize.h"

int main(int argc, char **argv)
{
    params_t params;
    heroes_t heroes;

    read_params(argc, argv, &params);
    read_input(&heroes);

    optimize_heroes(&heroes, &params);
    // print_heroes(&heroes);

    heroes_destroy(&heroes);
    return 0;
}