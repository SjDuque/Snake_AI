#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "brain.hpp"

class Population : public ControllerI {
    private:
    std::vector<Brain> brains;
    Brain best;
    float mutationRate;
    
    public:
    Population() {}
    Population(std::vector<int>& dims, int size=1000, float mutationRate=0.1f);
    
    void runEpoch(Snake& snake, float scoreWeight=0.99, const int MAX_MOVES = 100);
    std::vector<Brain> newBrains();
    
    // ControllerI
    
    direction getNextMove(Snake& snake);
    bool hasNextMove() { return true; }
    void update(Snake& snake) {}
    void newGame(Snake& snake);
};

#endif