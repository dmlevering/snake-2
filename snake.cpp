#include "snake.h"

//constructor for SnakeGame
SnakeGame::SnakeGame() {
    srand(time(NULL));
    _direction = Direction::East;
    _game_board.resize(20);
    for(size_t i = 0; i < 20; i++) {
        _game_board[i].resize(20);
    }
    //set up the coordinates/empty board
    for(size_t i = 0; i < 20; i++) {
        for(size_t j = 0; j < 20; j++) {
            _game_board[i][j] = new Tile(i, j, TileInfo::Empty);
        }
    }
    _head = _game_board[3][8];
    _snake.push_back(_head);
    _food = _game_board[rand()%20][rand()%20];
    _score = 1;
    _r = rand()%255;
    _g = rand()%255;
    _b = rand()%255;
    _gameover = false;
    _just_ate = false;
}

//big 3 for SnakeGame
//destructor
SnakeGame::~SnakeGame() {
    clear();
}

//copy constructor
SnakeGame::SnakeGame(const SnakeGame& other) {
    copy(other);
}

//assignment operator
SnakeGame& SnakeGame::operator=(const SnakeGame& other) {
    if(this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

void SnakeGame::clear() {
    for(size_t i = 0; i < 20; i++) {
        for(size_t j = 0; j < 20; j++) {
            delete _game_board[i][j];
        }
    }
}

void SnakeGame::copy(const SnakeGame& other) {
    srand(time(NULL));
    _direction = other._direction;
    _game_board.resize(20);
    for(size_t i = 0; i < 20; i++) {
        _game_board[i].resize(20);
    }
    for(size_t i = 0; i < 20; i++) {
        for(size_t j = 0; j < 20; j++) {
            Tile* t = other._game_board[i][j];
            _game_board[i][j] = new Tile(t->_x, t->_y, t->_info);
        }
    }
    _head = _game_board[3][8];
    _snake.push_back(_head);
    _food = _game_board[rand()%20][rand()%20];
    _score = 1;
    _r = rand()%255;
    _g = rand()%255;
    _b = rand()%255;
    _gameover = false;
    _just_ate = false;
}

//default constructor for Tile
Tile::Tile() {
    _x = -1;
    _y = -1;
    _info = TileInfo::Empty;
}
//actual constructor for Tile
Tile::Tile(int x, int y, TileInfo info)
    : _x(x), _y(y), _info(info)
{/*nothing to see here, move along*/}

void SnakeGame::reset() {
    _direction = Direction::East;
    //set up the coordinates/empty board
    for(size_t i = 0; i < 20; i++) {
        for(size_t j = 0; j < 20; j++) {
            _game_board[i][j]->_info = TileInfo::Empty;
        }
    }
    _head = _game_board[3][8];
    _snake = {};
    _snake.push_back(_head);
    _food = _game_board[rand()%20][rand()%20];
    _score = 1;
    _r = rand()%255;
    _g = rand()%255;
    _b = rand()%255;
    _gameover = false;
    _just_ate = false;
}

void SnakeGame::draw_board(sf::RenderWindow& window) {
    std::list<Tile*> snake_copy = _snake;
    for(size_t i = 0; i < _snake.size(); i++) {
        Tile* t = snake_copy.front();
        draw_snake(window, t->_x, t->_y);
        snake_copy.pop_front();
    }
    draw_food(window, _food->_x, _food->_y);
}

void SnakeGame::update_model() {
    int x = _head->_x;
    int y = _head->_y;
    switch (_direction) {
        case Direction::East:
            if(x+1 > 19) {
                x -= 20;
            }
            _snake.push_front(_game_board[x+1][y]);
            break;
        case Direction::West:
            if(x-1 < 0) {
                x += 20;
            }
            _snake.push_front(_game_board[x-1][y]);
            break;
        case Direction::North:
            if(y-1 < 0) {
                y += 20;
            }
            _snake.push_front(_game_board[x][y-1]);
            break;
        case Direction::South:
            if(y+1 > 19) {
                y -= 20;
            }
            _snake.push_front(_game_board[x][y+1]);
            break;
    }
    if(!_just_ate) {
        if(_snake.front()->_info == TileInfo::Snake) {
            _gameover = true;
            std::cout << "score: " << _score << std::endl;
        }
    }

    _snake.front()->_info = TileInfo::Snake;

    if(_head == _food) {
        //change food location
        _food = _game_board[rand()%20][rand()%20];
        _score++;
        _just_ate = true;
        //update food and snake color
        _r = rand()%210 + 40;
        _g = rand()%210 + 40;
        _b = rand()%210 + 40;
    }
    else {
        //don't grow
        if(_snake.back() != _food) {
            _snake.back()->_info = TileInfo::Empty;
        }
        _snake.pop_back();
    }
    _head = _snake.front();
}

void SnakeGame::draw_food(sf::RenderWindow& window, int x, int y) {
    sf::CircleShape c;
    c.setFillColor({_r, _g, _b});
    c.setRadius(10);
    c.setPosition(x*20, y*20);
    window.draw(c);
}

void SnakeGame::draw_snake(sf::RenderWindow& window, int x, int y) {
    sf::RectangleShape r(sf::Vector2f(19, 19));
    if(_just_ate) {
        _r = rand()%210 + 40;
        _g = rand()%210 + 40;
        _b = rand()%210 + 40;
    }
    r.setFillColor({_r, _g, _b});
    r.setPosition(x*20, y*20);
    window.draw(r);
}


void SnakeGame::play() {
    //anti-aliasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    //create window
    sf::RenderWindow window(sf::VideoMode(400, 400), "Snake 2", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setFramerateLimit(15);
    int ate_counter = 0;
    while(window.isOpen()) {
        if(_just_ate) {
            ate_counter++;
            if(ate_counter > 10) {
                _just_ate = false;
                ate_counter = 0;
            }
        }
        if(!_just_ate) {
        }
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while(window.pollEvent(event)) {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed) {
                window.close();
                std::cout << "bye." << std::endl;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          _direction = Direction::West;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          _direction = Direction::East;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          _direction = Direction::North;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          _direction = Direction::South;
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        //draw stuff
        if(!_gameover) {
            update_model();
        }
        else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                _gameover = false;
                reset();
            }
        }
        draw_board(window);

        // end the current frame
        window.display();
    }
}

int main() {
    SnakeGame game;
    game.play();
    return 0;
}