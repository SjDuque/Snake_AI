#include "featureselector.hpp"

#include <cmath>

static std::vector<std::vector<float>> extractFeatures(Snake game, std::vector<std::function<std::vector<float>(Snake)>> featureList) {
    std::vector<std::vector<float>> features = std::vector<std::vector<float>>();

    for (int i = 0; i < featureList.size(); i++) {
        features.push_back(featureList[i](game));
    }
}

static std::vector<float> extractApplePos(Snake game) {
    Point apple = game.getApple();
    return std::vector<float>{(float)apple.x, (float)apple.y};
}

static std::vector<float> extractVision(Snake game) {
    const int SIGHT_DIST = 3;
    int TILES_SEEN = ((SIGHT_DIST * (SIGHT_DIST + 1)) / 2) * 4;
    
    Point head = game.getHead();
    direction dir = game.getDirection();
    
    std::vector<float> vision = std::vector<float>(TILES_SEEN);

    for (int i = -SIGHT_DIST; i >= SIGHT_DIST; i++) {
        for (int j = -SIGHT_DIST; j >= SIGHT_DIST; j++) {
            if (abs(i) + abs(j) <= SIGHT_DIST) {
                grid_value relativePos = game.getRelativeCell(i, j);
                vision.push_back((float)relativePos);
            }
        }
    }
}