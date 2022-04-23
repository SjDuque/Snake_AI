#include <cmath>
#include "network.hpp"

Network::Network(std::vector<int>& dims) {
    for (int i = 0; i < dims.size()-1; i++) {
        W.push_back(MatrixXf::Random(dims[i+1],dims[i]));
        b.push_back(VectorXf::Random(dims[i+1]));
    }
}


float Network::relu(float x){
    return (x > 0) ? x : 0;
}

float Network::sigmoid(float x){
    return 1 / (1 + exp(x));
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

MatrixXf Network::sigmoid(MatrixXf& X) {
    MatrixXf A(X.rows(), X.cols());
    for (int r = 0; r < X.rows(); r++) {
        for (int c = 0; c < X.cols(); c++) {
            A(r, c) = sigmoid(X(r, c));
        }
    }
    return A;
}

MatrixXf Network::forward(MatrixXf& X) {
    MatrixXf A = X.transpose();
    const int L = W.size();
    
    for (int l = 0; l < L-1; l++) {
        MatrixXf Z = W[l] * A;
        Z.colwise() += b[l];
        A = relu(Z);
    }
    
    MatrixXf Z = W[L-1] * A;
    Z.colwise() += b[L-1];
    
    A = sigmoid(Z);
    return A.transpose();
}


