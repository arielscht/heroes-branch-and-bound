#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <sys/time.h>
#include "optimize.h"

/* ============================== Auxiliary Functions ============================== */

int check_friendships(heroes_t *heroes, optimize_state_t *optimize, int cur_hero)
{
    int hero1, hero2;
    for (int i = 0; i < heroes->friendships_qty; i++)
    {
        hero1 = heroes->friendships[i].hero1;
        hero2 = heroes->friendships[i].hero2;
        if (hero1 == cur_hero && hero2 < cur_hero)
            return optimize->cur_solution[hero2 - 1];
        else if (hero2 == cur_hero && hero1 < cur_hero)
            return optimize->cur_solution[hero1 - 1];
    }

    return 2;
}

int check_conflicts(heroes_t *heroes, int *partial_solution, int cur_hero, int cur_group)
{
    int hero1, hero2;
    int counter = 0;

    for (int i = 0; i < heroes->conflicts_qty; i++)
    {
        hero1 = heroes->conflicts[i].hero1;
        hero2 = heroes->conflicts[i].hero2;
        if (hero1 == cur_hero && hero2 < cur_hero && partial_solution[hero2 - 1] == cur_group)
            counter++;
        else if (hero2 == cur_hero && hero1 < cur_hero && partial_solution[hero1 - 1] == cur_group)
            counter++;
    }

    return counter;
}

int count_triangles(heroes_t *heroes, int depth)
{
    int hero1, hero2, found, counter;
    counter = 0;
    memset(heroes->aux_matrix[0], 0, heroes->quantity * heroes->quantity * sizeof(short int));
    for (int i = 0; i < heroes->conflicts_qty; i++)
    {
        found = 0;
        hero1 = heroes->conflicts[i].hero1;
        hero2 = heroes->conflicts[i].hero2;
        if (hero1 > depth && hero2 > depth)
        {
            hero1 -= 1;
            hero2 -= 1;
            for (int j = depth; j < heroes->quantity && found == 0; j++)
            {
                if (heroes->aux_matrix[j][hero1] == 1 && heroes->aux_matrix[j][hero2] == 1)
                {
                    heroes->aux_matrix[j][hero1] = -1;
                    heroes->aux_matrix[hero1][j] = -1;
                    heroes->aux_matrix[j][hero2] = -1;
                    heroes->aux_matrix[hero2][j] = -1;
                    heroes->aux_matrix[hero1][hero2] = -1;
                    heroes->aux_matrix[hero2][hero1] = -1;
                    counter++;
                    found = 1;
                }
            }
            if (found == 0)
            {
                heroes->aux_matrix[hero1][hero2] = 1;
                heroes->aux_matrix[hero2][hero1] = 1;
            }
        }
    }
    return counter;
}

/* ============================== Auxiliary Functions ============================== */

/* ============================== Internal Functions ============================== */

int profit(int *solution, heroes_t *heroes, int depth)
{
    int profit = 0;
    int hero1, hero2;
    for (int i = 0; i < heroes->conflicts_qty; i++)
    {
        hero1 = heroes->conflicts[i].hero1;
        hero2 = heroes->conflicts[i].hero2;
        if (hero1 <= depth && hero2 <= depth)
        {
            if ((solution[hero1 - 1] == 1 && solution[hero2 - 1] == 1) ||
                (solution[hero1 - 1] == 0 && solution[hero2 - 1] == 0))
                profit++;
        }
    }

    return profit;
}

int custom_bound(heroes_t *heroes, int *partial_solution, int depth, int cur_group)
{
    return profit(partial_solution, heroes, depth) + count_triangles(heroes, depth) + check_conflicts(heroes, partial_solution, depth + 1, cur_group);
}

int naive_bound(heroes_t *heroes, int *partial_solution, int depth)
{
    return profit(partial_solution, heroes, depth) + count_triangles(heroes, depth);
}

int partial_bound(heroes_t *heroes, int *partial_solution, int depth, params_t *params, int cur_group)
{
    if (params->custom_bound)
        return custom_bound(heroes, partial_solution, depth, cur_group);
    else
        return naive_bound(heroes, partial_solution, depth);
}

void optimize_heroes_recursive(heroes_t *heroes, params_t *params, optimize_state_t *optimize, int depth)
{
    int cur_opt, available_opt, partial_opt;
    optimize->nodes++;

    if (depth == heroes->quantity)
    {
        cur_opt = profit(optimize->cur_solution, heroes, INT_MAX);
        if (cur_opt < optimize->opt_value)
        {
            optimize->opt_value = cur_opt;
            memcpy(optimize->opt_solution, optimize->cur_solution, heroes->quantity * sizeof(int));
        }
    }

    available_opt = 2;
    if (params->feasibility && depth != heroes->quantity)
        available_opt = check_friendships(heroes, optimize, depth + 1);

    if (depth != heroes->quantity)
    {
        int init = available_opt == 2 ? 0 : available_opt;
        int cond = available_opt == 2 ? available_opt : init + 1;
        for (int i = init; i < cond; i++)
        {
            partial_opt = INT_MIN;
            if (params->optimization)
                partial_opt = partial_bound(heroes, optimize->cur_solution, depth, params, i);

            if (partial_opt < optimize->opt_value)
            {
                optimize->cur_solution[depth] = i;
                optimize_heroes_recursive(heroes, params, optimize, depth + 1);
                optimize->cur_solution[depth] = 0;
            }
        }
    }
}

/* ============================== Internal Functions ============================== */

int optimize_heroes(heroes_t *heroes, params_t *params)
{
    optimize_state_t optimize;
    struct timeval start, end;

    optimize.cur_solution = alloc_array(heroes->quantity, sizeof(int));
    optimize.opt_solution = alloc_array(heroes->quantity, sizeof(int));
    optimize.opt_value = INT_MAX;
    optimize.nodes = 0;

    gettimeofday(&start, NULL);
    optimize_heroes_recursive(heroes, params, &optimize, 0);
    gettimeofday(&end, NULL);

    optimize.time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

    for (int i = 0; i < heroes->quantity; i++)
    {
        printf("%d ", optimize.opt_solution[i]);
        heroes->heroes[i].group = optimize.opt_solution[i];
    }
    printf("\nNODES: %d", optimize.nodes);
    printf("\nTIME: %f", optimize.time);
    printf("\nCONFLICTS: %d\n\n", optimize.opt_value);

    return 0;
}
