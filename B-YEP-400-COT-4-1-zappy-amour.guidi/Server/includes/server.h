/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** server.h
*/

#ifndef SERVER_ZAPPY
    #define SERVER_ZAPPY
    #define MAX_IA 10000
    #define TRANTIME server->trantime
    #define FDS server->fds
    #define NFDS server->nfds
    #define TRANTOWORLD server->trantoworld
    #define MAPK server->map
    #define WRITE tranto->writeToIA
    #define TEAMTR server->teamclients
    #define POSITION tranto->position
    #define MAPSERVER server->map_server

#include <poll.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>     
#include <unistd.h>
#include <fcntl.h>
#include "map.h"
#include "trantoTime.h"


struct position;
typedef struct map {
    int x;
    int y;
}map_t;

typedef struct team {
    char *name;
    int *mates;
    int matescount;
} team_t;
  
typedef struct egg {
    int id;
    int x;
    int y;
    char *team_name;
    bool hatched;
    struct egg *next;
} egg_t;

enum GameMode { ON, OFF };

typedef struct servercontrol {
    int server_fd;
    struct sockaddr_in address;
    enum GameMode game;
    int port;
    int time;
    int teamnb;
    int maxid;
    map_t map;
    char *tab; //chaine contenant le nom de la ressources passé en param
    tranto_t *trantime;
    egg_t *eggs;
    team_t *team; // adresse d'un tableau de pointeurs vers des listes chainées(une par équipe)
    int teamclients; //max de client
    int frequence;
    struct pollfd *fds;
    int nfds;
    struct Map *map_server;
    struct trantorian *trantoworld;
    void (*push_back)(struct servercontrol *, int fd);
    void (*getLife)(struct servercontrol *, int dt);
} servercontrol_t;

typedef struct unika {
    int teamrest;
    char buffer[32];
    char message[450];
}unika_t;

struct trantorian *lookTrantorian(servercontrol_t *, int id);
void setupSocket(servercontrol_t *server);
void acceptKlients(servercontrol_t *server);
void handleIAcmds(servercontrol_t *server, int id);
void cleanTrantor(servercontrol_t *server, int index);
void push_back(servercontrol_t *sctrl, int fd);
void checkArgs(int argc, char **argv);
void registerArgs(int ac, char **av, servercontrol_t **ser);
void getLife(servercontrol_t *server, int dt);
void communika(servercontrol_t *server, char **commands, 
    struct trantorian *tranto);
void addMates(team_t *teams, int id);
struct position tranPosition(servercontrol_t *server);
void placeTrantorian(servercontrol_t *server, struct trantorian *tranto);
double tiManage(servercontrol_t *server);
struct trantorian *searchByFD(servercontrol_t *serv, int fd);
#endif