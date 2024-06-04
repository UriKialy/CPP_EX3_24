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
        promotion(string type, vector<card> price);
        virtual void buy_card(player &p)=0;
        void use_card(player &p);
    };
}
