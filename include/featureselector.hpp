#ifndef FEATURESELECTOR
#define FEATURESELECTOR

#include <vector>
#include <functional>

#include "snake.hpp"

static std::vector<std::vector<float>> extractFeatures(Snake game, std::vector< std::function<std::vector<float>(Snake)>> featureList);
static std::vector<float> extractApplePos(Snake game);
static std::vector<float> extractVision(Snake game); //UNTESTED

#endif