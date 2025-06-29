/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-amour.guidi
** File description:
** ia
*/

#include "include/Ai.hpp"

bool Clientia::foodneed()
{
    if (inventory.food >= reserve && _waitplayer == false) {
        _waitplayer = true;
        return false;
    }
    if (inventory.food <= danger && _waitplayer == true) {
        _waitplayer =  false;
        return true;
    }
    if (inventory.food > danger && inventory.food < reserve && _waitplayer == false) {
        return true;
    }
    if (inventory.food > danger && inventory.food < reserve && _waitplayer == true) {
        return false;
    }
    if (inventory.food <= danger && _waitplayer == false) {
        return true;
    }
    if (inventory.food > reserve && _waitplayer == true) {
        return false;
    }
    return false;
}

bool Clientia::isFoodVisibleAhead()
{
    for (const auto& tile : _vision) {
        if (tile.food > 0)
            return true;
    }
    return false;
}

bool Clientia::isRockVisibleAhead()
{
    for (const auto& tile : _vision) {
        if (tile.linemate > 0 || tile.deraumere > 0
            || tile.mendiane > 0 || tile.phiras > 0
            || tile.sibur > 0 || tile.thystame > 0)
            return true;
    }
    return false; 
}

bool Clientia::isObstacleVisible()
{
    if (_vision.size() > 1) {
        if (_vision[1].player > 0) { // vérifie si il y a un joueur dans la case qui suit
            return true;
        }
    }
    return false;
}

bool Clientia::needtoincant()
{
    if (playerlevel >= 8)
        return false;
    Incantation requis = incant[playerlevel - 1];

    if (_vision.empty())
        return false;
    const auto& currentTile = _vision[0];
    
    if (currentTile.player < requis.nbrplayers) {
        return false;
    }

    if (inventory.linemate < requis.linemate ||
       inventory.deraumere < requis.deraumere ||
       inventory.sibur < requis.sibur ||
       inventory.mendiane < requis.mendiane ||
       inventory.phiras < requis.phiras ||
       inventory.thystame < requis.thystame) {
        return false;
    }
    return true;
}

bool Clientia::dropressource()
{
    if (playerlevel > 7)
        return false;   

    Incantation req = incant[playerlevel - 1];

    if (inventory.linemate < req.linemate)
        return false;
    if (inventory.deraumere < req.deraumere)
        return false;
    if (inventory.sibur < req.sibur)
        return false;
    if (inventory.mendiane < req.mendiane)
        return false;
    if (inventory.phiras < req.phiras)
        return false;
    if (inventory.thystame < req.thystame)
        return false;

    return true;
}

bool Clientia::requiredrocks()
{
    Incantation requis = incant[playerlevel - 1];

    if (inventory.linemate < requis.linemate ||
       inventory.deraumere < requis.deraumere ||
       inventory.sibur < requis.sibur ||
       inventory.mendiane < requis.mendiane ||
       inventory.phiras < requis.phiras ||
       inventory.thystame < requis.thystame) {
        return false;
    }
    return true;
}

int Clientia::neededplayer()
{
    Incantation requis = incant[playerlevel - 1];
    return requis.nbrplayers;
}

bool Clientia::requiredplayers()
{
    Incantation requis = incant[playerlevel - 1];
    const auto& current = _vision[0];

    if (current.player >= requis.nbrplayers) {
        return true;
    }

    return false;
}

bool Clientia::makefork()
{
    if (inventory.food > danger && actualpinequip < 6)
        return true;
    return false;
}

bool Clientia::isBroadcastInteresting()
{
    return true;
}

bool Clientia::makeject()
{
    return false;
}

void Clientia::planFoodSearch()
{
    if (_vision[0].food > 0) {
        _action.push("Take food");
        _action.push("Look");
        _action.push("Inventory");
    } else {
        findShortestPath("food");
    }
}

void Clientia::planRockSearch()
{
    if (_vision[0].linemate > 0) {
        _action.push("Take linemate");
        _action.push("Look");
        _action.push("Inventory");
    } else if (_vision[0].deraumere > 0) {
        _action.push("Take deraumere");
        _action.push("Look");
        _action.push("Inventory");
    } else if (_vision[0].sibur > 0) {
        _action.push("Take sibur");
        _action.push("Look");
        _action.push("Inventory");
    } else if (_vision[0].mendiane > 0) {
        _action.push("Take mendiane");
        _action.push("Look");
        _action.push("Inventory");
    } else if (_vision[0].phiras > 0) {
        _action.push("Take phiras");
        _action.push("Look");
        _action.push("Inventory");
    } else if (_vision[0].thystame > 0) {
        _action.push("Take thystame");
        _action.push("Look");
        _action.push("Inventory");
    } else {
        collectpath();
    }
}
void Clientia::planBroadcast()
{
    _action.push("Broadcast Level");
}

void Clientia::planFork()
{
    _action.push("Fork");
}

void Clientia::planExploration()
{
    _action.push("Look");
    _action.push("Inventory");
    int dir = rand() % 3;

    if (dir == 0) {
        _action.push("Forward");
    } else if (dir == 1) {
        _action.push("Right");
        _action.push("Forward");
    } else if (dir == 2) {
        _action.push("Left");
        _action.push("Forward");
    }
}

void Clientia::planEject()
{
    _action.push("Eject");
}

void Clientia::planRespondToBroadcast()
{
    // Si le message vient de la même case
    if (direction == 0)
        return;

    if (direction == 1)
        _action.push("Forward");
    else if (direction == 2) {
        _action.push("Forward");
        _action.push("Left");
        _action.push("Forward");
    } else if (direction == 3) {
        _action.push("Left");
        _action.push("Forward");   
    } else if (direction == 4) {
        _action.push("Left");
        _action.push("Forward");
        _action.push("Left");
        _action.push("Forward");        
    } else if (direction == 5) {
        _action.push("Left");
        _action.push("Left");
        _action.push("Forward");
    } else if (direction == 6) {
        _action.push("Right");
        _action.push("Forward");
        _action.push("Right");
        _action.push("Forward");        
    } else if (direction == 7) {
        _action.push("Right");
        _action.push("Forward");
    } else if (direction == 8) {
        _action.push("Forward");
        _action.push("Right");
        _action.push("Forward");
    }
    std::cout << "DIRECTION: " << direction << std::endl;
}

void Clientia::planIncantation()
{
    if (playerlevel > 7)
        return;

    Incantation req = incant[playerlevel - 1];
    
    // std::cout << "Linemate: " << req.sibur << std::endl;

    if (inventory.linemate >= req.linemate)
        _action.push("Set linemate");
    if (inventory.deraumere >= req.deraumere)
        _action.push("Set deraumere");
    if (inventory.sibur >= req.sibur)
        _action.push("Set sibur");
    if (inventory.mendiane >= req.mendiane)
        _action.push("Set mendiane");
    if (inventory.phiras >= req.phiras)
        _action.push("Set phiras");
    if (inventory.thystame >= req.thystame)
        _action.push("Set thystame");
    
    _action.push("Incantation");
}

void Clientia::collectpath()
{
    std::vector<std::pair<std::string, int>> needed = getstones();
    
    if (needed.empty()) {
        return;
    }
    
    for (const auto& requirement : needed) {
        const std::string& stone = requirement.first;
        int neededQuantity = requirement.second;

        if (neededQuantity == 0) {
            continue;
        }
        
        if (getstonesquantity(stone) < neededQuantity) {
            for (int i = 1; i < _vision.size(); i++) {
                if (_vision[i].contains(stone)) {
                    if (i <= 3) {
                        planDirectApproach(i, stone);
                    } else {
                        planfindstone(i, stone);
                    }
                    return;
                }
            }
        }   
    }
    planExploration();
}

std::vector<std::pair<std::string, int>> Clientia::getstones()
{
    std::vector<std::pair<std::string, int>> needed;
    
    switch (playerlevel) {
        case 1:
            needed = {{"linemate", 1}, {"deraumere", 0}, {"sibur", 0}, 
                     {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}};
            break;
        case 2:
            needed = {{"linemate", 1}, {"deraumere", 1}, {"sibur", 1}, 
                     {"mendiane", 0}, {"phiras", 0}, {"thystame", 0}};
            break;
        case 3:
            needed = {{"linemate", 2}, {"deraumere", 0}, {"sibur", 1},
                    {"mendiane", 0}, {"phiras", 2}, {"thystame", 0}};
            break;
        case 4:
            needed = {{"linemate", 1}, {"deraumere", 1}, {"sibur", 2},
                    {"mendiane", 0}, {"phiras", 1}, {"thystame", 0}};
            break;
        case 5:
            needed = {{"linemate", 1}, {"deraumere", 2}, {"sibur", 1},
                    {"mendiane", 3}, {"phiras", 0}, {"thystame", 0}};
            break;
        case 6:
            needed = {{"linemate", 1}, {"deraumere", 2}, {"sibur", 3},
                      {"mendiane", 0}, {"phiras", 1}, {"thystame", 0}};
            break;
        case 7:
            needed = {{"linemate", 2}, {"deraumere", 2}, {"sibur", 2}, 
                     {"mendiane", 2}, {"phiras", 2}, {"thystame", 1}};
            break;
    }
    
    return needed;
}

int Clientia::getstonesquantity(const std::string& stone)
{
    if (stone == "linemate")
        return inventory.linemate;
    if (stone == "deraumere")
        return inventory.deraumere;
    if (stone == "sibur")
        return inventory.sibur;
    if (stone == "mendiane")
        return inventory.mendiane;
    if (stone == "phiras")
        return inventory.phiras;
    if (stone == "thystame")
        return inventory.thystame;
    return 0;
}

void Clientia::planfindstone(int visionIndex, const std::string& stone)
{
    if (visionIndex <= 6) {
        _action.push("Forward");
        _action.push("Look");
    } else {
        planExploration();
    }
}

void Clientia::findShortestPath(const std::string& res)
{
    for (int i = 1; i < _vision.size(); i++) {
        if (_vision[i].contains(res)) {
            
            if (i <= 3) {
                planDirectApproach(i, res);
            } else {
                planExploration();
            }
            return;
        }
    }
    planExploration();
}

void Clientia::planDirectApproach(int visionIndex, const std::string& res)
{
    switch (visionIndex) {
        case 1:
            _action.push("Forward");
            break;
            
        case 2:
            _action.push("Forward");
            _action.push("Left");
            _action.push("Forward");
            break;
            
        case 3:
            _action.push("Forward");
            _action.push("Right");
            _action.push("Forward");
            break;
            
        default:
            planExploration();
            return;
    }
    
    _action.push("Take " + res);
    _action.push("Inventory");
}

bool TIlecontent::contains(const std::string &res) const
{
    if (res == "food") {
        if (food > 0)
            return true;
        else
            return false;
    }
    if (res == "linemate") {
        if (linemate > 0)
            return true;
        else
            return false;
    }
    if (res == "deraumere") {
        if (deraumere > 0)
            return true;
        else
            return false;
    }

    if (res == "sibur") {
        if (sibur > 0)
            return true;
        else
            return false;
    }

    if (res == "mendiane") {
        if (mendiane > 0)
            return true;
        else
            return false;
    }
    if (res == "phiras") {
        if (phiras > 0)
            return true;
        else
            return false;
    }
    if (res == "thystame") {
        if (thystame > 0)
            return true;
        else
            return false;
    }
    return false;
}