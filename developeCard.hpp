#include <iostream>
#include <string>
#include <vector>
#pragma "player.hpp"
#include "resourceCard.hpp"
using namespace std;
namespace ariel
{
    class developCard 
    {
        string type;
        vector<resourceCard> price;
    public:
        developCard(string type, vector<card> price);
        virtual int buy_card(player &p)=0;
        int use_card(player &p);
    };
}
// this the developCard class which is a base card for promotion, victory, knights