#ifndef __HEROES__
#define __HEROES__

typedef struct hero_t
{
    int id;
    int group;
} hero_t;

typedef struct hero_pair_t
{
    int hero1, hero2;
} hero_pair_t;

typedef struct heroes_t
{
    int quantity, conflicts_qty, friendships_qty;
    hero_t *heroes;
    hero_pair_t *conflicts;
    hero_pair_t *friendships;
} heroes_t;

/*!
    \brief Initializes the heroes arrays
    \param heroes Pointer to the heroes structure
    \param quantity Quantity of heroes
    \param conflicts Quantity of conflicts
    \param friendships Quantity of friendships
*/
int heroes_init(heroes_t *heroes, int quantity, int conflicts, int friendships);

/*!
    \brief Free the allocated resources
    \param heroes Pointer to the heroes structure
*/
int heroes_destroy(heroes_t *heroes);

#endif