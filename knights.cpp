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
    int knights::use_card(player &p)
    {
        int Nkinghts = 0;
        for (int i = 0; i < 2; i++)
        {
            if (p.get_developmentCard().at(i).get_type() == "knight")
            {
                Nkinghts++;
            }
        }
        if(Nkinghts>2){
            p.add_points(2);
            for (int i = 0; i < 2; i++){
                if (p.get_developmentCard().at(i).get_type() == "knight"){
                    p.get_developmentCard().erase(p.get_developmentCard().at(i));
                    knightsCount--;
                }
            }
            return 1;
        }
        return 0;
        }
    }
   

