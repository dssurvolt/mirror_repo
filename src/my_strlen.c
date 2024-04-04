/*
** EPITECH PROJECT, 2023
** src
** File description:
** my_strlen.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return i;
}
