/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** serversuiteun.c
*/

#include "../includes/server.h"
#include "../includes/command.h"
#include <string.h>



char **kutstring(const char *str, const char *delim) {
    int count = strlen(str);
    char *copy = strdup(str);
    int i = 0;
    char *token = strtok(copy, delim);
    char **result = malloc((count + 1) * sizeof(char *));

    while (token) {
        result[i++] = strdup(token);
        token = strtok(NULL, delim);
    }
    result[i] = NULL;
    free(copy);
    return result;
}

void handleCommand(char *message, trantoriant_t *tranto) 
{
    if (!message || !tranto)
        return;

    if (tranto->queue.size(&tranto->queue) >= 10) {
        tranto->writeToIA(tranto, "ko\n");
        return;
    }
    tranto->queue.enqueue(&tranto->queue, strdup(message), tranto);
    for (int i = 0; i < 10; i++) {
        if (tranto->commands[i] == NULL) {
            tranto->commands[i] = strdup(message);
            break;
        }
    }
}

#include <stdlib.h>

char *my_strdup(const char *src)
{
    if (!src)
        return NULL;

    int len = 0;
    while (src[len] != '\0')
        len++;

    char *copy = malloc(sizeof(char) * (len + 1));
    if (!copy)
        return NULL;

    for (int i = 0; i < len; i++)
        copy[i] = src[i];

    copy[len] = '\0';
    return copy;
}

void processClientCommands(servercontrol_t *server, int id)
{
    trantoriant_t *tranto = lookTrantorian(server, id);      
        
    if (!tranto || tranto->queue.isEmpty(&tranto->queue))
        return;
    char *cmd = tranto->queue.dequeue(&tranto->queue);
    if (!cmd)
        return;
    char **args = kutstring(cmd, " ");
    if (!args || !args[0]) {
        tranto->writeToIA(tranto, "ko\n");
        free(cmd);
        free_double_tab(args);
        return;
    }
    int cmd_id = atoi(args[0]);
    if ((cmd_id == 11 || cmd_id == 12) && args[1] == NULL) 
        return;
    else
        server->tab = my_strdup(args[1]);
    if (cmd_id > 0 && cmd_id <= 14 && command_table[cmd_id]) {
        printf("Traitement de la commande %d pour le client %d\n", cmd_id, id);
        command_table[cmd_id](server, id);
    } else {
        tranto->writeToIA(tranto, "ko\n");
        printf("Cette commande es inconnue: %d\n", cmd_id);
    }
    free(cmd);
}

void handleIAcmds(servercontrol_t *server, int id)
{
    trantoriant_t *tranto = searchByFD(server, id);
    char *message = NULL;
    char buffer[32];
    int len = snprintf(buffer, sizeof(buffer), "%d", id);
    int teamrest = 0;

    printf("ia id => %d\n", tranto->id);
    if (tranto->readFromIA(tranto, &message) == false) {
        cleanTrantor(server, id);
    }
    message[strlen(message) - 2] = '\0';
    char **commands = kutstring(message, " \n");
    for (int i = 0; commands[i] != NULL; i++) {
        printf("%s\n", commands[i]);
    }
    if (!tranto->teams)
        communika(server, commands, tranto);
    handleCommand(message, tranto);
    processClientCommands(server, id);
}


void cleanTrantor(servercontrol_t *server, int index)
{
    printf("AI [%d] is gone.\n", server->fds[index].fd);
    close(server->fds[index].fd);
    server->fds[index].fd = -1;
    server->nfds--;
    removeTrantorian(&server->trantoworld, server->fds[index].fd);
}

void argsChecki(int ac, char **av)
{
    if (strcmp(av[ac-2], "-c") != 0 || atoi(av[ac-1]) <= 0) {
        fprintf(stderr, "Refers to ./zappy_server -help\n");
        exit(EXIT_FAILURE);
    }
}
void argsCheckValid(int argc, char **argv)
{
    if (strcmp(argv[5], "-y") != 0 || atoi(argv[6]) <= 0) {
        fprintf(stderr, "Refers to ./zappy_server -help\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[7], "-n") != 0 || strlen(argv[8]) <= 0 ||
        strlen(argv[9]) <= 0){
        fprintf(stderr, "Refers to ./zappy_server -help\n");
        exit(EXIT_FAILURE);
    }
    if (argc > 12 && strcmp(argv[argc-2], "-f") == 0) {
        if (strcmp(argv[argc-4], "-c") != 0 || atoi(argv[argc-3]) <= 0) {
            fprintf(stderr, "Refers to ./zappy_server -help\n");
            exit(EXIT_FAILURE);
        }
        if (atoi(argv[argc-1]) <= 0) {
            fprintf(stderr, "Refers to ./zappy_server -help\n");
            exit(EXIT_FAILURE);
        }
    } else argsChecki(argc, argv);
}

void checkArgs(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        write(1, "USAGE: ./zappy_server -p port -x width -y height -n name1 "
            "name2 ... -c clientsNb -f freq\n", 90);
        exit(EXIT_SUCCESS);
    }
    if (argc < 12) {
        fprintf(stderr, "Argument's number is insuffisent\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[1], "-p") != 0 || atoi(argv[2]) <= 0) {
        fprintf(stderr, "Refers to ./zappy_server -help\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(argv[3], "-x") != 0 || atoi(argv[4]) <= 0) {
        fprintf(stderr, "Refers to ./zappy_server -help\n");
        exit(EXIT_FAILURE);
    }
    argsCheckValid(argc, argv);
}