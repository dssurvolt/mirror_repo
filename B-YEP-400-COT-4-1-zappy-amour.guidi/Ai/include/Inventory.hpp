/*
-- File: Inventory.hpp
-- Author: saliehsab-#! && Amour
-- Date: 2025-21-06 12:46:15 PM
-- Description: Inventory file
*/

#ifndef ZAPPY_INVENTORY
#define ZAPPY_INVENTORY

    // Inventaire du joueur 
    struct Inventory {
        int food = 10;
        int linemate = 0;
        int deraumere = 0;
        int sibur = 0;
        int mendiane = 0;
        int phiras = 0;
        int thystame = 0;
    };

    // Prérequis pour une incantation
    struct Incantation {
        int nbrplayers;
        int linemate;
        int deraumere;
        int sibur;
        int mendiane;
        int phiras;
        int thystame;
    };

    extern Incantation incant[8];

#endif
