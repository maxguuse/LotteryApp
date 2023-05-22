#include "Ticket.h"

Ticket::Ticket(const int & id, const int & prizeAmount, std::array<int, 5> firstRankNumbers, const int & secondRankNumber)
{
    this->id = id;
    this->prizeAmount = prizeAmount;
    this->firstRankNumbers = firstRankNumbers;
    this->secondRankNumber = secondRankNumber;
}

const std::string Ticket::to_string()
{
    std::stringstream outputString;

    outputString << id << " | " << prizeAmount << " | ";

    for(const auto & number : firstRankNumbers)
        outputString << number << " ";

    outputString << "| " << secondRankNumber;

    return outputString.str();
}