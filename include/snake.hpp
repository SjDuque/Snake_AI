#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <list>
#include <vector>
#include <cstdlib>

const std::vector<int> DIR_MAP_X = {0, 0, -1, 1};
const std::vector<int> DIR_MAP_Y = {-1, 1, 0, 0};

enum grid_value {
    EMPTY,
    BODY,
    APPLE,
    OUT_OF_BOUNDS
};

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum game_status {
    ALIVE,
    DEAD,
    PAUSED,
    WIN
};

class Snake {
    
    private:
        /**
         * @brief stores x and y coords
         * 
         */
        struct Point {
            int x, y;
        };
        
        Point apple;
        std::list<Point> body;
        std::vector<std::vector<grid_value>> grid;
        
        int score;
        int startScore;
        int growthRate;
        
        direction dir;
        game_status status;

        void addFront(int x, int y);
        void deleteTail();
        void clear();
        Point shift(Point prev, direction dir);
        
    public:
        Snake(int rows=30, int cols=30, int startScore = 3, int growthRate = 1);
        
        // game logic
        
        /**
         * @brief Generates a new fruit at a random empty location.
         * 
         */
        void createFruit();
        
        /**
         * @brief Restart the game instance
         * 
         */
        void newGame();
        /**
         * @brief Moves snake forward
         * 
         * @return true if no collision
         * @return false otherwise
         */
        bool move();
        
        // get methods
        Point getHead();
        Point getTail();
        grid_value getCell(int x, int y);
        direction getDirection() { return this->dir; }
        game_status getStatus() { return this->status; }
        
        int rows() { return grid.size(); }
        int cols() { return grid[0].size(); }
        int size() { return body.size(); }
        
        // set methods
        void setDirection(direction dir) { this->dir = dir; }
};

#endif