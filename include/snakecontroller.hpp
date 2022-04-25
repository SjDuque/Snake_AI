#ifndef SNAKECONTROLLER_HPP
#define SNAKECONTROLLER_HPP

#include "raylib.h"
#include "snake.hpp"

class Snakecontroller {
    private:
        Snake gameBoard;
        bool paused;
    public:
        Snakecontroller(int rows=30, int cols=30, int startScore = 3, int growthRate = 1);

        void draw();
        void update();
        void newGame();
        
        void chooseDirection(direction dir);
        game_status getGameStatus() { return gameBoard.getStatus(); }
        void readInput();
        
        int rows() { return gameBoard.rows(); }
        int cols() { return gameBoard.cols(); }
};


#endif