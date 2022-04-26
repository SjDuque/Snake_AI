#include <random>
#include "population.hpp"

Population::Population(std::vector<int>& dims, int size, float mutationRate) : mutationRate(mutationRate) {
    for (int i = 0; i < size; i++) {
        brains.push_back(Brain(dims));
    }
}

void Population::runEpoch(Snake& snake, float scoreWeight, const int MAX_MOVES) {
    for (int i = 0; i < brains.size(); i++) {
        snake.newGame();
        //set move
        while(snake.getStatus() == ALIVE && snake.getMoves() < MAX_MOVES) {
            snake.setDirection(brains[i].getNextMove(snake));
            snake.move();
        }
        // set fitness
        brains[i].calcFitness(snake, scoreWeight);
    }
    snake.newGame();
}

std::vector<Brain> Population::newBrains() {
    float totalFitness = 0;
    for (int i = 0; i < brains.size(); i++) {
        totalFitness += brains[i].getFitness();
    }
    
    std::vector<Brain> newBrains;
    
    while (newBrains.size() < brains.size()) {
        float runningSum = 0;
        float fitValue = ((float) rand() / RAND_MAX) * totalFitness;
        
        for (int j = 0; j < brains.size(); j++) {
            runningSum += brains[j].getFitness();
            if (runningSum >= fitValue) {
                newBrains.push_back(Brain(brains[j], 0));
                newBrains.push_back(Brain(brains[j], mutationRate));
                break;
            }
        }
    }
    
    return newBrains;
}

direction Population::getNextMove (Snake& snake) {
    return brains[0].getNextMove(snake);
    // return best.getNextMove(snake);
}

void Population::newGame(Snake& snake) {
    runEpoch(snake, 0.99f, 100);
    
    int maxFit_i = 0;
    
    for (int i = 1; i < brains.size(); i++) {
        if (brains[maxFit_i].getFitness() < brains[i].getFitness()) {
            maxFit_i = i;
        }
    }
    
    best = brains[maxFit_i];
    brains = newBrains();
}