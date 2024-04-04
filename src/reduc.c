/*
** EPITECH PROJECT, 2023
** src
** File description:
** reduc.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
char *reduc(char *str)
{
    char *dest = malloc(11 * sizeof(char));
    int k = 0;

    for (int i = 5; i <= 13; i++) {
        dest[k] = str[i];
        k++;
    }
    dest[k] = '\0';
    return dest;
}

char *redix(char *str)
{
    char *dest = malloc(11 * sizeof(char));
    int k = 0;

    for (int i = 0; i <= 8; i++) {
        dest[k] = str[i];
        k++;
    }
    dest[k] = '\0';
    return dest;
}
