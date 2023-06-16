#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include "CirculationRepository.hpp"
#include "Circulation.hpp"
#include "TicketNums.hpp"

using namespace std;

mt19937 randomEngine(time(nullptr));
CirculationRepository<vector> repository;

void createCirculation();
void searchTicket();
void searchTicketById(Circulation<vector> & circulation);
void searchTicketByPrize(Circulation<vector> & circulation);

void fillFirstRankNumbers(uniform_int_distribution<int> &distribution, array<int, 5> &firstRankNumbers);
int enterNumber(int, int);
int enterNumber();

int main()
{
    while (true)
    {
        cout << "Select desired option:\n"
             << "1) Create new circulation\n"
             << "2) Search through tickets and circulations\n"
             << "3) Exit\n";

        int selection = enterNumber(1, 3);

        switch (selection)
        {
            case 1:
                createCirculation();
                break;
            case 2:
                searchTicket();
                break;
            case 3:
                return 0;
        }
    }
}

void createCirculation()
{
    int currentCirculationId = repository.getCirculationsAmount() + 1;

    uniform_int_distribution<int> firstRankNumberDist(1, 36);
    uniform_int_distribution<int> secondRankNumberDist(1, 5);
    uniform_int_distribution<int> prizeBaseDist(20, 150);

    array<int, 5> firstRankWinNumbers;
    fillFirstRankNumbers(firstRankNumberDist, firstRankWinNumbers);

    int secondRankWinNumber = secondRankNumberDist(randomEngine);

    TicketNums winNums(firstRankWinNumbers,secondRankWinNumber);

    int prizeBase = prizeBaseDist(randomEngine);

    system("cls");
    cout << "You started circulation #" << currentCirculationId 
         << ", with following win numbers: " << winNums.to_string() << endl;
    cout << "Enter desired number of tickets in circulation\n";

    int countOfTickets = enterNumber();

    if (countOfTickets > 5000)
    {
        cout << "Sorry, but you entered too large amount of tickets, " 
             << "they will not be displayed, but still will be generated and saved\n";
    }

    Circulation<vector> newCirculation(
            currentCirculationId,
            winNums,
            prizeBase,
            countOfTickets
    );

    for (int i = 0; i < countOfTickets; i++)
    {
        array<int, 5> firstRankInputNumbers;
        fillFirstRankNumbers(firstRankNumberDist, firstRankInputNumbers);

        int secondRankInputNumber = secondRankNumberDist(randomEngine);

        TicketNums inputNums(firstRankInputNumbers,secondRankInputNumber);

        Ticket lastTicket = newCirculation.addTicket(inputNums);

        if (countOfTickets <= 5000 && lastTicket.prizeAmount > 0)
        {
            cout << "Ticket #" << lastTicket.id
                 << "\twon: " << lastTicket.prizeAmount
                 << ",\twith numbers: " << lastTicket.ticketNums.to_string()
                 << endl;
        }
    }
    repository.addCirculation(newCirculation);
}
void searchTicket()
{
    if (repository.getCirculations().empty())
    {
        system("cls");
        cout << "No circulations found\n\n";
        return;
    }

    system("cls");
    cout << "To find desired ticket, at first specify circulation number(1 - " 
         << repository.getCirculationsAmount() << ")\n";
    int circulationId = enterNumber(1, repository.getCirculationsAmount());

    Circulation<vector> circulation = repository.getCirculation(circulationId);

    system("cls");
    cout << "Found circulation #" << circulation.id << ", now specify type of search\n"
         << "1) By ticket id\n"
         << "2) By ticket prize\n";

    int typeOfSearch = enterNumber(1, 2);

    switch (typeOfSearch)
    {
        case 1:
            searchTicketById(circulation);
            break;
        case 2:
            searchTicketByPrize(circulation);
            break;
    }
}
void searchTicketById(Circulation<vector> & circulation)
{
    system("cls");
    cout << "To find desired ticket, specify ticket number(1 - " << circulation.ticketsAmount
         << ")\n";
    int ticketId = enterNumber(1, circulation.ticketsAmount);

    Ticket ticket = circulation.getTicket(ticketId);

    system("cls");
    cout << "Found following information:"
         << "\nTicket id: " << ticket.id
         << "\nTicket numbers: " << ticket.ticketNums.to_string()
         << "\nTicket prize amount: " << ticket.prizeAmount
         << "\n\n";
}
void searchTicketByPrize(Circulation<vector> & circulation)
{
    vector<Ticket> allTickets = circulation.getTickets();
    vector<Ticket> desiredTickets;

    system("cls");
    cout << "To find desired ticket, specify prize, that ticket has\n";
    int prize = enterNumber();

    for (const Ticket & ticket : allTickets)
        if (ticket.prizeAmount == prize)
            desiredTickets.push_back(ticket);

    if (desiredTickets.empty())
    {
        system("cls");
        cout << "No tickets found\n\n";
    }
    else
    {
        system("cls");
        cout << "List of found tickets\n";
        for (const Ticket & ticket : desiredTickets)
        {
            cout << "Id: \t" << ticket.id 
                 << "\tTicket numbers: \t" << ticket.ticketNums.to_string() 
                 << "\tPrize amount: \t" << ticket.prizeAmount << endl;
        }
        cout << endl;
    }
}

void fillFirstRankNumbers(uniform_int_distribution<int> & distribution, array<int, 5> & firstRankNumbers)
{
    for (int i = 0; i < 5; i++)
    {
        int currentNum = distribution(randomEngine);

        bool duplicate = false;
        for (int j = 0; j < i; j++)
        {
            if (firstRankNumbers[j] == currentNum)
            {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) firstRankNumbers[i] = currentNum;
        else i--;
    }
}
int enterNumber(int min, int max)
{
    int number;
    while (true)
    {
        cout << ">> ";
        cin >> number;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input format. Try again.\n";
        } else if (number < min || number > max)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Selection is out of range. Try again.\n";
        } else break;
    }

    return number;
}
int enterNumber()
{
    int number;
    while (true)
    {
        cout << ">> ";
        cin >> number;

        if (cin.fail() || number < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input format. Try again.\n";
        } else break;
    }

    return number;
}