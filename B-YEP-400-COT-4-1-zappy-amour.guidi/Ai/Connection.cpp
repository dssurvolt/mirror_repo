/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-amour.guidi
** File description:
** connection
*/

#include "include/Ai.hpp"

Clientia::Clientia(int _p, const char *addr_ip, const std::string &team)
{
    team_name = team;
    port = _p;
    socketfd = create_socket();
    addr = create_servor_addr(_p);
    addr.sin_addr.s_addr = inet_addr(addr_ip);
    addr_len = sizeof(addr);
    pfds[0].fd = socketfd;
    pfds[0].events = POLLIN;
    current = Connecting;
    srand(time(NULL));

    if (connect(socketfd, (struct sockaddr *)&addr, addr_len) != 0)
    {
        perror("Connection failed");
        exit(84);
    }
    inventory.food     = 0;
    inventory.linemate = 0;
    inventory.deraumere = 0;
    inventory.sibur    = 0;
    inventory.mendiane = 0;
    inventory.phiras   = 0;
    inventory.thystame = 0;
}

int Clientia::create_socket()
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    return socketfd;
}

struct sockaddr_in Clientia::create_servor_addr(int p)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(p);
    addr.sin_addr.s_addr = INADDR_ANY;

    return addr;
}

void Clientia::send_line(const std::string &line)
{
    std::cout << "-> SENT: " << line << std::endl;
    std::string to_send = line + "\n";
    if (write(socketfd, to_send.c_str(), to_send.length()) < 0) {
        throw std::runtime_error("write failed");
    }
}

Clientia::~Clientia()
{
    close(socketfd);
}
