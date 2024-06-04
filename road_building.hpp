#include "promotion.hpp"
using namespace std;
namespace ariel
{
    class road_building : public promotion
    {
        string type;
        vector<resourceCard> price;
    public:
        road_building(string type, vector<resourceCard> price);
         int buy_card(player &p);
        int use_card(player &p);
    };
}