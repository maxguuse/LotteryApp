#pragma once

#include <memory>
#include "Circulation.hpp"

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
class CirculationRepository
{
    int circulationAmount = 0;
    container<Circulation<container>> circulations;
public:
    void addCirculation(Circulation<container>);

    int getCirculationsAmount();

    Circulation<container> getCirculation(int);
    const container<Circulation<container>> & getCirculations();
};

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
int CirculationRepository<container>::getCirculationsAmount() { return circulationAmount; }

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
void CirculationRepository<container>::addCirculation(Circulation<container> circulation) {
    circulationAmount++;
    circulations.push_back(circulation);
}

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
Circulation<container> CirculationRepository<container>::getCirculation(int circulationId)
{
    return circulations[circulationId - 1];
}

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
const container<Circulation<container>> & CirculationRepository<container>::getCirculations()
{
    return circulations;
}