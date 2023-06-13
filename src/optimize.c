#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "optimize.h"

/* ============================== Auxiliary Functions ============================== */

int check_friendships(heroes_t *heroes, optimize_state_t *optimize, int cur_hero)
{
    for (int i = 0; i < heroes->friendships_qty; i++)
    {
        if (heroes->friendships[i].hero1 == cur_hero && heroes->friendships[i].hero2 < cur_hero)
            return optimize->cur_solution[heroes->friendships[i].hero2 - 1];
        else if (heroes->friendships[i].hero2 == cur_hero && heroes->friendships[i].hero1 < cur_hero)
            return optimize->cur_solution[heroes->friendships[i].hero1 - 1];
    }

    return 2;
}

/* ============================== Auxiliary Functions ============================== */

/* ============================== Internal Functions ============================== */

int profit(int *solution, heroes_t *heroes)
{
    int profit = 0;
    for (int i = 0; i < heroes->conflicts_qty; i++)
        if ((solution[heroes->conflicts[i].hero1 - 1] == 1 && solution[heroes->conflicts[i].hero2 - 1] == 1) ||
            (solution[heroes->conflicts[i].hero1 - 1] == 0 && solution[heroes->conflicts[i].hero2 - 1] == 0))
            profit++;

    return profit;
}

int custom_bound(int *partial_solution)
{
    return 0;
}

int naive_bound(int *partial_solution)
{
    return 0;
}

void optimize_heroes_recursive(heroes_t *heroes, params_t *params, optimize_state_t *optimize, int depth)
{
    int cur_opt, available_opt;
    optimize->nodes++;

    if (depth == heroes->quantity)
    {
        cur_opt = profit(optimize->cur_solution, heroes);
        if (cur_opt < optimize->opt_value)
        {
            optimize->opt_value = cur_opt;
            memcpy(optimize->opt_solution, optimize->cur_solution, heroes->quantity * sizeof(int));
        }
    }

    available_opt = 2;
    if (params->feasibility)
        if (depth != heroes->quantity)
            available_opt = check_friendships(heroes, optimize, depth + 1);

    // FAZEMOS O BOUND AQUI

    if (depth != heroes->quantity)
    {
        int init = available_opt == 2 ? 0 : available_opt;
        int cond = available_opt == 2 ? available_opt : init + 1;
        for (int i = init; i < cond; i++)
        {
            optimize->cur_solution[depth] = i;
            optimize_heroes_recursive(heroes, params, optimize, depth + 1);
            optimize->cur_solution[depth] = 0;
        }
    }
}

/* ============================== Internal Functions ============================== */

int partial_bound(int *partial_solution, params_t *params)
{
    if (params->custom_bound)
        return custom_bound(partial_solution);
    else
        return naive_bound(partial_solution);
}

int optimize_heroes(heroes_t *heroes, params_t *params)
{
    optimize_state_t optimize;

    optimize.cur_solution = alloc_array(heroes->quantity, sizeof(int));
    optimize.opt_solution = alloc_array(heroes->quantity, sizeof(int));
    optimize.opt_value = INT_MAX;
    optimize.nodes = 0;

    optimize_heroes_recursive(heroes, params, &optimize, 0);

    for (int i = 0; i < heroes->quantity; i++)
    {
        printf("%d ", optimize.opt_solution[i]);
        heroes->heroes[i].group = optimize.opt_solution[i];
    }
    printf("\nNODES: %d\n", optimize.nodes);

    return 0;
}
