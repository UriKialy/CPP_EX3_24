#include "knights.hpp"
using namespace std;
namespace ariel
{
    int knights::knightsCount = 0;
    knights::knights(string type, vector<resourceCard> price) : developeCard(type, price)
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
    int knights::get_knightsCount(){
        return knightsCount;
    }
    string knights::get_type()
    {
        return type;
    }
}
   

