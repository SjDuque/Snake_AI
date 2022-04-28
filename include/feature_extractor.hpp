#ifndef FEATURE_EXTRACTOR_HPP
#define FEATURE_EXTRACTOR_HPP

#include <vector>
#include <functional>

#include "snake.hpp"

static std::vector<float> extractFeatures(Snake& game);
static std::vector<float> extractApplePos(Snake& game);
static std::vector<float> extractPos(Snake& game);
static std::vector<float> extractRelFeatures(Snake& game);
static std::vector<float> extractAbsFeatures(Snake& game);
static std::vector<float> extractVision(Snake& game, const int SIGHT_DIST=3);

static int extractFeaturesSize(ControllerI* input, const int ROWS = 30, const int COLS = 30) {
    Snake snake(input, ROWS, COLS);
    return extractFeatures(snake).size();
}

static std::vector<float> extractFeatures(Snake& game){
    return extractAbsFeatures(game);
}

static std::vector<float> extractAbsFeatures(Snake& game){
    std::vector<float> f;
    std::vector<float> features;
    
    // direction 
    Snake::Direction dir = game.getDirection();
    if (dir == Snake::NORTH) {
        f = {0, 0.5};
    } else if (dir == Snake::EAST) {
        f = {0.5, 0};
    } else if (dir == Snake::SOUTH) {
        f = {0, -0.5};
    } else {
        f = {-0.5, 0};
    }
    features.insert(features.end(), f.begin(), f.end());
    
    // apple
    Snake::Point p = game.getApple();
    f = {((float)p.X)/game.rows(), ((float)p.X)/game.cols()};
    features.insert(features.end(), f.begin(), f.end());
    
    // head
    p = game.getHead();
    f = {((float)p.X)/game.rows(), ((float)p.Y)/game.cols()};
    features.insert(features.end(), f.begin(), f.end());
    
    return features;
}

static std::vector<float> extractRelFeatures(Snake& game){
    std::vector<float> features;
    
    // apple
    std::vector<float> f = extractApplePos(game);
    features.insert(features.end(), f.begin(), f.end());
    
    // position
    f = extractPos(game);
    features.insert(features.end(), f.begin(), f.end());
    
    // vision
    // f = extractVision(game, 1);
    // features.insert(features.end(), f.begin(), f.end());
    
    return features;
}

static std::vector<float> extractApplePos(Snake& game) {
    Point apple = game.getApple();
    Point head = game.getHead();
    
    Point dist = {apple.x - head.x, apple.y - head.y};
    dist = dist.rotate(game.getDirection());
    
    return std::vector<float>{(float)dist.x, (float)dist.y};
}

static std::vector<float> extractPos(Snake& game) {
    Point pos = game.getHead();
    
    float distLeft = pos.x;
    float distRight = game.rows() - pos.x;
    float distUp = pos.y;
    float distDown = game.cols() - pos.y;
    
    if (game.getDirection() == NORTH) {
        return std::vector<float>{distUp, distRight, distDown, distLeft};
    } else if (game.getDirection() == EAST) {
        return std::vector<float>{distRight, distDown, distLeft, distUp};
    } else if (game.getDirection() == SOUTH) {
        return std::vector<float>{distDown, distLeft, distUp, distRight};
    }
    return std::vector<float>{distLeft, distUp, distRight, distDown};
}

static std::vector<float> extractVision(Snake& game, const int SIGHT_DIST) {
    std::vector<float> vision;
    
    for (int i = -SIGHT_DIST; i <= SIGHT_DIST; i++) {
        for (int j = -SIGHT_DIST; j <= SIGHT_DIST; j++) {
            if (i != 0 || j != 0) {
                grid_value relPos = game.getRelativeCell(i, j);
                if (relPos == BODY || relPos == OUT_OF_BOUNDS) {
                    vision.push_back(1);
                } else {
                    vision.push_back(0);
                }
            }
        }
    }
    
    return vision;
}

#endif