#include <iostream>
#include <random>
#include <set>

using namespace std;

class Ticket
{
    const int winNumsCount = 5;
    set<int> winNums;
public:
    Ticket()
    {
        srand(time(NULL));

        while (winNums.size() < winNumsCount)
        {
            int current = rand() % 36 + 1;
            winNums.insert(current);
        }
    }

    void displayWinNums()
    {
        set<int>::iterator itr;

        for (itr = winNums.begin(); itr != winNums.end(); itr++)
            cout << *itr << " " << endl; 
        
        cout << endl;
    }

    // Returns read-only set of win nums, so user can't change these nums
    set<int> getWinNums()
    {
        return winNums;
    }
};