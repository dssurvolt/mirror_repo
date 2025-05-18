#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <random>
#include <chrono>
#include <deque>
#include <algorithm>
#include "../../arcade.hpp"

class Cell;
class Food;
class Snake;
class MapLoader;

enum class CellType {
    EMPTY,
    WALLS,
    FOOD,
    SNAKE_HEAD,
    SNAKE_BODY
};

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Cell {
private:
    CellType _type;
    std::pair<int, int> _position;
    
public:
    Cell(CellType type = CellType::EMPTY, std::pair<int, int> position = {0, 0})
        : _type(type), _position(position) {}
    
    CellType getType() const;
    void setType(CellType type);
    std::pair<int, int> getPosition() const;
    
    Arcade::DATA toDATA() const;
};

class Food {
private:
    std::pair<int, int> _position;
    
public:
    Food(std::pair<int, int> position = {0, 0}) : _position(position) {}
    
    std::pair<int, int> getPosition() const;
    void setPosition(std::pair<int, int> position);
};

class Snake {
private:
    std::deque<std::pair<int, int>> _body;
    Direction _direction;
    bool _isGrowing;
    
public:
    Snake(std::pair<int, int> startPosition = {16, 31}, Direction startDirection = Direction::RIGHT) 
        : _direction(startDirection), _isGrowing(false) {
        _body.push_front(startPosition);
        
        std::pair<int, int> nextPos = startPosition;
        for (int i = 0; i < 3; i++) {
            switch (_direction) {
                case Direction::UP:
                    nextPos.second++;
                    break;
                case Direction::DOWN:
                    nextPos.second--;
                    break;
                case Direction::LEFT:
                    nextPos.first++;
                    break;
                case Direction::RIGHT:
                    nextPos.first--;
                    break;
            }
            _body.push_back(nextPos);
        }
    }
    
    const std::deque<std::pair<int, int>>& getBody() const;
    Direction getDirection() const;
    void setDirection(Direction direction);
    
    std::pair<int, int> getHead() const;
    std::pair<int, int> getTail() const;
    
    void move();
    
    void grow();
    
    bool checkCollisionWithSelf() const;
};

class MapLoader {
public:
    static std::vector<std::vector<CellType>> loadMap(const std::string& filename);
};

class Nibbler : public Arcade::AGAME {
private:
    int _width;
    int _height;
    std::vector<std::vector<Cell>> _map;
    Snake _snake;
    std::vector<Food> _foods;
    Arcade::STATUS _status;
    int _timeRemaining;
    int _level;
    int _score;
    int _updateCounter;
    int _gameSpeed;
    
    void initializeGame();
    
    void loadLevel(const std::string& filename);
    
    void updateMapWithSnake();
    
    void update();

    std::string getKeyInput();
    
    void autoNavigate();
    
    void handleWALLSCollision();
    
    Direction keyToDirection(Arcade::KEY key);
    
public:
    Nibbler(const std::string& mapFile = "level1.txt") {
        initializeGame();
        loadLevel(mapFile);
    }
    
    void movePlayer(Arcade::KEY key) override;
    
    std::vector<Arcade::DATA> getDATA() override;
    
    Arcade::STATUS getStatus() override;
    
    void nextLevel();
    
    int getScore() override;
    
    int getTimeRemaining() const;
    
    int getLevel() const;
};

// extern "C" IGAME* createGame() {
//     return new Nibbler("level1.txt");
// }
// extern "C" Arcade::IGAME* createGame() {
//     return new Nibbler("level1.txt");
// }