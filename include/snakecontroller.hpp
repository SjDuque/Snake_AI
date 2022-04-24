#ifndef SNAKECONTROLLER_HPP
#define SNAKECONTROLLER_HPP

#include "snake.hpp"
#include "raylib.h"

class Snakecontroller {
    private:
        Snake gameBoard;
        bool paused;
        int width;
        int height;
    public:
        Snakecontroller();
        Snakecontroller(int width, int height);

        void draw();
        void update();
        void chooseDirection(direction dir);
        game_status getGameStatus() { return gameBoard.getStatus(); }
        void readInput();
};


#endif