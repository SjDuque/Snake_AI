#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <list>
#include <vector>

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
        bool collided;
        int length;

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

};

#endif