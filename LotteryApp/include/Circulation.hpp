#pragma once

#include "Ticket.hpp"
#include "TicketNums.hpp"

#include <iostream>
#include <algorithm>
#include <memory>
#include <array>

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
class Circulation
{
    container<Ticket> tickets;
    int maxTicketsId = 0;
public:
    Circulation(const int &, TicketNums, const int &, const int &);

    const int id;
    const TicketNums winNums;
    const int prizeBase;
    const int ticketsAmount;

    const Ticket & addTicket(TicketNums);
    const container<Ticket> & getTickets();
    Ticket & getTicket(const int & ticketId);
};

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
Circulation<container>::Circulation(const int & circId,
                                    TicketNums circTicketNums,
                                    const int & circPrizeBase,
                                    const int & circTicketsAmount)
                                    :
                                    id(circId),
                                    winNums(std::move(circTicketNums)),
                                    prizeBase(circPrizeBase),
                                    ticketsAmount(circTicketsAmount) { }

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
    Ticket newTicket(++maxTicketsId, prize, inputTicketNums);
    tickets.push_back(newTicket);
    return *(tickets.end() - 1);
}

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
const container<Ticket> & Circulation<container>::getTickets()
{
    return tickets;
}

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
Ticket & Circulation<container>::getTicket(const int & ticketId)
{
    return tickets[ticketId - 1];
}