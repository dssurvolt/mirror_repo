/*
** EPITECH PROJECT, 2023
** src
** File description:
** concint.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
char *concint(char *dest, int i)
{
    char *str = malloc((20 + 1) * sizeof(char));
    int z = 0;

    my_strcpy(str, dest);
    dest = malloc((20 + 1) * sizeof(char));
    for (int k = 0; z < 20; k++) {
        if (k == i) {
            k = 0;
        }
        dest[z] = str[k];
        z++;
    }
    dest = reduc(dest);
    return dest;
}

char *concindix(char *dest, int i)
{
    char *str = malloc((9 + 1) * sizeof(char));
    int z = 0;

    my_strcpy(str, dest);
    dest = malloc((9 + 1) * sizeof(char));
    for (int k = 0; z < 9; k++) {
        if (k == i) {
            k = 0;
        }
        dest[z] = str[k];
        z++;
    }
    dest = reduc(dest);
    return dest;
}

int basec(char *dest)
{
    int i = my_atoi(dest);
    char *numerint = malloc(sizeof(char));

    numerint[0] = '\0';
    numerint = base_converter(i, 9);
    i = my_strlen(numerint);
    if (i < 9) {
    numerint = concindix(numerint, i);
    } else if (i > 9) {
    numerint = redix(numerint);
    }
    return my_atoi(numerint);
}
