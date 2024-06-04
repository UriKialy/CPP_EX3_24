#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"
#include "developCard.hpp" 
// #include "card.hpp"
using namespace std;
namespace ariel
{
    class promotion : public developCard
    {
        string type;
        vector<resourceCard> price;
    public:
        promotion(string type, vector<card> price);
        virtual int buy_card(player &p)=0;
        int use_card(player &p);
    };
}
// this the promotion class which is a base card for monopoly, year_of_abundance, road_building