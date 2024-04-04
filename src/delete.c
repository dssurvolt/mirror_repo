/*
** EPITECH PROJECT, 2024
** delete.c
** File description:
** usdtyds
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
#include "../include/my.h"
#include <unistd.h>

entry_t *atpos(int hash, entry_t *hm)
{
    entry_t *current = hm;
    entry_t *previous = NULL;
    int i = 0;

    if (current->key == hash) {
        current = current->next;
        return current;
    }
    while (current->key != hash) {
        previous = current;
        current = current->next;
    }
    if (current->next == NULL) {
        previous->next = NULL;
        return hm;
    }
    previous->next = current->next;
    current = NULL;
    return hm;
}

int ht_delete(hashtable_t *ht, char *key)
{
    int a;
    int hash;
    char *repons;
    entry_t *temp;

    repons = ht_search(ht, key);
    if (repons == NULL)
    return 84;
    if (ht == NULL || key == NULL)
    return 84;
    a = ht->hash(key, ht->len) % ht->len;
    hash = ht->hash(key, ht->len);
    temp = ht->s[a];
    if (ht->s[a] != NULL){
        ht->s[a] = atpos(hash, ht->s[a]);
    } else {
        return 84;
    }
    return 0;
}
