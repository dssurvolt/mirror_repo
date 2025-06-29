/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-amour.guidi
** File description:
** loop
*/

#include "include/Ai.hpp"

AIAction Clientia::decideAction()
{
    if (!foodneed() && requiredrocks()) {
        if (!_receivebroadcast) {   
            std::string msg = "Broadcast "
                      + std::to_string(playerlevel) + "," 
                      + std::to_string(_clientId);
            _action.push(msg);
            if (requiredplayers()) {   
                if (needtoincant()) {
                    return AIAction::INCANTATION;
                }
            }
        } else {
            return AIAction::RESPOND_BROADCAST;
        }
    } else if (foodneed()) {
        if (_receivebroadcast) {
            return AIAction::RESPOND_BROADCAST;
        }
        if (_vision[0].food > 0) {
            return AIAction::MOVE_AND_TAKE_FOOD;
        }
        
        if (isFoodVisibleAhead()) {
            return AIAction::SEARCH_FOOD;
        } else {
            return AIAction::EXPLORE;
        }
    } else if (!requiredrocks()) {
        if (_vision[0].linemate > 0 || _vision[0].deraumere > 0
            || _vision[0].mendiane > 0 || _vision[0].phiras > 0
            || _vision[0].sibur > 0 || _vision[0].thystame > 0) {
                return AIAction::MOVE_AND_TAKE_ROCK;
        }
    }

    return AIAction::EXPLORE;
}

void Clientia::think()
{
    if (_vision.empty()) { // Pour demander les infos si on ne sait pas
        _action.push("Look");
        return;
    }

    if (inventory.food == 0) { // Pareil pour l'inventaire
        _action.push("Inventory");
        return;
    }

    // Parcourir l'arbre de décision
    AIAction action = decideAction();

    // Planifier les actions
    planAction(action);
    
}

void Clientia::run()
{   
    while (1) {
        if (poll(pfds, 1, 100) > 0) {
            if (pfds[0].revents & POLLIN) {
                readInfo();
            }
        }

        if (current == Connected) {
            think();

            if (!_action.empty() && cmd.empty()) {
                cmd.push(_action.front());
                _action.pop();
            }

            if (!cmd.empty()) {
                std::string currentcmd = cmd.front();
                send_line(currentcmd);
                cmd.pop();  
            }
        }
    }
}

void Clientia::planAction(AIAction action)
{
    switch (action) {
        case AIAction::MOVE_AND_TAKE_FOOD:
            _action.push("Take food");
            _action.push("Inventory");
            break;
            
        case AIAction::SEARCH_FOOD:
            planFoodSearch();
            break;
            
        case AIAction::MOVE_AND_TAKE_ROCK:
            if (_vision[0].linemate > 0)
                _action.push("Take linemate");
            else if (_vision[0].deraumere > 0)
                _action.push("Take deraumere");
            else if (_vision[0].sibur > 0)
                _action.push("Take sibur");
            else if (_vision[0].mendiane > 0)
                _action.push("Take mendiane");
            else if (_vision[0].phiras > 0)
                _action.push("Take phiras");
            else if (_vision[0].thystame > 0)
                _action.push("Take thystame");
            _action.push("Inventory");
            _action.push("Look");
            break;
            
        case AIAction::SEARCH_ROCKS:
            planRockSearch();
            break;

        case AIAction::INCANTATION:
            _action.push("Incantation");
            break;

        case AIAction::BROADCAST:
            planBroadcast();
            break;

        case AIAction::FORK:
            planFork();
            break;

        case AIAction::EJECT:
            planEject();
            break;
            
        case AIAction::RESPOND_BROADCAST:
            planRespondToBroadcast();
            _action.push("Look");
            break;
        
        case AIAction::DROP_RESOURCES_FOR_INCANT:
            planIncantation();
            break;
        
        case AIAction::EXPLORE:
        default:
            planExploration();
            break;
    }
}
