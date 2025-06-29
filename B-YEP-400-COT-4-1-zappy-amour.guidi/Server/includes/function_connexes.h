/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** function_connexes.h
*/

/* Nous implémentons ici toutes les fonctions connexes dont on pourrait
avoir besoin...*/

#ifndef FUNCTIONS_CONNEXES_ZAPPY
    #define FUNCTIONS_CONNEXES_ZAPPY

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <stdbool.h>
    #include <netinet/in.h>
    #include <poll.h>


struct trantorian;
typedef struct commandBox{
    char *commands;
    struct trantoriant *trantorian;
    struct commandBox *next;
}commandBox_t;    

typedef struct queue {
    commandBox_t *box;
    bool (*isEmpty)(struct queue *);
    int (*size)(struct queue *);
    void (*enqueue)(struct queue *, char *commande, struct trantorian *);
    char *(*dequeue)(struct queue *);
    void (*boxKill)(struct queue *);
}queue_t;
void initQueue(queue_t *queux);
#endif