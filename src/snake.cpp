#include "snake.hpp"

using namespace std;
    
Snake::Snake(int width, int height) {
    grid = vector<vector<int>>(width, std::vector<int>(height));
    body = list<Point>();
    int midX = width/2;
    int midY = height/2;
    body.push_back(Point{midX, midY});
    body.push_back(Point{midX, midY+1});
    body.push_back(Point{midX, midY+2});
    grid[midX][midY] = BODY;
    grid[midX][midY+1] = BODY;
    grid[midX][midY+2] = BODY;
}

Snake::Point Snake::getHead() {
    return body.front();
}

Snake::Point Snake::getTail() {
    return body.back();
}
