#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "controller_i.hpp"

class Player : public ControllerI {
    public:
    direction getNextMove(Snake& snake) {
        int oldDir = snake.getDirection();
        int newDir = oldDir;
        
        if (IsKeyPressed(KEY_UP) || IsKeyDown(KEY_UP)) {
            newDir = NORTH;
        } else if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT)) {
            newDir = EAST;
        } else if (IsKeyPressed(KEY_DOWN) || IsKeyDown(KEY_DOWN)) {
            newDir = SOUTH;
        } else if (IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT)) {
            newDir = WEST;
        }
        
        // check to see if snake would turn into itself
        if (oldDir != (newDir+2)%4) {
            return (direction)newDir;
        }
        
        return (direction)oldDir;
    }
    bool hasNextMove() { return true; }
    void update(Snake& snake) {};
    void newGame(Snake& snake) {};
};

#endif