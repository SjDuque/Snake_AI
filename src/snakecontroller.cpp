#include "snakecontroller.hpp"
#include "cmath"

Snakecontroller::Snakecontroller(int rows, int cols, int startScore, int growthRate) {
    gameBoard = Snake(rows, cols, startScore, growthRate);
    paused = false;
}

void Snakecontroller::newGame() {
    gameBoard.newGame();
}

void Snakecontroller::draw() {
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    
    int screen = (width < height) ? width : height;
    int side = (rows() > cols()) ? rows() : cols();
    
    float scale = ((float) screen) / side;
    
    for (int r = 0; r < rows(); r++) {
        for (int c = 0; c < cols(); c++) {
            Color color = MAGENTA;
            grid_value cell = gameBoard.getCell(r, c);
            
            if (cell == EMPTY) {
                color = BLACK;
            } else if (cell == BODY) {
                color = WHITE;
            } else if (cell == APPLE) {
                color = RED;
            }
            
            DrawRectangle(round(r * scale), round(c * scale), round(scale), round(scale), color);
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