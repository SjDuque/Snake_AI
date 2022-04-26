#ifndef CONTROLLER_I_HPP
#define CONTROLLER_I_HPP

#include <snake.hpp>

class ControllerI {
    public:
    virtual direction getNextMove(Snake& snake) = 0;
    virtual bool hasNextMove() = 0;
    virtual void update(Snake& snake) = 0;
    virtual void newGame(Snake& snake) = 0;
};

#endif