#ifndef CONTROLLER_I_HPP
#define CONTROLLER_I_HPP

#include <snake.hpp>

class ControllerI {
    public:
    virtual direction getNextMove(Snake& snake) { return NORTH; };
    virtual bool hasNext() { return false; };
};

#endif