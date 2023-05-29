#pragma once

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
};