#include "road_building.hpp"
using namespace std;
namespace ariel
{
    road_building::road_building(string type, vector<resourceCard> price) : promotion(type, price)
    {    }
    int road_building::buy_card(player &p)
    {
        p.add_card(*this);
    }
    int road_building::use_card(player &p)
    {
        p.use_card(*this);
    }
    
}