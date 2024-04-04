/*
** EPITECH PROJECT, 2024
** insert.c
** File description:
** iudtsytsdhftyds
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
#include "../include/my.h"
#include <unistd.h>

int ht_insert(hashtable_t *ht, char *key, char *value)
{
    int j = 0;
    entry_t *info;
    int a = 0;

    if (ht == NULL || key == NULL || value == NULL)
    return 84;
    info = create_address(key, value, ht);
    a = info->key % ht->len;
    if (ht->s[a] == NULL){
        ht->s[a] = info;
    } else {
        info->next = ht->s[a];
        ht->s[a] = info;
    }
}
