/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** dsiuygtc
*/
#include "../include/hashtable.h"
int main(int ac, char **av)
{
    hashtable_t *ht = new_hashtable(&hash, 340);
    ht_insert(ht, "3", "+33 6 4 344");
    ht_dump(ht);
    return 0;
}