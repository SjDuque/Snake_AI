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
            Color color;

            switch (gameBoard.getCell(x, y)) {
                case EMPTY:
                    color = BLACK;
                    break;
                case BODY:
                    color = WHITE;
                    break;
                case APPLE:
                    color = RED;
                    break;
            }
                

            DrawRectangle(x * 10, y * 10, 10, 10, color);
        }
    }
}

void Snakecontroller::update() {
    gameBoard.move();
}