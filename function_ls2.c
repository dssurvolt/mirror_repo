/*
** EPITECH PROJECT, 2023
** function_ls2.c
** File description:
** erdtfuytd
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

void information2(struct stat *s)
{
    struct passwd *P;
    uid_t uid = s->st_uid;
    struct group *G;
    gid_t gid = s->st_gid;
    struct tm *time;
    char *t;
    char **T;

    P = getpwuid(s->st_uid);
    G = getgrgid(s->st_gid);
    t = ctime(&s->st_mtime);
    my_printf(" %s", P->pw_name);
    my_printf(" %s", G->gr_name);
    my_printf(" %lld", s->st_size);
    T = my_str_to_word_array(t);
    my_printf(" %s ", T[2]);
    my_printf("%s.", T[1]);
    T[3][5] = '\0';
    my_printf(" %s ", T[3]);
}

void information(char *argv)
{
    char *c;
    struct stat s;
    struct dirent *entree;
    DIR *fd;

    stat(argv, &s);
    dir_file(argv);
    my_printf("%c", s.st_mode &S_IRUSR ? 'r' : '-');
    my_printf("%c", s.st_mode &S_IWUSR ? 'w' : '-');
    my_printf("%c", s.st_mode &S_IXUSR ? 'x' : '-');
    my_printf("%c", s.st_mode &S_IRGRP ? 'r' : '-');
    my_printf("%c", s.st_mode &S_IWGRP ? 'w' : '-');
    my_printf("%c", s.st_mode &S_IXGRP ? 'x' : '-');
    my_printf("%c", s.st_mode &S_IROTH ? 'r' : '-');
    my_printf("%c", s.st_mode &S_IWOTH ? 'w' : '-');
    my_printf("%c.", s.st_mode &S_IXOTH ? 'x' : '-');
    my_printf(" %d", s.st_nlink);
    information2(&s);
}

void nothing(void)
{
    struct dirent *entree;
    DIR *fd;
    char *c;

    fd = opendir(".");
    entree = readdir(fd);
    while (entree != NULL){
        c = entree->d_name;
        if (entree->d_name[0] == '.'){
            my_printf("");
        } else {
            my_printf("%s ", c);
        }
        entree = readdir(fd);
    }
}

void file_as_parameter(char *argv)
{
    struct stat s;

    stat(argv, &s);
    my_printf("%s\n", argv);
}

void file_l(char *argv)
{
    information(argv);
    my_printf("%s\n", argv);
}
