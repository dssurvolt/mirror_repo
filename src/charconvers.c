/*
** EPITECH PROJECT, 2023
** src
** File description:
** charconvers.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
char *charconver(long int nb)
{
    long int remain;
    long int i;
    char *result = malloc(200 * sizeof(char));

    for (i = 0; nb >= 10; i++){
        remain = nb % 10;
        nb = nb / 10;
        if (remain < 10){
            result[i] = remain + 48;
        }
    }
    result[i] = nb + 48;
    result[i + 1] = '\0';
    my_revstr(result);
    return result;
}
