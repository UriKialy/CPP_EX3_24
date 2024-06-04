#include <iostream>
#include <string>
#include <vector>
#pragma "player.hpp"
#include "card.hpp"
using namespace std;
namespace ariel
{
    class developCard : public card
    {
        string type;
        vector<resourceCard> price;
    public:
        developCard(string type, vector<card> price);
        virtual void buy_card(player &p)=0;
        void use_card(player &p);
    };
}
// this the developCard class which is a base card for promotion, victory, knights