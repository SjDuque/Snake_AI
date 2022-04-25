#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <Eigen/Dense>

using namespace Eigen;

/**
 * @brief Fully-Connected Neural Network
 * 
 */
class Network {
    
    private:
    
    std::vector<MatrixXf> W; // weight matrices
    std::vector<VectorXf> b; // bias vectors
    
    public:
    
    /**
     * @brief Construct an empty new Network object
     * 
     */
    Network() {}
    
    /**
     * @brief Construct a new Network object
     * 
     * @param dims Specify the dimensions of each layer.
     * 
     * The length represents the number of layers, with
     * the first representing the input and the last representing
     * the output. 
     */
    Network(std::vector<int>& dims);
    
    /**
     * @brief Construct a copy of base with mutation
     * 
     * @param base Network to mutate
     * @param mutation_rate Determines magnitude of mutation, 
     * similar to learning rate. Use values between 0 and 1.
     */
    Network(Network& base, float mutation_rate);
    
    // ACTIVATION FUNCTIONS

    float relu(float& x);
    MatrixXf relu(MatrixXf& X);
    
    float sigmoid(float& x);
    MatrixXf sigmoid(MatrixXf& X);
    
    // OPERATIONS
    
    /**
     * @brief Perform forward propagation
     * 
     * @param X Shape: (NUM_FEATURES)
     * @return Shape: (NUM_OUTPUTS)
     */
    VectorXf forward(VectorXf& X);
        
    /**
     * @brief Perform forward propagation
     * 
     * @param X Shape: (NUM_EXAMPLES, NUM_FEATURES)
     * @return Shape: (NUM_EXAMPLES, NUM_OUTPUTS)
     */
    MatrixXf forward(MatrixXf& X);
};

#endif