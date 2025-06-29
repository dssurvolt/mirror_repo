/*
-- File: AIEnums.hpp
-- Author: saliehsab-#! && Amour
-- Date: 2025-21-06 12:40:45 PM
-- Description: AIEnums file
*/

#ifndef ZAPPY_AI_ENUMS
#define ZAPPY_AI_ENUMS

    // Enum de State de l'ia 
    enum AIState {
        Connecting,
        Welcome,
        TeamName,
        Connected,
        waiting_player,
        waiting_forincantation
    };

    // Struct d'actions de l'ia 
    enum AIAction {
        SEARCH_FOOD,
        MOVE_AND_TAKE_FOOD,
        SEARCH_ROCKS,
        MOVE_AND_TAKE_ROCK,
        INCANTATION,
        START_INCANTATION,
        BROADCAST,
        FORK,
        EJECT,
        EXPLORE,
        RESPOND_BROADCAST,
        DROP_RESOURCES_FOR_INCANT,
    };

#endif
