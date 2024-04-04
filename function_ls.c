/*
** EPITECH PROJECT, 2023
** function_ls.c
** File description:
** fdhkjcgf
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

int directory_as_parameter(char *argv)
{
    struct dirent *entree;
    DIR *fd;
    char *c;
    fd = opendir(argv);
    if (fd == NULL)
        return 84;
    entree = readdir(fd);
    while (entree != NULL){
        c = entree->d_name;
        if (entree->d_name[0] == '.')
            my_printf("");
        else
            my_printf("%s ", c);
        entree = readdir(fd);
    }
    my_printf("\n");
    closedir;
}

void flag_a(char *argv)
{
    struct dirent *entree;
    DIR *fd;
    char *c;

    fd = opendir(argv);
    entree = readdir(fd);
    while (entree != NULL){
        c = entree->d_name;
        my_printf("%s ", c);
        entree = readdir(fd);
    }
    closedir;
}

void flag_l(char *argv)
{
    struct dirent *entree;
    DIR *fd;
    char *c;
    char *d = "/";
    char *e;

    fd = opendir(argv);
    entree = readdir(fd);
    while (entree != NULL){
        c = entree->d_name;
        if (entree->d_name[0] == '.'){
            my_printf("");
        } else {
            e = my_strcat(argv, d, c);
            information(e);
            my_printf("%s\n", c);
        }
        entree = readdir(fd);
    }
    closedir;
}

int cond(struct stat *s, int i, char *argv[])
{
    if (argv[i][0] == '-' && argv[i][1] == 'l' && argv[i + 1][0] != '-'){
        stat(argv[i + 1], s);
        if (S_ISDIR(s->st_mode)){
            flag_l(argv[i + 1]);
            i = i + 2;
        }
        return 1;
    }
    if (argv[i][0] == '-' && argv[i][1] == 'a' && argv[i + 1][0] != '-'){
        stat(argv[i + 1], s);
        if (S_ISDIR(s->st_mode)){
            flag_a(argv[i + 1]);
            i = i + 2;
        }
        return 1;
    }
    if (argv[i][0] == '-' && argv[i][1] == 'd' && argv[i + 1][0] != '-'){
        my_printf(".");
    } else if (argv[i][0] == '-' && argv[i][1] != 'l' || argv[i][1] != 'a')
        return 84;
}

int main(int argc, char **argv)
{
    int i;
    struct stat s;
    struct dirent *entree;
    DIR *fd;
    int a = 0;

    if (argc == 1)
        nothing();
    for (i = 1; i < argc; i++){
        stat(argv[i], &s);
        a = cond(&s, i, argv);
        if (S_ISREG(s.st_mode))
            file_as_parameter(argv[i]);
        if (S_ISDIR(s.st_mode))
            directory_as_parameter(argv[i]);
        else
            erreur(argv[i]);
        if (a == 1)
            i += 1;
    }
}
