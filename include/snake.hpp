#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <list>
#include <vector>
#include <cstdlib>

enum grid_value {
    EMPTY,
    BODY,
    APPLE,
    OUT_OF_BOUNDS
};

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum game_status {
    ACTIVE,
    COLLIDED,
    PAUSED,
    WIN
};

class Snake {
    
    private:
        /**
         * @brief stores x and y coords
         * 
         */
        struct Point {
            int x, y;
        };

        static const int GROWTH = 1;
          
        std::list<Point> body;
        std::vector<std::vector<grid_value>> grid;
        direction dir;
        int length;
        game_status status;

        void addFront(int x, int y);
        void deleteTail();
        void shift();
        Point shiftDirection(Point prev, direction dir);
        
    public:
        Snake();
        Snake(int width, int height);
        
        Point getHead();
        Point getTail();
        grid_value getCell(int x, int y);
        void move();
        void setDirection(direction dir) { this->dir = dir; }
        direction getDirection() { return this->dir; }
        void createFruit();
        game_status getStatus() { return this->status; }
};

#endif