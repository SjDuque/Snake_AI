#include <random>
#include "snake.hpp"

// CONSTRUCTORS AND GAME STARTING
Snake::Snake(int rows, int cols, int startScore, int growthRate) : growthRate(growthRate), startScore(startScore) {
    grid = std::vector<std::vector<grid_value>>(rows, std::vector<grid_value>(cols, EMPTY));
    body = std::list<Point>();
    apple = Point{0, 0};
    
    newGame();
}

void Snake::clear() {
    while(size() != 0) {
        deleteTail();
    }
    grid[apple.x][apple.y] = EMPTY;
}

void Snake::newGame() {
    clear();
    
    dir = NORTH;
    score = startScore;
    status = ALIVE;
    moves = 0;
    
    addFront(rows()/2, cols()/2);
    createFruit();
}

// movement methods

void Snake::addFront(int r, int c) {
    body.push_front(Point{r, c});
    grid[r][c] = BODY;
}

void Snake::deleteTail() {
    Point tail = getTail();
    grid[tail.x][tail.y] = EMPTY;
    body.pop_back();
}

Point Snake::shift(Point prev, direction dir) {
    return Point{prev.x + DIR_MAP_X[dir], prev.y + DIR_MAP_Y[dir]};
}

bool Snake::move() {
    Point nextHead = shift(getHead(), dir);
    grid_value nextCell = getCell(nextHead.x, nextHead.y);
    
    // check for collision/death
    if (nextCell == BODY || nextCell == OUT_OF_BOUNDS) {
        status = DEAD;
        return false;
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
        createFruit();
    }
    return true;
}

void Snake::createFruit() {
    int x, y;
    do {
        x = rand() % rows();
        y = rand() % cols();
    } while (getCell(x, y) != EMPTY);
    
    grid[x][y] = APPLE;
    apple = Point{x, y};
}

Point Snake::getApple() {
    return apple;
}

grid_value Snake::getCell(int x, int y) {
    if (x < 0 || x >= rows() ||
        y < 0 || y >= cols())
        return OUT_OF_BOUNDS;
    return grid[x][y];
}

grid_value Snake::getRelativeCell(int relativeX, int relativeY) {
    if (dir == NORTH) {

    }
}
// DIRECTION
void Snake::turnLeft() {
    dir = (direction)((dir + 3) % 4);
}

void Snake::turnRight() {
    dir = (direction)((dir + 1) % 4);
}