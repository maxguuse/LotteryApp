#pragma once

#include <array>

struct TicketNums
{
    const std::array<int, 5> firstRank;
    const int secondRank;

    TicketNums(std::array<int, 5> inputFirstRank,
               const int & inputSecondRank)
               :
               firstRank(inputFirstRank),
               secondRank(inputSecondRank) { }
};