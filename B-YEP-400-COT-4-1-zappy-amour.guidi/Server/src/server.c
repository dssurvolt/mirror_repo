/*
** EPITECH PROJECT, 2024
** B-YEP-400-COT-4-1-zappy-amour.guidi [WSL: Ubuntu-24.04]
** File description:
** server.c
*/

#include "../includes/server.h"
#include "../includes/command.h"
#include <time.h>

void push_back(servercontrol_t *sctrl, int fd) ///fd
{
    struct pollfd new_fd = {fd, POLLIN, 0};
    struct pollfd *temp = realloc(sctrl->fds, 
        sizeof(struct pollfd) * (sctrl->nfds + 1));

    sctrl->fds = temp;
    sctrl->fds[sctrl->nfds] = new_fd;
    sctrl->nfds++; 
}

void listnbind(servercontrol_t *server)
{
    server->address.sin_family = AF_INET;    
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
    if (bind(server->server_fd, (struct sockaddr*)&server->address,
        sizeof(server->address)) < 0) {
        perror("Echec du bind");
        exit(EXIT_FAILURE);     
    }
    if (listen(server->server_fd, SOMAXCONN) < 0) {
        perror("Echec du listen");
        exit(EXIT_FAILURE);
    }
}

void setupSocket(servercontrol_t *server)
{
    int opt = 1;

    if ((server->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Echec de la création du socket");
        exit(EXIT_FAILURE);
    }
    if(setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt
        , sizeof(opt))) {
        perror("Echec du Setsockopt");
        exit(EXIT_FAILURE);
    }
    listnbind(server);
    server->push_back(server, server->server_fd);
}

void acceptKlients(servercontrol_t *server)
{
    struct sockaddr_in client_addr = {0};
    int flags = 0;
    socklen_t addr_len = sizeof(client_addr);
    trantoriant_t *tranto = NULL;
    int client_fd = accept(server->server_fd,
        (struct sockaddr*)&client_addr, &addr_len);

    if (client_fd < 0) {
        exit(EXIT_FAILURE);
    }
    flags = fcntl(client_fd, F_GETFL, 0);
    fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);
    server->push_back(server, client_fd);
    server->maxid += 1;
    addTrantorian(&server->trantoworld, client_fd, server->maxid);
    printf("Nouvelle IA connectée [%d]\n", server->maxid);
    tranto = lookTrantorian(server, server->maxid);
    tranto->writeToIA(tranto, "WELCOME\n");
}
