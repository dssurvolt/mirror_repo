/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** function_connexes.c
*/

#include "../includes/function_connexes.h"
#include "../includes/server.h"

bool isEmpty(queue_t *self)
{
    return self->box == NULL;
}

int size(queue_t *self)
{
    int count = 0;
    commandBox_t *current = self->box;
    
    for (; current != NULL; current = current->next) {
        count++;
    }
    return count;
}

void enqueue(queue_t *self, char *commande, trantoriant_t *trantorian)
{
    commandBox_t *oldBox = self->box;
    commandBox_t *newbox = malloc(sizeof(commandBox_t));

    newbox->commands = strdup(commande);
    newbox->next = NULL;
    if (oldBox == NULL) {
        self->box = newbox;
    } else {
        for (; oldBox->next != NULL; oldBox = oldBox->next);
        oldBox->next = newbox;
    }
}

char *deqeue(queue_t *self)
{
    commandBox_t *oldBox = self->box;
    char *commande = NULL;

    if (isEmpty(self)) {
        return "";
    } else {
        self->box = oldBox->next;
        commande = strdup(oldBox->commands);
        free(oldBox->commands);
        free(oldBox);
    }
    return commande;
}


void boxKill(queue_t *self)
{
    commandBox_t *oldBox = self->box;
    commandBox_t *next = NULL;
    while (oldBox != NULL) {
        next = oldBox->next;
        free(oldBox->commands);
        free(oldBox);
        oldBox = next;
    }
    self->box = NULL;
}

void initQueue(queue_t *queux)
{
    queux->box = NULL;
    queux->isEmpty = isEmpty;
    queux->size = size;
    queux->enqueue = enqueue;
    queux->dequeue = deqeue;
    queux->boxKill = boxKill;
}
