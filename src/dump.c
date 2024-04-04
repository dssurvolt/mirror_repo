/*
** EPITECH PROJECT, 2024
** dump.c
** File description:
** ieuwdgstr
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
#include "../include/my.h"
#include <unistd.h>

void ht_dump(hashtable_t *ht)
{
    hashtable_t *hm = ht;

    for (int i = 0; i < ht->len; i++){
        my_putchar('[');
        my_putnbr(i);
        my_putstr("]:\n");
        while (hm->s[i] != NULL) {
            my_putstr("> ");
            my_putnbr(hm->s[i]->key);
            my_putstr(" - ");
            my_putstr(hm->s[i]->value);
            my_putchar('\n');
            hm->s[i] = hm->s[i]->next;
        }
    }
}
