#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "controller_i.hpp"
#include "network.hpp"
#include "snake.hpp"

using namespace Eigen;
    
class Brain : public ControllerI {
    private:
    
    Network net;
    float fitness;
    
    public:
    
    Brain() {}
    Brain(std::vector<int>& dims) : net(Network(dims)), fitness(0) {}
    Brain(Brain& base, float mutationRate) : net(Network(base.net, mutationRate)), fitness(0) {}
    
    void mutate(float mutationRate) { net.mutate(mutationRate); };
    
    int predict(VectorXf& features);
    /**
     * @brief Calculate fitness using gamestate and a weight
     * 
     * @param snake 
     * @param scoreWeight 
     */
    void calcFitness(Snake& snake, float scoreWeight);
    
    VectorXf getFeatures(Snake& snake);
    float getFitness() { return fitness; }
    void setFitness(float fitness) { this->fitness = fitness; }
    
    friend bool operator<(const Brain& a, const Brain& b) {
        return a.fitness < b.fitness;
    }
    
    // inherited controller functions
    direction getNextMove (Snake& snake);
    bool hasNextMove() { return true; }
    void update(Snake& snake) {}
    void newGame(Snake& snake) { fitness = 0; }
};

#endif