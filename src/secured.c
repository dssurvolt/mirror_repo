/*
** EPITECH PROJECT, 2024
** secured.c
** File description:
** dsjduj
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
#include <unistd.h>

hashtable_t *new_hashtable(int (*hash)(char *, int), int len)
{
    hashtable_t *info = malloc(sizeof(hashtable_t));

    if (len <= 0)
    return NULL;
    info->s = malloc((len) * sizeof(entry_t));
    for (int i = 0; i < len; i++){
        info->s[i] = NULL;
    }
    info->hash = hash;
    info->len = len;
    return info;
}

void delete_hashtable(hashtable_t *ht)
{
    for (int i = 0; i < ht->len; i++){
        if (ht->s[i] != NULL){
            ht->s[i]->key = 0;
            free(ht->s[i]->value);
            free(ht->s[i]);
        }
    }
    free(ht);
}

entry_t *create_address(char *key, char *value, hashtable_t *ht)
{
    entry_t *info = malloc(sizeof(entry_t));

    info->key = ht->hash(key, ht->len);
    info->value = my_strdup(value);
    info->next = NULL;
    return info;
}
