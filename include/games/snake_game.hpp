#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include "snake.hpp"
#include "interfaces/game_i.hpp"
#include "interfaces/controller_i.hpp"

class SnakeGame : public GameI {
    private:
    ControllerI* input;
    Snake snake;
    
    public:
    
    SnakeGame(ControllerI* input, int rows=30, int cols=30, int startScore = 3, int growthRate = 1);

    void draw();
    void update();
    void reset();
    
    Snake& getSnake() { return snake; }
};


#endif