#include "population.hpp"

Population::Population(std::vector<int> dims, int size, float mutationRate) : mutationRate(mutationRate) {
    brains.reserve(size);
    for (int i = 0; i < size; i++) {
        brains.push_back(Brain(dims));
    }
}