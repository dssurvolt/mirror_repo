/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-amour.guidi
** File description:
** ia_main
*/

#include "include/Ai.hpp"

struct ClientConfig
{
    int port = 0;
    std::string name;
    std::string machine = "127.0.0.1";
};

void printusage(void)
{
    std::cerr << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
    std::cerr << "\tport\t is the port number" << std::endl;
    std::cerr << "\tname\t is the name of the team" << std::endl;
    std::cerr << "\tmachine\t is the name of the machine; localhost by default" << std::endl;
    exit(84);
}

ClientConfig parseArguments(int argc, char **argv)
{
    ClientConfig config;

    if (argc < 7)
        printusage();

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-p") {
            config.port = std::atoi(argv[i + 1]);
        } else if (std::string(argv[i]) == "-n") {
            config.name = argv[i + 1];
        } else if (std::string(argv[i]) == "-h") {
            config.machine = argv[i + 1];
        }
    }

    if (config.port == 0 || config.name.empty())
        printusage();
    return config;
}

int main(int argc, char **argv)
{
    try {
        ClientConfig config = parseArguments(argc, argv);
        Clientia client(config.port, config.machine.c_str(), config.name);
        client.run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}