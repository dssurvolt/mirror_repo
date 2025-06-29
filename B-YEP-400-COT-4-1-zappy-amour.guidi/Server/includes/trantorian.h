/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** server.h
*/

/**
 * @file server.h 
 * Fichier d'en-tête. C'est ici que nous définissions les prototypes des fonctions et structures
 * @author Akandé
 * @author Amour
 * @author Elias
 * @author Emmanuelle
 * @author Jean-Baptiste
 * @author Rakib
 * @date 2025
 * @version 1.0 Danxome
 */
#ifndef TRANTORIAN_ZAPPY
    #define TRANTORIAN_ZAPPY

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <stdbool.h>
    #include "server.h"
    #include "function_connexes.h"
    #define MAX_RESOURCES 7


typedef enum {
    NORTH, //Nord
    EAST, //Est
    SOUTH,//Sud
    WEST // Ouest
} Orientation_t;


typedef struct serial {

}serial_t;


typedef struct inventory {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} inventory_t; //This is each trantorian's inventoy


typedef struct position {
    int x;
    int y;
} position_t; //This is each trantorian's position


typedef struct trantorian {
    int id;
    char *teams;
    int fd;
    int vie;
    int level;
    bool islive;
    int time;
    int *inventory;
    position_t position;
    int direction;  // 1: Nord, 2: Est, 3: Sud, 4: Ouest
    char *commands[10];
    struct queue queue;
    Orientation_t orientation;
    bool (*readFromIA)(struct trantorian *, char **message);
    bool (*writeToIA)(struct trantorian *, char *message);
    bool (*isGone)(struct trantorian *);
    struct trantorian *next;
} trantoriant_t; //Each trantorian on the map is reprensented by this struct

trantoriant_t *generaTrantorian(int fd, int maxFD);
void free_double_tab(char** tab); /* to free a double array */
void removeTrantorian(trantoriant_t **base, int id);
void addTrantorian(trantoriant_t **base, int fd, int maxFD);
#endif