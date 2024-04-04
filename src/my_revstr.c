/*
** EPITECH PROJECT, 2023
** src
** File description:
** my_revstr.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
char *my_revstr(char *str)
{
    int j = my_strlen(str) - 1;
    int i = 0;
    int k = 0;

    while (i < j) {
        my_swap(&(str[k]), &(str[j]));
        k++;
        j--;
        i++;
    }
    return str;
}
