#ifndef CIRCULATION_H
#define CIRCULATION_H

#include "CirculationType.h"
#include "Ticket.h"
#include <array>
#include <random>
#include <ctime>

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
class Circulation
{
private:
    int id;
    std::array<int, 5> firstRankWinNumbers;
    int secondRankWinNumber;
    
    int ticketsAmount;
    container<Ticket> tickets;
public:
    Circulation(const int & circulationId);
    
    template <CirculationType circulationType>
    void start();
};

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
Circulation<container>::Circulation(const int &circulationId)
{
    id = circulationId;
}

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
template <CirculationType circulationType>
void Circulation<container>::start () { }

#endif // !CIRCULATION_H