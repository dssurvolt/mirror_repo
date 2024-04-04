/*
** EPITECH PROJECT, 2023
** my printf
** File description:
** a function that print everything
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
char *base_converter(int nb, int base)
{
    int remain;
    int i;
    char *result = malloc(remain * sizeof(char));

    for (i = 0; nb >= base; i++){
        remain = nb % base;
        nb = nb / base;
        if (remain < 10){
            result[i] = remain + 48;
        }
    }
    result[i] = nb + 48;
    result[i + 1] = '\0';
    my_revstr(result);
    return result;
}
