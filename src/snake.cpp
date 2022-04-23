#include "snake.hpp"

using namespace std;
    
Snake::Snake() {    }

Snake::Snake(int width, int height) {
    grid = vector<vector<grid_value>>(width, std::vector<grid_value>(height, EMPTY));
    body = list<Point>();
    int midX = width/2;
    int midY = height/2;
    addFront(midX, midY);
    dir = UP;
    length = 3;
    status = ACTIVE;

    createFruit();
}

Snake::Point Snake::getHead() {
    return body.front();
}

Snake::Point Snake::getTail() {
    return body.back();
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

/**
 * @brief Moves snake and checks collision. Sets collision flag if collision occurs.
 * 
 * @param dir 
 * @return false if collision occurs.
 */
void Snake::move() {
    Point nextHead = shiftDirection(getHead(), dir);
    grid_value destGrid = getCell(nextHead.x, nextHead.y);
    switch (destGrid) {
        case EMPTY:
            break;
        case BODY:
            if (getTail().x != nextHead.x || getTail().y != nextHead.y)
                status = COLLIDED;
            break;
        case APPLE:
            length += GROWTH;
            if (length != grid.size() * grid[0].size())
                createFruit();
            break;
        case OUT_OF_BOUNDS:
            status = COLLIDED;
            return;
        default:
            break;
    }
    shift();
    if (length == grid.size() * grid[0].size())
        status = WIN;
}

grid_value Snake::getCell(int x, int y) {
    if (x < 0 || x >= grid.size() ||
        y < 0 || y >= grid[0].size())
        return OUT_OF_BOUNDS;
    return grid[x][y];
}

/**
 * @brief Moves the body of the snake, growing if possible.
 * 
 * @param dir 
 */
void Snake::shift() {
    Point nextHead = shiftDirection(getHead(), dir);
    if (body.size() + 1 > length)
        deleteTail();
    addFront(nextHead.x, nextHead.y);
}

Snake::Point Snake::shiftDirection(Point prev, direction dir) {
    int deltaX[] = {0, 0, -1, 1};
    int deltaY[] = {-1, 1, 0, 0};
    return Point{prev.x + deltaX[dir], prev.y + deltaY[dir]};
}

/**
 * @brief Generates a new fruit on a random empty location.
 * 
 */
void Snake::createFruit() {
    while (true) {
        int x = rand() % grid.size();
        int y = rand() % grid[0].size();
        if (getCell(x, y) == EMPTY) {
            grid[x][y] = APPLE;
            return;
        }
    }
}