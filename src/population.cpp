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
            snake.setDirection(brain.getNextMove(snake));
        }
        // set fitness
        brain.calcFitness(snake, scoreWeight);
    }
}

std::vector<Brain> Population::newBrains() {
    float totalFitness = 0;
    for (Brain brain : brains) {
        totalFitness += brain.getFitness();
    }
    
    std::vector<Brain> newBrains;
    newBrains.reserve(brains.size());
    
    for (int i = 0; i < brains.size(); i++) {
        float runningSum = 0;
        float fitValue = ((float) rand() / RAND_MAX) * totalFitness;
        for (Brain brain : brains) {
            runningSum += brain.getFitness();
            if (runningSum >= fitValue) {
                newBrains.push_back(brain);
                break;
            }
        }
    }
    
    return newBrains;
}

