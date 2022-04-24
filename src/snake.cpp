#include "snake.hpp"

using namespace std;

Snake::Snake(int width, int height, int startLength, int growthRate) : growthRate(growthRate), startLength(startLength) {
    grid = vector<vector<grid_value>>(width, std::vector<grid_value>(height, EMPTY));
    body = list<Point>();
    
    newGame();
}

void Snake::clear() {
    while(size() != 0) {
        deleteTail();
    }
}

void Snake::newGame() {
    clear();
    
    dir = UP;
    length = startLength;
    status = ALIVE;
    
    createFruit();
}

void Snake::addFront(int x, int y) {
    body.push_front(Point{x, y});
    grid[x][y] = BODY;
}

void Snake::deleteTail() {
    Point tail = getTail();
    grid[tail.x][tail.y] = EMPTY;
    body.pop_back();
}

bool Snake::move() {
    Point nextHead = shift(getHead(), dir);
    grid_value destGrid = getCell(nextHead.x, nextHead.y);
    
    // check for collision/death
    // then check for apple
    if (destGrid == BODY || destGrid == OUT_OF_BOUNDS) {
        status = DEAD;
        return false;
    } else if (destGrid == APPLE) {
        length += growthRate;
    }
    
    // it's safe to add the head
    addFront(nextHead.x, nextHead.y);
    
    // remove tail if snake is long enough
    if (body.size() >= length){
        deleteTail();
    }
    
    // check to see if you can add another apple
    if (length >= grid.size() * grid[0].size()) {
        status = WIN;
    } else {
        createFruit();
    }
        
    return true;
}

Snake::Point Snake::shift(Point prev, direction dir) {
    return Point{prev.x + DIR_MAP_X[dir], prev.y + DIR_MAP_Y[dir]};
}

/**
 * @brief Generates a new fruit at a random empty location.
 * 
 */
void Snake::createFruit() {
    int x, y;
    do {
        x = rand() % grid.size();
        y = rand() % grid[0].size();
    } while (getCell(x, y) != EMPTY);
    grid[x][y] = APPLE;
}


Snake::Point Snake::getHead() {
    return body.front();
}

Snake::Point Snake::getTail() {
    return body.back();
}

grid_value Snake::getCell(int x, int y) {
    if (x < 0 || x >= grid.size() ||
        y < 0 || y >= grid[0].size())
        return OUT_OF_BOUNDS;
    return grid[x][y];
}
