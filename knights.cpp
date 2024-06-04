#include "knights.hpp"
using namespace std;
namespace ariel
{
    int knights::knightsCount = 0;
    knights::knights(string type, vector<resourceCard> price) : developCard(type, price)
    {
        if (knightsCount < 4)
        {
            knightsCount++;
            this->type = type;
            this->price = price;
        }
        else
        {
            cout << "you can't have more than 4 knights cards" << endl;
        }
    }
    void knights::use_card(player &p)
    {
        cout << "knights card used" << endl;
    }
    void knights::buy_card(player &p)
    {
        cout << "knights card bought" << endl;
    }
}