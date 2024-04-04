/*
** EPITECH PROJECT, 2023
** B-CPE-110-COT-1-1-organized-akande-philippe.abiodoun
** File description:
** my_strdup.c
*/
#include "../include/hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *my_strdup(char *str)
{
    int k = my_strlen(str);
    int i;
    char *dest = malloc(k * sizeof(char));

    for (i = 0; str[i] != '\0'; i++) {
        dest[i] = str[i];
    }
    dest[i] = '\0';
    return dest;
}
