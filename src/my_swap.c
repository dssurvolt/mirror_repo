/*
** EPITECH PROJECT, 2023
** src
** File description:
** my_swap.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
void my_swap(char *a, char *b)
{
    char e;

    e = *a;
    *a = *b;
    *b = e;
}
