#include <iostream>
#include <limits>
#include <fstream>
#include <filesystem>
#include <array>
#include <random>

#include "Circulation.hpp"

namespace fs = std::filesystem;

using namespace std;

random_device dev;
mt19937 randomEngine(dev());

void main_screen();
void circulation_screen();
void search_screen(Circulation<vector> * circulation = nullptr);

int main()
{
    main_screen();
    return 0;
}

void main_screen()
{
    cout << "Select one of these options\n"
         << "1) Start circulation.\n"
         << "2) Search ticket.\n";

    int selection;

    while (true)
    {
        cout << ">> ";
        cin >> selection;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input format. Try again.\n";
        } else if (selection != 1 && selection != 2)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Selection is out of range. Try again.\n";
        } else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (selection) {
                case 1:
                    circulation_screen();
                    break;
                case 2:
                    search_screen();
                    break;
                default:
                    cout << "Unknown error.\n";
                    break;
            }
            break;
        }
    }
}

void circulation_screen()
{
    const fs::path circulations_count_path = "circulations_count.txt";

    uniform_int_distribution<int> firstRankNumberDist(1, 36);
    uniform_int_distribution<int> secondRankNumberDist(1, 5);
    uniform_int_distribution<int> prizeBaseDist(20, 150);

    fstream file;
    int circulationId = 0;

    if (!fs::exists(circulations_count_path))
    {
        circulationId = 1;

        file.open(circulations_count_path, fstream::out | fstream::in | fstream::trunc);
        file << circulationId;
        file.close();
    }
    else
    {
        file.open(circulations_count_path, fstream::out | fstream::in);

        if (file.is_open()) file >> circulationId;
        else cout << "Something went wrong\n";

        circulationId++;
        file.close();

        file.open(circulations_count_path, fstream::out | fstream ::in | fstream::trunc);

        if (file.is_open()) file << circulationId;
        else cout << "Something went wrong\n";

        file.close();
    }

    cout << "You started circulation #" << circulationId << endl;
    cout << "Enter desired number of tickets in circulation\n";

    int countOfTickets = 0;

    while (true)
    {
        cout << ">> ";
        cin >> countOfTickets;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input format. Try again.\n";
        } else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    array<int, 5> firstRankWinNumbers;
    int secondRankWinNumber = secondRankNumberDist(randomEngine);
    int prizeBase = prizeBaseDist(randomEngine);

    for (int i = 0; i < 5; i++)
    {
        int currentNum = firstRankNumberDist(randomEngine);

        bool duplicate = false;
        for (int j = 0; j < i; j++)
        {
            if (firstRankWinNumbers[j] == currentNum)
            {
                duplicate = true;
                break;
            }
        }

        if (!duplicate) firstRankWinNumbers[i] = currentNum;
        else i--;
    }

    TicketNums winNums(firstRankWinNumbers, secondRankWinNumber);
    Circulation<vector> circulation(circulationId, winNums, prizeBase, countOfTickets);

    for (int i = 0; i < countOfTickets; i++)
    {
        array<int, 5> firstRankInputNumbers;
        int secondRankInputNumber = secondRankNumberDist(randomEngine);

        for (int k = 0; k < 5; k++)
        {
            int currentNum = firstRankNumberDist(randomEngine);

            bool duplicate = false;
            for (int j = 0; j < k; j++)
            {
                if (firstRankInputNumbers[j] == currentNum)
                {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) firstRankInputNumbers[k] = currentNum;
            else k--;
        }

        TicketNums inputNums(firstRankInputNumbers, secondRankInputNumber);
        circulation.addTicket(inputNums);
    }

    search_screen(&circulation);
}

void search_screen(Circulation<vector> * circulation)
{
    if (circulation == nullptr)
    {

    }
    else
    {
        cout << "You're executing search in circulation #" << circulation->id << endl;
        cout << "Select type of search:\n"
             << "1) By id\n"
             << "2) By prize amount\n";


        {
            cout << "Enter id of ticket you're searching for(1 - " << circulation->ticketsAmount << ")\n";

            int ticketId;

            while (true) {
                cout << ">> ";
                cin >> ticketId;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input format. Try again.\n";
                } else if (ticketId < 1 || ticketId > circulation->ticketsAmount) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Selection is out of range. Try again.\n";
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
            }

            cout << circulation->getTicket(ticketId).to_string();
        }
    }

}

