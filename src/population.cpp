#include <random>
#include "population.hpp"

Population::Population(std::vector<int>& dims, int size, float mutationRate) : mutationRate(mutationRate) {
    brains.reserve(size);
    for (int i = 0; i < size; i++) {
        brains.push_back(Brain(dims));
    }
}

void Population::runEpoch(Snake& snake, float scoreWeight, unsigned int seed) {
    for (Brain brain : brains) {
        srand(seed);
        snake.newGame();
        
        //set move
        while(snake.getStatus() == ALIVE) {
            brain.move(snake);
        }
        // set fitness
        brain.calcFitness(snake, scoreWeight);
    }
}

