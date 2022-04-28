#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <list>
#include <vector>

#include <controller_i.hpp>

class Snake : public GameI {
    public:
    
    /**
     * @brief Stores x and y coords
     * 
     */
    struct Point {
        int X, Y;
    };
    
    /**
     * @brief Snake game grid values
     * 
     */
    const enum GridVal {
        EMPTY,
        SNAKE,
        APPLE,
        DEATH
    };
    
    /**
     * @brief Directions for keeping track of turns
     * 
     */
    const enum Direction {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };
    
    /**
     * @brief Status of the game
     * 
     */
    const enum GameStatus{
        ALIVE,
        PAUSED,
        WIN,
        LOSE
    };
    
    /**
     * @brief Construct a new Snake object
     * 
     * @param input
     * @param ROWS
     * @param COLS 
     * @param START_SCORE 
     * @param GROWTH_RATE 
     */
    Snake(ControllerI* input, const int& ROWS=30, const int& COLS=30, const int& START_SCORE=3, const int& GROWTH_RATE=1);
    
    /**
     * @brief Generates a new fruit at a random empty location.
     * 
     */
    void newFruit();
    
    // get methods
    const Point getApple();
    const Point getHead();
    const Point getTail();
    const Direction getDirection();
    const GameStatus getStatus();
    const GridVal getRelativeCell(const int& REL_R, const int& REL_C);
    
    // size get methods
    const int getMoves();
    const int getScore();
    const int rows();
    const int cols();
    const int size();
    
    const bool isValid(const int& R, const int& C);
    const GridVal getCell(const int& R, const int& C);
    void setDirection(Direction dir);
    
    const bool alive();
    void reset();
    void update();
    void draw();
    
    private:
    
    const std::vector<int> DIR_MAP_X = {0, 1, 0, -1};
    const std::vector<int> DIR_MAP_Y = {-1, 0, 1, 0};
    
    Point apple;
    std::list<Point> body;
    std::vector<std::vector<GridVal>> grid;
    
    
    int score;
    int moves;
    int startScore;
    int growthRate;
    
    Direction dir;
    GameStatus status;

    void addFront(const int& R, const int& C);
    void deleteTail();
    const Point shift(Point& prev, Direction& dir);
};

#endif