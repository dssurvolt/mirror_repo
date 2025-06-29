/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** trantorian.c
*/

#include "../includes/command.h"
#include "../includes/trantorian.h"
#include <errno.h>
#include "../includes/function_connexes.h"
#include "../includes/map.h"

bool readFromIA(trantoriant_t *tranto, char **message) //fd
{
    char reader[1024] = {0};
    printf("file dezcri %d\n", tranto->fd);
    int bytes_read = read(tranto->fd, reader, sizeof(reader));
    if (bytes_read <= 0) {
        printf("Client %d is gone.\n", tranto->fd);
        close(tranto->fd);
        tranto->islive = false;
        return false;
    }
    reader[bytes_read] = '\0'; 
    *message = strdup(reader);
    return true;
}

bool isGone(trantoriant_t *tranto)
{
    return tranto->islive;
}

bool writeToIA(trantoriant_t *tranto, char *message) {///fd
    size_t total_sent = 0;
    ssize_t bytes_sent = 0;
    size_t message_len = strlen(message);

    while (total_sent < message_len) {
        bytes_sent = write(tranto->fd, message + total_sent,
            message_len - total_sent); //fd
        if (bytes_sent == -1) {
            if (errno == EINTR)
                continue; // écriture interrompue, on recommence
            return false;
        }
        if (bytes_sent == 0) {
            return false;
        }
        total_sent += bytes_sent;
    }
    return true;
}

void free_double_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++) {
        free(tab[i]);
    }
}

trantoriant_t *generaTrantorian(int fd, int maxId) //fd
{
    trantoriant_t *tranto = malloc(sizeof(trantoriant_t));

    tranto->id = maxId;
    tranto->fd = fd;
    tranto->level = 1;
    tranto->islive = false;
    tranto->teams = NULL;
    tranto->vie = 126;
    tranto->writeToIA = writeToIA;
    tranto->isGone = isGone;
    tranto->readFromIA = readFromIA;
    tranto->inventory = inventory_init(7);
    initQueue(&tranto->queue);
    tranto->orientation = NORTH;
    return tranto;
}


void addTrantorian(trantoriant_t **base, int fd, int maxId) //fd
{
    trantoriant_t *current = *base;
    trantoriant_t *trantorian = generaTrantorian(fd, maxId);

    trantorian->next = NULL;
    if (*base == NULL) {
        *base = trantorian;
    } else {
        for (; current->next != NULL; current = current->next);
        current->next = trantorian;
    }
}

void removeTrantorian(trantoriant_t **base, int id)
{
    trantoriant_t *current = *base;
    trantoriant_t *last = malloc(sizeof(trantoriant_t));

    if (current->id == id) {
        last = current->next;
        free(current->teams);
        free_double_tab(current->commands);
        close(current->fd);
        free(current);
    } else {
        for (; current->next != NULL; current = current->next) {
            if (current->id == id) break;
            last = current;
        }
        last->next = current->next;
        free(current->teams);
        free_double_tab(current->commands);
        close(current->fd);
        free(current);
    }
}


