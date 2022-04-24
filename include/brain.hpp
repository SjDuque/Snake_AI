#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "network.hpp"
#include "snake.hpp"

using namespace Eigen;

class Brain {
    private:
    
    Network net;
    
    public:
    
    Brain() {}
    Brain(std::vector<int>& dims) : net(Network(dims)) {}
    Brain(Brain& base, float mutation_rate) : net(Network(base.net, mutation_rate)) {}
    
    int predict(VectorXf& features);
};

#endif