#pragma once

#include <string>

#include "TicketNums.hpp"

struct Ticket
{
    const int id;
    const int prizeAmount;
    const TicketNums ticketNums;

    Ticket(const int & inputId,
           const int & inputPrizeAmount,
           TicketNums inputTicketNums)
           :
           id(inputId),
           prizeAmount(inputPrizeAmount),
           ticketNums(std::move(inputTicketNums)) { }

    std::string to_string()
    {
        using std::to_string;

        return
            to_string(id)
            + " " + to_string(ticketNums.firstRank[0])
            + " " + to_string(ticketNums.firstRank[1])
            + " " + to_string(ticketNums.firstRank[2])
            + " " + to_string(ticketNums.firstRank[3])
            + " " + to_string(ticketNums.firstRank[4])
            + " " + to_string(ticketNums.secondRank)
            + " " + to_string(prizeAmount);
    }
};