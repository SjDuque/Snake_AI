#include <random>
#include "snake.hpp"
#include "raylib.h"

const bool Snake::alive() {
    return status==ALIVE || status==PAUSED;
}

void Snake::reset() {
    // delete the tail and remove the apple
    while(size() != 0) {
        deleteTail();
    }
    grid[apple.X][apple.Y] = EMPTY;
    
    dir = NORTH;
    score = startScore;
    status = ALIVE;
    moves = 0;
    
    addFront(rows()/2, cols()/2);
    newFruit();
}

void Snake::draw() {
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    
    int screen = (width < height) ? width : height;
    int side = (rows() > cols()) ? rows() : cols();
    
    float scale = ((float) screen) / side;
    
    for (int r = 0; r < rows(); r++) {
        for (int c = 0; c < cols(); c++) {
            Color color = MAGENTA;
            GridVal cell = getCell(r, c);
            
            if (cell == EMPTY) {
                color = BLACK;
            } else if (cell == SNAKE) {
                color = WHITE;
            } else if (cell == APPLE) {
                color = RED;
            }
            
            DrawRectangle(ceil(r * scale), ceil(c * scale), ceil(scale), ceil(scale), color);
        }
    }
}

void Snake::update() {
    Point nextHead = shift(getHead(), dir);
    GridVal nextCell = getCell(nextHead.x, nextHead.y);
    
    // check for collision/death
    if (nextCell == Snake::SNAKE || nextCell == Snake::DEATH) {
        status = Snake::LOSE;
        return;
    }
    
    // increase length with apples
    if (nextCell == APPLE) {
        score += growthRate;
    }
    
    // move forward
    addFront(nextHead.x, nextHead.y);
    moves++;
    
    // remove tail if long enough
    if (size() > score){
        deleteTail();
    }
    
    // check to see if there's a free space on grid
    if (size() == rows() * cols()) {
        status = WIN;
    } else if (nextCell == APPLE) {
        newFruit();
    }
}

const int Snake::getMoves() {
    return moves;
}

const int Snake::getScore() {
    return (score-startScore)/growthRate;
}

const int Snake::rows() {
    return grid.size();
}
const int Snake::cols() {
    return grid[0].size();
}
const int Snake::size() {
    return score;
}

// CONSTRUCTORS AND GAME STARTING
Snake::Snake(ControllerI* input, const int& ROWS=30, const int& COLS=30, const int& START_SCORE=3, const int& GROWTH_RATE=1) {
    startScore = START_SCORE;
    growthRate = GROWTH_RATE;
    
    grid = std::vector<std::vector<GridVal>>(rows, std::vector<GridVal>(cols, EMPTY));
    body = std::list<Point>();
    apple = Point{0, 0};
    
    reset();
}

// movement methods

void Snake::addFront(const int& R, const int& C) {
    body.push_front(Point{R, C});
    grid[R][C] = Snake::SNAKE;
}

void Snake::deleteTail() {
    Point tail = getTail();
    grid[tail.X][tail.Y] = Snake::EMPTY;
    body.pop_back();
}

const Snake::Point Snake::shift(Point& prev, Direction& dir) {
    return Point{prev.X + DIR_MAP_X[dir], prev.Y + DIR_MAP_Y[dir]};
}

void Snake::newFruit() {
    int x, y;
    do {
        x = rand() % rows();
        y = rand() % cols();
    } while (getCell(x, y) != EMPTY);
    
    grid[x][y] = APPLE;
    apple = Point{x, y};
}

const Snake::Point Snake::getApple() {
    return apple;
}

const Snake::GridVal Snake::getRelativeCell(const int& R, const int& C) {  
    Point head = getHead();
    Point add{R, C};
    add = add.rotate(getDirection());
    
    return getCell(head.x + add.x, head.y + add.y);
}
// DIRECTION
void Snake::turnLeft() {
    dir = (direction)((dir + 3) % 4);
}

void Snake::turnRight() {
    dir = (direction)((dir + 1) % 4);
}