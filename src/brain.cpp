#include "brain.hpp"
    
int Brain::predict(VectorXf& features) {
    VectorXf outputs = net.forward(features);
    
    int max_i = 0;
    
    for (int i = 1; i < outputs.rows(); i++){
        if (outputs[i] > outputs[max_i]) {
            max_i = i;
        }
    }
    
    return max_i;
}