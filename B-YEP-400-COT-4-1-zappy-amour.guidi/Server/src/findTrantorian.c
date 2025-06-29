/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** findTrantorian.c
*/

#include "../includes/server.h"

trantoriant_t *lookTrantorian(servercontrol_t *serv, int id)
{
    trantoriant_t *looki = serv->trantoworld;

    for (; looki != NULL; looki = looki->next) {
        if (looki->id == id)
            return looki;
    }
}


trantoriant_t *searchByFD(servercontrol_t *serv, int fd)
{
    trantoriant_t *looki = serv->trantoworld;

    for (; looki != NULL; looki = looki->next) {
        if (looki->fd == fd)
            return looki;
    }
}