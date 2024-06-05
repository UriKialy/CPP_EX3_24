#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"
#include "promotion.hpp"
// #include "card.hpp"
using namespace std;
namespace ariel
{
    class monopolyCard : public promotion
    {
        string type;
        vector<resourceCard> price;
    public:
        monopolyCard(string type, vector<resourceCard> price); // Added closing parenthesis here
        int use_card(player &p);
    };
}
