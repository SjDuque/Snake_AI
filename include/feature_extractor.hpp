#ifndef FEATURE_EXTRACTOR_HPP
#define FEATURE_EXTRACTOR_HPP

#include <vector>
#include <functional>

#include "snake.hpp"

static std::vector<float> extractFeatures(Snake& game);
static std::vector<float> extractApplePos(Snake& game);
static std::vector<float> extractVision(Snake& game, const int SIGHT_DIST=3);

static std::vector<float> extractFeatures(Snake& game){
    std::vector<float> features;
    
    // apple
    std::vector<float> f = extractApplePos(game);
    features.insert(features.end(), f.begin(), f.end());
    
    // vision
    f = extractVision(game, 3);
    features.insert(features.end(), f.begin(), f.end());
    
    return features;
}

static std::vector<float> extractApplePos(Snake& game) {
    Point apple = game.getApple();
    Point head = game.getHead();
    
    Point dist = {apple.x - head.x, apple.y - head.y};
    dist.rotate(game.getDirection());
    
    return std::vector<float>{(float)dist.x, (float)dist.y};
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