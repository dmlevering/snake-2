#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <list>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
using std::string;

enum class Direction {
    North, South, East, West
};

enum class TileInfo {
    Empty, Food, Snake
};

class Tile {
public:
    Tile();
    Tile(int x, int y, TileInfo type);

    int _x;
    int _y;
    TileInfo _info;
};

class SnakeGame {
public:
    SnakeGame();
    //big 3
    SnakeGame(const SnakeGame& other);
    ~SnakeGame();
    SnakeGame& operator=(const SnakeGame& other);
    //the game loop
    void play();
private:
    void update_model();

    //graphics
    void draw_board(sf::RenderWindow& window);
    void draw_food(sf::RenderWindow& window, int x, int y);
    void draw_snake(sf::RenderWindow& window, int x, int y);

    //helpers
    void copy(const SnakeGame& other);
    void clear();
    void reset();

    Tile* _head;
    Tile* _food;
    std::list<Tile*> _snake;
    std::vector<std::vector<Tile*> > _game_board;
    Direction _direction;
    int _score;
    unsigned char _r, _g, _b;
    bool _gameover;
    bool _just_ate;
};

#endif
