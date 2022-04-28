#ifndef BRAIN_I_HPP
#define BRAIN_I_HPP

#include "controller_i.hpp"
#include "network.hpp"

using namespace Eigen;
    
class BrainI : public ControllerI {
    public:
    
    Brain() {}
    Brain(std::vector<int>& dims);
    Brain(Brain& base, const float& MUTATION_RATE);
    
    void mutate(const float& MUTATION_RATE);
    
    const int predict(VectorXf& FEATURES);
    void calcFitness(GameI& game);
    
    const VectorXf getFeatures(GameI& game);
    const float getFitness();
    void setFitness(const float& FITNESS);
    
    // inherited controller functions
    const int getNextMove(GameI& game);
    void update(GameI& game);
    void reset(GameI& game);
    
    private:
    
    Network net;
    float fitness;
};

#endif