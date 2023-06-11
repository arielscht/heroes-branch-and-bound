#ifndef __INTERFACE__
#define __INTERFACE__

#include "heroes.h"

typedef struct params_t
{
    int feasibility, optimization, custom_bound;
} params_t;

/*!
    \brief Read argv keeping the parameters sent
    \param argc the number of arguments
    \param argv the array of arguments
    \param params Pointer to the params_t structure
*/
void read_params(int argc, void *argv, params_t *params);

/*!
    \brief Read the input file
    \param heroes Pointer to the heroes structure
*/
void read_input(heroes_t *heroes);

/*!
    \brief Print out the result
    \param heroes Pointer to the heroes structure
*/
int show_results(heroes_t *heroes);

/*!
    \brief Debug print
    \param heroes Pointer to the heroes structure
*/
void print_heroes(heroes_t *heroes);

#endif