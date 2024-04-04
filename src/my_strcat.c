/*
** EPITECH PROJECT, 2023
** src
** File description:
** my_strcat.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
char *my_strcat(char *dest, char const *src)
{
    int j = my_strlen(dest);
    int i = my_strlen(src);
    char *res = malloc((j + 1) * sizeof(char));

    my_strcpy(res, dest);
    dest = malloc((j + i+ 1) * sizeof(char));
    my_strcpy(dest, res);
    for (int m = 0; m < i; m++) {
        dest[j + m] = src[m];
    }
    dest[j + i + 1] = '\0';
    return dest;
}
