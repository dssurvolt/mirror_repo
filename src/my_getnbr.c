/*
** EPITECH PROJECT, 2023
** GETNUMBER
** File description:
** A function that gets a number
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hashtable.h"
int my_atoi(char const *str)
{
    int j = 0;
    int i = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            j = (j * 10) + (str[i]-48);
        } else
            break;
    }
    return j;
}
