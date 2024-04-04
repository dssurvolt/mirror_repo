/*
** EPITECH PROJECT, 2024
** search.c
** File description:
** ehdusygtr
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
#include "../include/my.h"
#include <unistd.h>

char *ht_search(hashtable_t *ht, char *key)
{
    int a;
    hashtable_t *hm;

    if (ht == NULL || key == NULL)
    return NULL;
    hm = ht;
    a = ht->hash(key, ht->len) % ht->len;
    while (hm->s[a] != NULL) {
        if (hm->s[a]->key == ht->hash(key, ht->len)){
            return hm->s[a]->value;
        }
        hm->s[a] = hm->s[a]->next;
    }
    return NULL;
}
