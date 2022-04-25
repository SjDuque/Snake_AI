#include "brain.hpp"
#include "feature_extractor.hpp"

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

void Brain::calcFitness(Snake& snake, float scoreWeight) {
    fitness = scoreWeight * snake.getScore() + (1-scoreWeight) * logf(snake.getMoves()+1);
}

VectorXf Brain::getFeatures(Snake& snake) {
    std::vector<float> features = extractFeatures(snake);
    VectorXf copy(features.size());
    
    for (int i = 0; i < features.size(); i++) {
        copy[i] = features[i];
    }
    
    return copy;
}

direction Brain::getNextMove(Snake& snake) {
    VectorXf features = getFeatures(snake);
    
    int oldDir = snake.getDirection();
    int newDir = predict(features);
    
    if (newDir == 0) { // right
        return (direction)((oldDir + 1) % 4);
    } else if (newDir == 1) { // left
        return (direction)((oldDir + 3) % 4);
    }
    return (direction) oldDir;
}