/*
** EPITECH PROJECT, 2023
** function_ls3.c
** File description:
** iuergdydf
*/
#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int erreur(char *argv)
{
    my_printf("ls: impossible d'accéder à '%s':", argv);
    my_printf(" Aucun fichier ou dossier de ce type\n", argv);
    return 84;
}

void dir_file(char *argv)
{
    struct stat s;

    stat(argv, &s);
    if (S_ISDIR(s.st_mode))
        my_printf("d");
    if (S_ISREG(s.st_mode))
        my_printf("-");
}

char *mallocs(char *dest, char const *src, const char *str, int i)
{
    char *s;
    int a = 0;

    while (src[i] != '\0')
        i++;
    a = i;
    i = 0;
    while (str[i] != '\0')
        i++;
    a = a + i;
    while (str[i] != '\0')
        i++;
    a = a + i + 1;
    s = malloc(a * sizeof(char));
}

char *my_strcat(char *dest, char const *src, const char *str)
{
    int i = 0;
    int j = 0;
    char *s;

    s = mallocs(dest, src, str, i);
    i = 0;
    for (j = 0; dest[j] != '\0'; j++){
        s[i] = dest[j];
        i++;
    }
    for (j = 0; src[j] != '\0'; j++){
        s[i] = src[j];
        i++;
    }
    for (j = 0; str[j] != '\0'; j++){
        s[i] = str[j];
        i++;
    }
    s[i] = '\0';
    return s;
}
