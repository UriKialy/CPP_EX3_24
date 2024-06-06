#include <iostream>
#include <string>
#include <vector>
#include "developeCard.hpp" 
// #include "card.hpp"
using namespace std;
namespace ariel
{
    class promotion : public developeCard
    {
        string type;
        vector<resourceCard> price;
    public:
        promotion(string type, vector<resourceCard> price);
        virtual int use_card(player &p) = 0;
        
    };
}
// this the promotion class which is a base card for monopoly, year_of_abundance, road_building