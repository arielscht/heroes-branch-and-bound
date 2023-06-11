#include <stdio.h>
#include "interface.h"

void read_params(int argc, void *argv, params_t *params)
{
}

void read_input(heroes_t *heroes)
{
    int quantity, conflicts, friendships;
    fscanf(stdin, "%d %d %d", &quantity, &conflicts, &friendships);

    heroes_init(heroes, quantity, conflicts, friendships);

    for (int i = 0; i < heroes->conflicts_qty; ++i)
        fscanf(stdin, "%d %d", &heroes->conflicts[i].hero1, &heroes->conflicts[i].hero2);

    for (int i = 0; i < heroes->friendships_qty; ++i)
        fscanf(stdin, "%d %d", &heroes->friendships[i].hero1, &heroes->friendships[i].hero2);
}

void print_heroes(heroes_t *heroes)
{
    printf("===== NUMBERS =====\n");
    printf("Quantity of heroes: %d\n", heroes->quantity);
    printf("Quantity of conflicts: %d\n", heroes->conflicts_qty);
    printf("Quantity of friendships: %d\n\n", heroes->friendships_qty);

    printf("===== HEROES =====\n");
    for (int i = 0; i < heroes->quantity; i++)
    {
        printf("HERO %d:\n", i + 1);
        printf("    id: %d - group: %d\n", heroes->heroes[i].id, heroes->heroes[i].group);
    }

    printf("\n===== CONFLICTS =====");
    for (int i = 0; i < heroes->conflicts_qty; i++)
    {
        if (i % 10 == 0)
            printf("\n");
        printf("(%d, %d) ", heroes->conflicts[i].hero1, heroes->conflicts[i].hero2);
    }
    printf("\n\n");

    printf("===== FRIENDSHIPS =====");
    for (int i = 0; i < heroes->friendships_qty; i++)
    {
        if (i % 10 == 0)
            printf("\n");
        printf("(%d, %d) ", heroes->friendships[i].hero1, heroes->friendships[i].hero2);
    }
    printf("\n");
}