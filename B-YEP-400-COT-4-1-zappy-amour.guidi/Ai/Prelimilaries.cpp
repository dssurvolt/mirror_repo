/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-amour.guidi
** File description:
** prelimilaries
*/

#include "include/Ai.hpp"

void Clientia::parseBroadcast(const std::string &msg)
{
    _lastBroadcast = msg;

    int pos = msg.find("message");
    std::string direction_, level_, id_, msg_;
    std::stringstream ss(msg.substr(pos + 7));

    //message 22, 30
    if (std::getline(ss, direction_, ',') && std::getline(ss, level_, ',') && std::getline(ss, id_)) {
            direction = std::stoi(direction_);
            playerlevel = std::stoi(level_);
            senderId = std::stoi(id_);
            if (_receivebroadcast == false)
                _receivebroadcast = true;
            std::cout << "Player Level: " << playerlevel << " Direction :  " << direction  << " ID: " << senderId << std::endl;
    } else {
        std::cerr << "cut error" << std::endl;
    }
}

void Clientia::parseInventory(const std::string& response)
{
    std::string content = response.substr(1, response.find_last_of(']') - 1);
    std::stringstream ss(content);
    std::string str;

    while (std::getline(ss, str, ',')) {
        std::stringstream parse_ss(str);
        std::string key;

        int a;
        parse_ss >> key >> a;

        if (key == "food")
            inventory.food = a;
        else if (key == "linemate")
            inventory.linemate = a;
        else if (key == "deraumere")
            inventory.deraumere = a;
        else if (key == "sibur")
            inventory.sibur = a;
        else if (key == "mendiane")
            inventory.mendiane = a;
        else if (key == "phiras")
            inventory.phiras = a;
        else if (key == "thystame")
            inventory.thystame = a;
    }
}

void Clientia::readInfo(void)
{   
    bzero(buffer, sizeof(buffer));
    int bytesRead = read(socketfd, buffer, sizeof(buffer));
    if (bytesRead <= 0) {
        std::cout << "Server disconnected." << std::endl;
        exit(0);
    }
    std::cout << "<- RECV: " << buffer;

    std::string response(buffer);
    std::istringstream stream(response);
    std::string line;
    while (std::getline(stream, line)) {
        if (!line.empty()) {
            parseservermessage(line);
        }
    }
}

void Clientia::parseservermessage(const std::string &msg)
{
    if (current == Connecting && msg == "WELCOME") {
        parseWelcome();
    } else if (current == Welcome) {
        parseNbrclient(msg);
    } else if (current == TeamName) {
        parseMapSize(msg);
    } else {
        if (msg.find("[ food") == 0)
            parseInventory(msg);
        else if (msg.find("[ player") == 0)
            parseLook(msg);
        else if (msg == "ok") {
            return;
        } else if (msg == "ko") {
            clearall();
            return;
        } else if (msg == "Elevation underway") {
            std::cout << "Incantation en cours..." << std::endl;
        } else if (msg == "Current Level:") {
            std::cout << "Incantation réussie!" << std::endl;
        } else if (msg.find("message ") == 0) {
            parseBroadcast(msg);
        } else if (msg == "dead") {
            std::cout << "I died. Game over." << std::endl;
            exit(0);
        }
    }
}

void Clientia::clearall()
{
    while (!_action.empty()) {
        _action.pop();
    }
    
    while (!cmd.empty()) {
        cmd.pop();
    }

    _action.push("Look");
    _action.push("Inventory");
}

void Clientia::parseWelcome()
{
    current = Welcome;
    send_line(team_name);
}

void Clientia::parseNbrclient(const std::string &msg)
{
    std::stringstream str(msg);
    str >> nbr_; 
    current = TeamName;    
}

void Clientia::parseMapSize(const std::string &msg)
{
    std::istringstream str(msg);
    int x, y;
    str >> x >> y;
    current = Connected;
}

void Clientia::parseLook(const std::string &msg)
{
    _vision.clear();
    std::string content = msg.substr(1, msg.length() - 2); // Pour enlever les crochets du début et la fin
    std::stringstream str(content);
    std::string tilec;

    while (std::getline(str, tilec, ',')) {
        TIlecontent tile;
        std::stringstream t(tilec);
        std::string item;

        while (t >> item) {
            if (item == "player")
                tile.player++;
            else if (item == "food")
                tile.food++;
            else if (item == "linemate")
                tile.linemate++;
            else if (item == "deraumere")
                tile.deraumere++;
            else if (item == "sibur")
                tile.sibur++;
            else if (item == "mendiane")
                tile.mendiane++;
            else if (item == "phiras")
                tile.phiras++;
            else if (item == "thystame")
                tile.thystame++;
        }
        _vision.push_back(tile);
    }
}
