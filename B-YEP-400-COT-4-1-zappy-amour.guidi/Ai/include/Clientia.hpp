/*
-- File: Clientia.hpp
-- Author: amour
-- Date: 2025-21-06 12:55:04 PM
-- Description: Clientia.hpp
*/

#ifndef ZAPPY_CLIENTIA
#define ZAPPY_CLIENTIA

    #include "Library.hpp"
    #include "AIEnums.hpp"
    #include "Tile.hpp"
    #include "Inventory.hpp"

    struct StoneTarget {
        std::string name;
        int tileIndex;
        int distance;
    };

    class Clientia {
        private:
            // Etat de la connexion
            int socketfd;
            std::string team_name;
            int id;
            int port;
            struct pollfd pfds[1];
            AIState current;
            std::queue<std::string> cmd;
            struct sockaddr_in addr;
            int addr_len;

            // État du joueur
            int playerlevel = 1;
            int direction = 0;
            int senderId = 0;
            Inventory inventory;
            int _teammatesCount = 1;
            int frequence = 100;

            // État de la map
            int mapH;
            int mapW;
            std::vector<TIlecontent> _vision;

            // Logique de décision
            std::queue<std::string> _action;

            bool authenticated = false;
            std::vector<std::string> lookresult;
            int actualpinequip = 0;
            int nbr_;
            bool status = false;
            char buffer[4096];
            int broadcastseq = 0;
            std::vector<int> _playerstate;
            std::string _lastBroadcast;
            int danger = 5;
            bool _waitplayer = false;
            int reserve = 9;
            int _clientId = 0;
            bool _receivebroadcast = false;
            int responsesReceived = 1;
            std::string messages;
            bool startbroadcast = false;

        public:
            // Constructeur
            Clientia(int _p, const char *addr_ip, const std::string &team_name);
            ~Clientia();
            void run();

            // Initialisation
            int create_socket();
            struct sockaddr_in create_servor_addr(int p);
            struct pollfd create_poll_struct(int s);
            void buildDecisionTree();
            void send_line(const std::string &line);
            
            // Communication Réseau
            void readInfo();
            int checkstart(char *buf);
            void parseservermessage(const std::string& msg);
            void clearall();

            //Parsing des Messages Serveur
            void parseWelcome();
            void parseNbrclient(const std::string& msg);
            void parseMapSize(const std::string& msg);
            void parseLook(const std::string& msg);
            void parseInventory(const std::string& msg);
            void parseBroadcast(const std::string& msg);
            void parseBroadcaststate(const std::string &msg);

            // Planification d'Actions
            AIAction decideAction();
            void planAction(AIAction action);
            void think();

            // Fonctions de stratégie
            void planFoodSearch();
            void planIncantation();
            void planFork();
            void planBroadcast();
            void planExploration();
            void planEject();
            void planRespondToBroadcast();
            void planRockSearch();
            int calculdist(int pos);

            //Fonctions de Décision pour l'Arbre
            bool foodneed();
            bool isFoodVisibleAhead();
            bool makefork();
            bool needtoincant();
            bool isObstacleVisible();
            bool isBroadcastInteresting();
            bool makeject();
            bool requiredrocks();
            bool requiredplayers();
            bool isRockVisibleAhead();
            void planDirectApproach(int visionIndex, const std::string& res);
            std::vector<std::pair<std::string, int>> getstones();
            int getstonesquantity(const std::string& stone);
            void planfindstone(int visionIndex, const std::string& stone);
            bool dropressource();
            void startIncantation();
            void waitForIncantationResponses();
            int neededplayer();

            // Fonctions pour pour rendre le programme plus optimiser
            void findShortestPath(const std::string& resource);
            void findShortestPathToTile(int targetTile, const std::string& res);
            void collectpath();
            int calculateFoodCost(int actions);
    };

#endif
