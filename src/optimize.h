#ifndef __OPTIMIZE__
#define __OPTIMIZE__

#include "interface.h"
#include "heroes.h"

typedef struct optimize_state_t
{
    int *cur_solution;
    int *opt_solution;
    int opt_value;
    int nodes;
    double time;
} optimize_state_t;

/*!
    \brief Branch and bound function
    \param heroes Pointer to the heroes structure
    \param params Pointer to the params structure
*/
int optimize_heroes(heroes_t *heroes, params_t *params);

#endif