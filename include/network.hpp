#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <Eigen/Dense>

using namespace Eigen;

class Network {
    
    private:
    
    std::vector<MatrixXf> W; // weight matrices
    std::vector<VectorXf> b; // bias vectors
    
    public:
    
    Network(std::vector<int>& dims);
    float relu(float x);
    float sigmoid(float x);
    MatrixXf relu(MatrixXf& X);
    MatrixXf sigmoid(MatrixXf& X);
    MatrixXf forward(MatrixXf& X);
};

#endif