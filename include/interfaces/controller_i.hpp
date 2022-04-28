#ifndef CONTROLLER_I_HPP
#define CONTROLLER_I_HPP

#include "game_i.hpp"

class ControllerI {
    public:
    virtual const int getNextMove(GameI& game) = 0;
    virtual void update(GameI& game) = 0;
    virtual void reset(GameI& game) = 0;
};

#endif