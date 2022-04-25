#include <cmath>

#include "snake_game.hpp"
#include "raylib.h"

SnakeGame::SnakeGame(ControllerI* input, int rows, int cols, int startScore, int growthRate) : input(input) {
    snake = Snake(rows, cols, startScore, growthRate);
    paused = false;
}

void SnakeGame::draw() {
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    
    int screen = (width < height) ? width : height;
    int side = (rows() > cols()) ? rows() : cols();
    
    float scale = ((float) screen) / side;
    
    for (int r = 0; r < rows(); r++) {
        for (int c = 0; c < cols(); c++) {
            Color color = MAGENTA;
            grid_value cell = snake.getCell(r, c);
            
            if (cell == EMPTY) {
                color = BLACK;
            } else if (cell == BODY) {
                color = WHITE;
            } else if (cell == APPLE) {
                color = RED;
            }
            
            DrawRectangle(ceil(r * scale), ceil(c * scale), ceil(scale), ceil(scale), color);
        }
    }
}

void SnakeGame::update() {
    direction nextDir = input->getNextMove(snake);
    snake.setDirection(nextDir);
    snake.move();
}