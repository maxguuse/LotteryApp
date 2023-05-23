#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <sstream>
#include <array>

class Ticket
{
private:
    int id;
    int prizeAmount;
    std::array<int, 5> firstRankNumbers;
    int secondRankNumber;    
public:
    Ticket(const int & id, const int & prizeAmount, std::array<int, 5> firstRankNumbers, const int & secondRankNumber);
    std::string to_string();
};

#endif // !TICKET_H