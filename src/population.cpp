#include <random>
#include <iostream>
#include <algorithm>
#include "population.hpp"

Population::Population(std::vector<int>& dims, int size, float mutationRate) : mutationRate(mutationRate) {
    for (int i = 0; i < size; i++) {
        brains.push_back(Brain(dims));
    }
}

void Population::runEpoch(Snake& snake, float scoreWeight, const int MAX_MOVES, const int NUM_GAMES) {
    for (int i = 0; i < brains.size(); i++) {
        brains[i].setFitness(0);
        for (int g = 0; g < NUM_GAMES; g++) {
            snake.newGame();
            //set move
            while(snake.getStatus() == ALIVE && snake.getMoves() < MAX_MOVES) {
                snake.setDirection(brains[i].getNextMove(snake));
                snake.move();
            }
            // set fitness
            brains[i].calcFitness(snake, scoreWeight);
        }
    }
    snake.newGame();
    
    std::sort(brains.begin(), brains.end());
    std::cout << brains[0].getFitness() << " " << brains[brains.size()-1].getFitness() << std::endl;
}

void Population::newBrains() {
    Brain best = brains[brains.size()-1];
    for (int i = brains.size()/2; i < brains.size(); i++) {
        brains[i-brains.size()/2] = Brain(brains[i], mutationRate);
        brains[i] = Brain(brains[i], mutationRate);
    }
    brains[brains.size()-1] = best;
}

direction Population::getNextMove (Snake& snake) {
    return brains[brains.size()-1].getNextMove(snake);
}

void Population::newGame(Snake& snake) {
    runEpoch(snake);
    
    int maxFit_i = 0;
    
    for (int i = 1; i < brains.size(); i++) {
        if (brains[maxFit_i].getFitness() < brains[i].getFitness()) {
            maxFit_i = i;
        }
    }
    newBrains();
}