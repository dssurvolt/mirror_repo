/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** trantoTime.h
*/

#ifndef TRANTO_TIME
    #define TRANTO_TIME

    #include <stdio.h>
    #include <time.h>
    #include <unistd.h>
    #include <stdint.h>

    struct trantorian;
typedef struct tranto {
    struct timespec timedebut;
    struct timespec timefin;
    uint64_t dt;
} tranto_t;


int counTranto(struct trantorian *);

#endif