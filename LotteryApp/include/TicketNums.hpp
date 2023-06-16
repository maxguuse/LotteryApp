#pragma once

#include <array>
#include <string>
#include <sstream>

struct TicketNums
{
    const std::array<int, 5> firstRank;
    const int secondRank;

    TicketNums(std::array<int, 5> inputFirstRank,
               const int & inputSecondRank)
               :
               firstRank(inputFirstRank),
               secondRank(inputSecondRank) { }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << firstRank[0] << " "
           << firstRank[1] << " "
           << firstRank[2] << " "
           << firstRank[3] << " "
           << firstRank[4] << " | "
           << secondRank;

        return ss.str();
    }
};