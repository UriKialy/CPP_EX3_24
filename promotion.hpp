#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"
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
        
        
    };
}
// this the promotion class which is a base card for monopoly, year_of_abundance, road_building