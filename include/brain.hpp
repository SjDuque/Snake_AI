#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "network.hpp"
#include "snake.hpp"

using namespace Eigen;

class Brain {
    private:
    
    Network net;
    float fitness;
    
    public:
    
    Brain() {}
    Brain(std::vector<int>& dims) : net(Network(dims)) {}
    Brain(Brain& base, float mutation_rate) : net(Network(base.net, mutation_rate)) {}
    
    int predict(VectorXf& features);
    /**
     * @brief Calculate fitness using gamestate and a weight
     * 
     * @param snake 
     * @param scoreWeight 
     */
    void calcFitness(Snake& snake, float scoreWeight);
    void move(Snake& snake);
    VectorXf getFeatures(Snake& snake);
    float getFitness() { return fitness; }
};

#endif