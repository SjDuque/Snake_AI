#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "snake.hpp"
#include "brain.hpp"

class Population {
    private:
    std::vector<Brain> brains;
    float mutationRate;
    
    public:
    Population() {}
    Population(std::vector<int> dims, int size=1000, float mutationRate=0.01f);
    
    
    
};

#endif