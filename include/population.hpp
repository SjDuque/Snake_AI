#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "brain.hpp"

class Population {
    private:
    std::vector<Brain> brains;
    float mutationRate;
    
    public:
    Population() {}
    Population(std::vector<int>& dims, int size=1000, float mutationRate=0.01f);
    
    void runEpoch(Snake& snake, float scoreWeight=0.99, unsigned int seed = 0);
    std::vector<Brain> newBrains();
};

#endif