#pragma once

#include "Ticket.hpp"
#include "TicketNums.hpp"

#include <iostream>
#include <memory>
#include <filesystem>
#include <array>

namespace fs = std::filesystem;

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
class Circulation
{
    const fs::path circulation_folder = "circulations";

    const int id;
    const TicketNums winNums;
    const int prizeBase;
    const int ticketsAmount;

    fs::path current_circulation_path;
    std::fstream file;

    container<Ticket> tickets;
    int maxTicketsId = 0;

    void writeTicketToFile(Ticket & ticket);
public:
    Circulation(const int &, TicketNums, const int &, const int &);
    ~Circulation();

    const Ticket & addTicket(TicketNums);
    const container<Ticket> & getTickets();
    const Ticket & getTicket(const int & ticketId);
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
                                    ticketsAmount(circTicketsAmount)
                                    {
                                        using std::fstream;

                                        current_circulation_path = circulation_folder.string() + "/" + std::to_string(id) + ".txt";

                                        if (!fs::exists(current_circulation_path))
                                        {
                                            file.open(current_circulation_path, fstream::trunc | fstream::in | fstream::out);
                                            file << ticketsAmount << "\n";
                                            file.close();
                                        }

                                        file.open(current_circulation_path, fstream::app);
                                    }

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
Circulation<container>::~Circulation()
{
    file.close();
}

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
    writeTicketToFile(newTicket);
    tickets.push_back(newTicket);
    return *(tickets.end() - 1);
}

template <template <typename Y, typename Allocator = std::allocator<Y>> class container>
void Circulation<container>::writeTicketToFile(Ticket &ticket)
{
    file << ticket.to_string() << "\n";
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