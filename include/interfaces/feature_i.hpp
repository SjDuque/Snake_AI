#ifndef FEATURE_I_HPP
#define FEATURE_I_HPP

#include <Eigen/Dense>
#include "game_i.hpp"

using namespace Eigen;

class FeatureI {
    public:
    /**
     * @brief Get the Features for brain
     * 
     * @param game 
     * @return VectorXf 
     */
    virtual VectorXf getFeatures(GameI& game) = 0;
    virtual int size() = 0;
};

#endif