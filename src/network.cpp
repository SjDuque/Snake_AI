#include <cmath>
#include "network.hpp"
#include <iostream>

// CONSTRUCTORS

Network::Network(std::vector<int>& dims) {
    for (int i = 0; i < dims.size()-1; i++) {
        // he initialization
        const float HE = (1.0f / sqrtf(dims[i+1]/2.0f));
        W.push_back(MatrixXf::Random(dims[i+1],dims[i]) * HE);
        b.push_back(VectorXf::Zero(dims[i+1]));
    }
}

Network::Network(Network& base, float mutation_rate) {
    for (int i = 0; i < base.W.size(); i++) {
        // grab the base values
        MatrixXf W_i = base.W[i].eval();
        MatrixXf b_i = base.b[i].eval();
        
        // find the mutation weights
        const float HE =  (mutation_rate / sqrtf(W_i.rows()/2.0f));
        MatrixXf randW_i = MatrixXf::Random(W_i.rows(), W_i.cols()) * HE;
        MatrixXf randb_i = VectorXf::Random(b_i.rows()) * HE;
        
        //
        W.push_back(W_i+randW_i);
        b.push_back(b_i+randb_i);
    }
}

// ACTIVATION FUNCTIONS

float Network::relu(float x){
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

float Network::sigmoid(float x){
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
    
    for (int l = 0; l < L-1; l++) {
        MatrixXf Z = W[l] * A;
        Z.colwise() += b[l];
        A = relu(Z).eval();
    }
    
    MatrixXf Z = W[L-1] * A;
    Z.colwise() += b[L-1];
    A = sigmoid(Z).eval();
    
    return A;
}

MatrixXf Network::forward(MatrixXf& X) {
    const int L = W.size(); // num layers
    
    MatrixXf A = X.transpose().eval();
    
    for (int l = 0; l < L-1; l++) {
        MatrixXf Z = W[l] * A;
        Z.colwise() += b[l];
        A = relu(Z).eval();
    }
    
    MatrixXf Z = W[L-1] * A;
    Z.colwise() += b[L-1];
    A = sigmoid(Z).eval();
    
    A.transposeInPlace();
    return A;
}