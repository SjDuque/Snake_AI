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

void Brain::calcFitness(Snake& snake, float scoreWeight) {
    fitness = scoreWeight * snake.getScore() + (1-scoreWeight) * logf(snake.getMoves()+1);
}

void Brain::move(Snake& snake) {
    VectorXf features = getFeatures(snake);
    
    int dir = predict(features);
    if (dir == 0) {
        snake.turnLeft();
    } else if (dir == 1) {
        snake.turnRight();
    }
    snake.move();
}