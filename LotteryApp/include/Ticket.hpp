#pragma once

#include <array>

struct Ticket
{
    const int id;
    const int prizeAmount;
    const std::array<int, 5> firstRankNumbers;
    const int secondRankNumber;

    Ticket(const int & inputId,
           const int & inputPrizeAmount,
           std::array<int, 5> inputFirstRankNumbers,
           const int & inputSecondRankNumber)
           :
           id(inputId),
           prizeAmount(inputPrizeAmount),
           firstRankNumbers(inputFirstRankNumbers),
           secondRankNumber(inputSecondRankNumber) { }
};