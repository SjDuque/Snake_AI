#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "snake.hpp"
#include "raylib.h"
#include "controller_i.hpp"

class SnakePlayer : public ControllerI {
    public:
    const int getNextMove(GameI& game) {
        Snake& snake = (Snake&) game;
        int oldDir = snake.getDirection();
        int newDir = oldDir;
        
        if (IsKeyPressed(KEY_UP) || IsKeyDown(KEY_UP)) {
            newDir = Snake::NORTH;
        } else if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT)) {
            newDir = Snake::EAST;
        } else if (IsKeyPressed(KEY_DOWN) || IsKeyDown(KEY_DOWN)) {
            newDir = Snake::SOUTH;
        } else if (IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT)) {
            newDir = Snake::WEST;
        }
        
        // check to see if snake would turn into itself
        if (oldDir != (newDir+2)%4) {
            return newDir;
        }
        
        return oldDir;
    }
    void update(Snake& snake) {};
    void newGame(Snake& snake) {};
};

#endif