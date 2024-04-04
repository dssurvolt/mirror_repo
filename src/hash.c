/*
** EPITECH PROJECT, 2023
** B-CPE-110-COT-1-1-secured-akande-philippe.abiodoun
** File description:
** hash.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"

int hash(char *key, int len)
{
    long int nb = 0;
    int k = 2;
    long int i = 0;
    char *numb = NULL;
    char *numerint = malloc(sizeof(char));

    numerint[0] = '\0';
    for (i = 0; key[i] != '\0'; i++) {
        k += 2;
        nb += key[i];
        nb = nb * k;
        numb = charconver(nb);
    }
    i = my_strlen(numb);
    if (i < 20) {
    numb = concint(numb, i);
    }
    if (i >= 20)
    numb = reduc(numb);
    return basec(numb);
}
