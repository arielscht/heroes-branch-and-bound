#include <stdio.h>
#include <stdlib.h>
#include "heroes.h"

int heroes_init(heroes_t *heroes, int quantity, int conflicts, int friendships)
{
    heroes->quantity = quantity;
    heroes->conflicts_qty = conflicts;
    heroes->friendships_qty = friendships;

    heroes->heroes = calloc(quantity, sizeof(hero_t));
    if (heroes->heroes == NULL)
    {
        perror("Error allocating array");
        return -1;
    }

    heroes->conflicts = calloc(conflicts, sizeof(hero_pair_t));
    if (heroes->conflicts == NULL)
    {
        perror("Error allocating array");
        return -1;
    }

    heroes->friendships = calloc(friendships, sizeof(hero_pair_t));
    if (heroes->friendships == NULL)
    {
        perror("Error allocating array");
        return -1;
    }

    for (int i = 1; i <= quantity; i++)
    {
        heroes->heroes[i].id = i;
        heroes->heroes[i].group = 0;
    }

    return 0;
}

int heroes_destroy(heroes_t *heroes)
{
    if (heroes->heroes)
        free(heroes->heroes);

    if (heroes->conflicts)
        free(heroes->conflicts);

    if (heroes->friendships)
        free(heroes->friendships);

    return 0;
}