#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <list>
#include <vector>
class Snake {
    
    private:
    
    /**
     * @brief stores x and y coords
     * 
     */
    struct Point {
        int x, y;
    };
    
    enum grid_values {
        EMPTY,
        BODY,
        APPLE
    };
    
    enum directions {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    
    std::list<Point> body;
    std::vector<vector<int>> grid;
    directions dir;
    
    public:
    Snake(int width, int height);
    
    Point getHead();
    Point getTail();
    
    
    
};

#endif