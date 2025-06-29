/*
-- File: Tile.hpp
-- Author: Amour
-- Date: 2025-21-06 12:50:09 PM
-- Description: Title file
*/

#ifndef ZAPPY_TILE
#define ZAPPY_TILE

    #include <string>

     // Tile content on the map
    struct TIlecontent {
        int player = 0;
        int food = 0;
        int linemate = 0;
        int deraumere = 0;
        int sibur = 0;
        int mendiane = 0;
        int phiras = 0;
        int thystame = 0;
        bool contains(const std::string &ressource) const;
    };


#endif
