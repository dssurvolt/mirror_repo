#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <random>
#include <chrono>
#include <deque>
#include <algorithm>
#include "../../../include/games_libraries/nibbler/nibbler.hpp"

CellType Cell::getType() const { return _type; }
void Cell::setType(CellType type) { _type = type; }
std::pair<int, int> Cell::getPosition() const { return _position; }

Arcade::DATA Cell::toDATA() const {
    char character;
    std::string spritePath;
    
    switch (_type) {
        case CellType::WALLS:
            character = '#';
            spritePath = "../../../asserts/nibbler/wall.png";
            break;
        case CellType::FOOD:
            character = '*';
            spritePath = "../../../asserts/nibbler/food.png";
            break;
        case CellType::SNAKE_HEAD:
            character = 'O';
            spritePath = "../../../asserts/nibbler/snake_head.png";
            break;
        case CellType::SNAKE_BODY:
            character = 'o';
            spritePath = "../../../asserts/nibbler/snake_body.png";
            break;
        case CellType::EMPTY:
        default:
            character = ' ';
            spritePath = "../../../asserts/nibbler/empty.png";
            break;
    }

    Arcade::DATA data;
    data.setPosNcurses({static_cast<float>(_position.first), static_cast<float>(_position.second)});
    data.setPosSprite({static_cast<float>(_position.first) * 32, static_cast<float>(_position.second) * 32});
    data.setSize({1.0f, 1.0f});
    data.setCharacterNcurses(character);
    data.setSpritePath(spritePath);
    return data;
    
    // return Arcade::DATA(
    //     {static_cast<float>(_position.first), static_cast<float>(_position.second)},
    //     {static_cast<float>(_position.first) * 32, static_cast<float>(_position.second) * 32},
    //     {1.0f, 1.0f},
    //     character,
    //     spritePath
    // );
}

std::pair<int, int> Food::getPosition() const { return _position; }
void Food::setPosition(std::pair<int, int> position) { _position = position; }

const std::deque<std::pair<int, int>>& Snake::getBody() const { return _body; }
Direction Snake::getDirection() const { return _direction; }
void Snake::setDirection(Direction direction) { _direction = direction; }
    
std::pair<int, int> Snake::getHead() const { return _body.front(); }
std::pair<int, int> Snake::getTail() const { return _body.back(); }
    
void Snake::move() {
    std::pair<int, int> newHead = getHead();
    
    switch (_direction) {
        case Direction::UP:
            newHead.second--;
            break;
        case Direction::DOWN:
            newHead.second++;
            break;
        case Direction::LEFT:
            newHead.first--;
            break;
        case Direction::RIGHT:
            newHead.first++;
            break;
    }
    
    _body.push_front(newHead);
    
    if (!_isGrowing) {
        _body.pop_back();
    } else {
        _isGrowing = false;
    }
}
    
void Snake::grow() {
    _isGrowing = true;
}
    
bool Snake::checkCollisionWithSelf() const {
    if (_body.size() <= 1) return false;
    
    auto head = getHead();
    for (size_t i = 1; i < _body.size(); i++) {
        if (_body[i] == head) {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<CellType>> MapLoader::loadMap(const std::string& filename) {
    std::vector<std::vector<CellType>> map;
    std::ifstream mapFile(filename);
    
    if (!mapFile.is_open()) {
        throw std::runtime_error("Failed to open map file: " + filename);
    }
    
    std::string line;
    while (getline(mapFile, line)) {
        std::vector<CellType> row;
        for (char c : line) {
            switch (c) {
                case '#':
                    row.push_back(CellType::WALLS);
                    break;
                case '*':
                    row.push_back(CellType::FOOD);
                    break;
                case ' ':
                default:
                    row.push_back(CellType::EMPTY);
                    break;
            }
        }
        map.push_back(row);
    }
    
    mapFile.close();
    return map;
}

    void Nibbler::initializeGame() {
        _status = Arcade::STATUS::NONE;
        _timeRemaining = 300;
        _updateCounter = 0;
        _score = 0;
        _level = 1;
        _gameSpeed = 10;
    }
    
    void Nibbler::loadLevel(const std::string& filename) {
        auto mapData = MapLoader::loadMap(filename);
        _height = mapData.size();
        _width = mapData[0].size();
        
        _map.clear();
        for (int y = 0; y < _height; y++) {
            std::vector<Cell> row;
            for (int x = 0; x < _width; x++) {
                row.push_back(Cell(mapData[y][x], {x, y}));
            }
            _map.push_back(row);
        }
        
        std::pair<int, int> spawnPos = {0, _height - 2};
        for (int x = 1; x < _width - 1; x++) {
            if (_map[_height - 2][x].getType() == CellType::EMPTY) {
                spawnPos = {x, _height - 2};
                break;
            }
        }
        _snake = Snake();
        _foods.clear();
        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                if (_map[y][x].getType() == CellType::FOOD) {
                    _foods.push_back(Food({x, y}));
                }
            }
        }
        
        updateMapWithSnake();
    }
    
    void Nibbler::updateMapWithSnake() {
        for (int y = 0; y < _height; y++) {
            for (int x = 0; x < _width; x++) {
                if (_map[y][x].getType() == CellType::SNAKE_HEAD || 
                    _map[y][x].getType() == CellType::SNAKE_BODY) {
                    _map[y][x].setType(CellType::EMPTY);
                }
            }
        }
        
        auto head = _snake.getHead();
        if (head.first >= 0 && head.first < _width && 
            head.second >= 0 && head.second < _height) {
            _map[head.second][head.first].setType(CellType::SNAKE_HEAD);
        }
        
        auto body = _snake.getBody();
        for (size_t i = 1; i < body.size(); i++) {
            auto segment = body[i];
            if (segment.first >= 0 && segment.first < _width && 
                segment.second >= 0 && segment.second < _height) {
                _map[segment.second][segment.first].setType(CellType::SNAKE_BODY);
            }
        }
    }
    
    void Nibbler::update() {
        _updateCounter++;
        
        if (_updateCounter >= _gameSpeed) {
            _updateCounter = 0;
            
            autoNavigate();
            _snake.move();
            
            auto head = _snake.getHead();
            
            if (head.first < 0 || head.first >= _width || 
                head.second < 0 || head.second >= _height || 
                _map[head.second][head.first].getType() == CellType::WALLS) {
                handleWALLSCollision();
            }
            
            auto foodIt = std::find_if(_foods.begin(), _foods.end(),
                [head](const Food& food) { return food.getPosition() == head; });
                
            if (foodIt != _foods.end()) {
                _snake.grow();
                _score += 10;
                _foods.erase(foodIt);
                
                if (_foods.empty()) {
                    if(_level == 3) {
                        _status = Arcade::STATUS::VICTORY;
                        return;
                    }
                    _level++;
                    _timeRemaining += 300;
                    auto str = "../../../asserts/nibbler/level" + std::to_string(_level) + ".txt";
                    loadLevel(str);
                }
            }
            
            if (_snake.checkCollisionWithSelf()) {
                _status = Arcade::STATUS::LOSE;
                return;
            }
            
            if (_timeRemaining > 0) {
                _timeRemaining--;
            } else {
                _status = Arcade::STATUS::LOSE;
                return;
            }
            
            updateMapWithSnake();
        }
    }

    std::string Nibbler::getKeyInput() {
        std::string input;
        std::cout << "Appuyez sur une touche (gauche: 'l', droite: 'r') puis Entrée : ";
        std::cin >> input;
        return input;
    }
    
    void Nibbler::autoNavigate() {
        auto head = _snake.getHead();
        Direction currentDir = _snake.getDirection();
        std::pair<int, int> nextPos = head;
        
        switch (currentDir) {
            case Direction::UP:
                nextPos.second--;
                break;
            case Direction::DOWN:
                nextPos.second++;
                break;
            case Direction::LEFT:
                nextPos.first--;
                break;
            case Direction::RIGHT:
                nextPos.first++;
                break;
        }
        
        if (nextPos.first < 0 || nextPos.first >= _width || 
            nextPos.second < 0 || nextPos.second >= _height || 
            _map[nextPos.second][nextPos.first].getType() == CellType::WALLS) {
            
            Direction leftDir, rightDir;
            
            switch (currentDir) {
                case Direction::UP:
                    leftDir = Direction::LEFT;
                    rightDir = Direction::RIGHT;
                    break;
                case Direction::DOWN:
                    leftDir = Direction::RIGHT;
                    rightDir = Direction::LEFT;
                    break;
                case Direction::LEFT:
                    leftDir = Direction::DOWN;
                    rightDir = Direction::UP;
                    break;
                case Direction::RIGHT:
                    leftDir = Direction::UP;
                    rightDir = Direction::DOWN;
                    break;
            }
            
            std::pair<int, int> leftPos = head;
            switch (leftDir) {
                case Direction::UP:
                    leftPos.second--;
                    break;
                case Direction::DOWN:
                    leftPos.second++;
                    break;
                case Direction::LEFT:
                    leftPos.first--;
                    break;
                case Direction::RIGHT:
                    leftPos.first++;
                    break;
            }
            
            std::pair<int, int> rightPos = head;
            switch (rightDir) {
                case Direction::UP:
                    rightPos.second--;
                    break;
                case Direction::DOWN:
                    rightPos.second++;
                    break;
                case Direction::LEFT:
                    rightPos.first--;
                    break;
                case Direction::RIGHT:
                    rightPos.first++;
                    break;
            }
            
            bool canTurnLeft = !(leftPos.first < 0 || leftPos.first >= _width || 
                                leftPos.second < 0 || leftPos.second >= _height || 
                                _map[leftPos.second][leftPos.first].getType() == CellType::WALLS);
                                
            bool canTurnRight = !(rightPos.first < 0 || rightPos.first >= _width || 
                                rightPos.second < 0 || rightPos.second >= _height || 
                                _map[rightPos.second][rightPos.first].getType() == CellType::WALLS);
            
            if (canTurnLeft && canTurnRight) {
                bool running = true;
                
                while (running) {
                    std::string key = getKeyInput();
                
                    if (key == "l") {
                        _snake.setDirection(leftDir);
                        running = false;
                    } else if (key == "r") {
                        _snake.setDirection(rightDir);
                        running = false;
                    } else {
                        std::cout << "Touche invalide, réessayez.\n";
                    }
                }
                // _snake.setDirection(leftDir);
            } 
            else if (canTurnLeft) {
                _snake.setDirection(leftDir);
            } 
            else if (canTurnRight) {
                _snake.setDirection(rightDir);
            }
        }
    }
    
    void Nibbler::handleWALLSCollision() {
    }
    
    Direction Nibbler::keyToDirection(Arcade::KEY key) {
        switch (key) {
            case Arcade::KEY::UP:
                return Direction::UP;
            case Arcade::KEY::DOWN:
                return Direction::DOWN;
            case Arcade::KEY::LEFT:
                return Direction::LEFT;
            case Arcade::KEY::RIGHT:
                return Direction::RIGHT;
            default:
                return _snake.getDirection();
        }
    }
    
    void Nibbler::movePlayer(Arcade::KEY key) {
        if (key != Arcade::KEY::NOTHING && key != Arcade::KEY::SPACE) {
            Direction newDir = keyToDirection(key);
            
            Direction currentDir = _snake.getDirection();
            if ((currentDir == Direction::UP && newDir != Direction::DOWN) ||
                (currentDir == Direction::DOWN && newDir != Direction::UP) ||
                (currentDir == Direction::LEFT && newDir != Direction::RIGHT) ||
                (currentDir == Direction::RIGHT && newDir != Direction::LEFT)) {
                _snake.setDirection(newDir);
            }
        }
        
        update();
    }
    
    std::vector<Arcade::DATA> Nibbler::getDATA() {
        std::vector<Arcade::DATA> data;
        
        for (const auto& row : _map) {
            for (const auto& cell : row) {
                data.push_back(cell.toDATA());
            }
        }
        
        return data;
    }
    
    Arcade::STATUS Nibbler::getStatus() {
        return _status;
    }
    
    void Nibbler::nextLevel() {
        _level++;
        loadLevel("../../../asserts/nibbler/level" + std::to_string(_level) + ".txt");
    }
    
    int Nibbler::getScore() {
        return _score;
    }
    
    int Nibbler::getTimeRemaining() const {
        return _timeRemaining;
    }
    
    int Nibbler::getLevel() const {
        return _level;
    }

extern "C" std::unique_ptr<Nibbler> instance() {
    return std::make_unique<Nibbler>();
}
// extern "C" Arcade::IGAME* createGame() {
//     return new Nibbler("level1.txt");
// }


// extern "C" void destroyGame(Arcade::IGAME* game) {
//     delete game;
// }
