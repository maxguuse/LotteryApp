#pragma once

#include "Ticket.hpp"
#include "TicketNums.hpp"

#include <iostream>

#include <memory>
#include <array>
#include <algorithm>
#include <utility>

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
class Circulation
{
    const int id;
    const TicketNums winNums;
    const int prizeBase;

    container<Ticket> tickets;
    int ticketsAmount{};
public:
    Circulation(const int &, TicketNums, const int &);
    const Ticket & addTicket(TicketNums);
    const container<Ticket> & getTickets();
    const Ticket & getTicket(const int & index);
};

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
Circulation<container>::Circulation(const int & circId,
                                    TicketNums circTicketNums,
                                    const int & circPrizeBase)
                                    :
                                    id(circId),
                                    winNums(std::move(circTicketNums)),
                                    prizeBase(circPrizeBase) { }

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
const Ticket & Circulation<container>::addTicket(TicketNums inputTicketNums)
{
    int countOfWinNums = 0;
    std::array<int, 5>::const_iterator itr;

    for (itr = inputTicketNums.firstRank.begin();
         itr != inputTicketNums.firstRank.end();
         itr++)
    {
        const int * foundNumIterator = std::find(
                winNums.firstRank.begin(),
                winNums.firstRank.end(),
                *itr);
        if (foundNumIterator != winNums.firstRank.end()) countOfWinNums++;
    }

    countOfWinNums += countOfWinNums == 5 ? 500 : 0;
    countOfWinNums += inputTicketNums.secondRank == winNums.secondRank ? 2000 : 0;

    int prize = countOfWinNums < 2 ? 0 : prizeBase * countOfWinNums * 10;
    Ticket newTicket(++ticketsAmount, prize, inputTicketNums);
    tickets.push_back(newTicket);
    return *(tickets.end() - 1);
}

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
const container<Ticket> & Circulation<container>::getTickets()
{
    return tickets;
}

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
const Ticket & Circulation<container>::getTicket(const int & ticketId)
{
    return tickets[ticketId - 1];
}