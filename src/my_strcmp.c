/*
** EPITECH PROJECT, 2023
** B-CPE-110-COT-1-1-organized-akande-philippe.abiodoun
** File description:
** my_strcmp.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
int my_strcmp(char const *dest, char *str)
{
    int i = 0;
    int s = my_strlen(dest);
    int k = my_strlen(str);

    if (s != k) {
        return 1;
    }
    while (dest[i] != '\0' && dest[i] == str[i]) {
        i++;
    }
    return (dest[i] == '\0') ? 0 : 1;
}
