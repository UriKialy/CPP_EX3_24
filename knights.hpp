#include "developeCard.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"
using namespace std;
namespace ariel
{
    class knights : public developCard
    {
        string type;
        vector<resourceCard> price;
    public:
        static int knightsCount;
        knights(string type, vector<card> price);
        virtual int buy_card(player &p)=0;
        int use_card(player &p);
    };
}