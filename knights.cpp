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
    int knights::use_card(player &p)
    {
        int kinghts = 0;
        for (int i = 0; i < 2; i++)
        {
            if (p.get_developmentCard().at(i).get_type() == "knight")
            {
                kinghts++;
            }
        }
        if(knights>2){
            p.add_points(2);
            p.get_developmentCard().erase();
            return 1;
        }
        return 0;
        }
    }
    int knights::buy_card(player &p)
    {
        if (p.get_resourceCard().contains(*this.price))
        {
            p.add_card(*this);
            p.get_resourceCard().erase(*this.price);
            return 1;
        }
        else
        {
            cout << "you don't have enough resources to buy this card" << endl;
            return 0;
        }
    }
}
