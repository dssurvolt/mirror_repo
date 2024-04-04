/*
** EPITECH PROJECT, 2024
** trigo.c
** File description:
** ddjdfff
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int count(char *p)
{
    int a = 0;

    for (int i = 0; p[i] != '\0'; i++){
        if (p[i] == '*'){
            a++;
        }
    }
    return a;
}
