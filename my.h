/*
** EPITECH PROJECT, 2023
** my.h
** File description:
** my headerfile
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#ifndef TRIPLE_H_INCLUDED
    #define TRIPLE_H_INCLUDED
extern double arg;
int error(char **T);
char **mytok(char **T, char *str, char *d);
char **array(char *str, int c, char *p);
char *revstr(char *str);
int count(char *p);
double *cases(char *str);
double compute(char *str, double x);
int calcul(char **T);
int calculs(char **T);
int cheker_size(char *size);
int count(char *p);
#endif // TRIPLE_H_INCLUDED
