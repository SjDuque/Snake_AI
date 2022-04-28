#include <cmath>
#include "network.hpp"

// CONSTRUCTORS

Network::Network(std::vector<int>& dims) {
    for (int i = 0; i < dims.size()-1; i++) {
        // he initialization
        const float HE = (1.0f / sqrtf(dims[i+1]/2.0f));
        W.push_back(MatrixXf::Random(dims[i+1],dims[i]) * HE);
        b.push_back(VectorXf::Zero(dims[i+1]));
    }
}

Network::Network(Network& base, float mutationRate) {
    for (int i = 0; i < base.W.size(); i++) {
        // grab the base values
        W.push_back(base.W[i]);
        b.push_back(base.b[i]);
    }
    mutate(mutationRate);
}

void Network::mutate(float mutationRate) {
    for (int i = 0; i < W.size(); i++) {
        // find the mutation weights
        const float HE =  (mutationRate / sqrtf(W[i].rows()/2.0f));
        MatrixXf randW_i = MatrixXf::Random(W[i].rows(), W[i].cols()) * HE;
        MatrixXf randb_i = VectorXf::Random(W[i].rows()) * HE;
        
        randW_i += W[i];
        randb_i += b[i];
        
        W[i] = randW_i;
        b[i] = randb_i;
    }
}

// ACTIVATION FUNCTIONS

float Network::relu(float& x){
    return (x > 0) ? x : 0;
}

MatrixXf Network::relu(MatrixXf& X) {
    MatrixXf A(X.rows(), X.cols());
    for (int r = 0; r < X.rows(); r++) {
        for (int c = 0; c < X.cols(); c++) {
            A(r, c) = relu(X(r, c));
        }
    }
    return A;
}

float Network::sigmoid(float& x){
    return 1 / (1 + expf(-x));
}

MatrixXf Network::sigmoid(MatrixXf& X) {
    MatrixXf A(X.rows(), X.cols());
    for (int r = 0; r < X.rows(); r++) {
        for (int c = 0; c < X.cols(); c++) {
            A(r, c) = sigmoid(X(r, c));
        }
    }
    return A;
}

// OPERATIONS

VectorXf Network::forward(VectorXf& X) {
    const int L = W.size(); // num layers
    
    VectorXf A = X.eval();
    MatrixXf Z;
    
    for (int l = 0; l < L-1; l++) {
        Z = W[l] * A;
        Z.colwise() += b[l];
        A = relu(Z).eval();
    }
    
    Z = W[L-1] * A;
    Z.colwise() += b[L-1];
    A = sigmoid(Z).eval();
    
    return A;
}

MatrixXf Network::forward(MatrixXf& X) {
    const int L = W.size(); // num layers
    
    MatrixXf Z, A = X.transpose().eval();
    
    for (int l = 0; l < L-1; l++) {
        Z = W[l] * A;
        Z.colwise() += b[l];
        A = relu(Z).eval();
    }
    
    Z = W[L-1] * A;
    Z.colwise() += b[L-1];
    A = sigmoid(Z).eval();
    
    A.transposeInPlace();
    return A;
}