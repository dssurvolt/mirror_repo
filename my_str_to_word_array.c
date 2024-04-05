/*
** EPITECH PROJECT, 2023
** my_str_to_word_array.c
** File description:
** displays the content of an array of words.
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

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

int compter(char const *str)
{
    int a = 0;

    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] == ' ')
            a++;
    }
    return a;
}

int my_strlen(char const *str)
{
    int i;

    for (i = 0; str[i] > '\0'; i++)
        return i;
}

char **remplissage(int a, int b, char **T, char const *str)
{
    int c = 0;

    for (a; str[a] != '\0'; a++){
        if (str[a] != ' '){
            T[b][c] = str[a];
            c++;
        } else {
            T[b][c] = '\0';
            b++;
            c = 0;
        }
    }
}

char **my_str_to_word_array(char const *str)
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int m = 0;
    int e = compter(str);
    char **T;

    T = malloc((e + 1) * sizeof(char *));
    while (d <= (e + 1)){
        T[d] = malloc((my_strlen(str) + 1) * sizeof(char));
        d++;
    }
    remplissage(a, b, T, str);
    T[3][6] = '\0';
    return T;
}
