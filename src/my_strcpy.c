/*
** EPITECH PROJECT, 2023
** src
** File description:
** my_strcpy.c
*/

#include "../include/hashtable.h"

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
