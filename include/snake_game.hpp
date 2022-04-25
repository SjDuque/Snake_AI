#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "snake.hpp"
#include "controller_i.hpp"

class SnakeGame {
    private:
    ControllerI* input;
    Snake snake;
    bool paused;
    public:
    
    SnakeGame() {}
    SnakeGame(ControllerI* input, int rows=30, int cols=30, int startScore = 3, int growthRate = 1);

    void draw();
    void update();
    void newGame() { snake.newGame(); }
    
    game_status getStatus() { return snake.getStatus(); }
    
    int rows() { return snake.rows(); }
    int cols() { return snake.cols(); }
};


#endif