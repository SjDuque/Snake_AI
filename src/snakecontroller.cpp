#include "snakecontroller.hpp"

Snakecontroller::Snakecontroller() {    }

Snakecontroller::Snakecontroller(int width, int height) {
    gameBoard = Snake(width, height);
    paused = false;
    this->width = width;
    this->height = height;
}

void Snakecontroller::draw() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Color color = MAGENTA;
            grid_value cell = gameBoard.getCell(x, y);
            
            if (cell == EMPTY) {
                color = BLACK;
            } else if (cell == BODY) {
                color = WHITE;
            } else if (cell == APPLE) {
                color = RED;
            }
            
            DrawRectangle(x * 10, y * 10, 10, 10, color);
        }
    }
}

void Snakecontroller::update() {
    gameBoard.move();
}

/**
 * @brief Changes snake direction to turn left or right.
 * 
 * @param dir 
 */
void Snakecontroller::chooseDirection(direction dir) {
    if (gameBoard.getDirection() / 2 != dir / 2)
        gameBoard.setDirection(dir);
}

void Snakecontroller::readInput() {
    if (IsKeyPressed(KEY_UP) || IsKeyDown(KEY_UP)) {
        chooseDirection(UP);
    } else if (IsKeyPressed(KEY_DOWN) || IsKeyDown(KEY_DOWN)) {
        chooseDirection(DOWN);
    } else if (IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT)) {
        chooseDirection(LEFT);
    } else if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT)) {
        chooseDirection(RIGHT);
    }
}