#include "promotion.hpp"
#include "player.hpp"
#pragma once
using namespace std;
namespace ariel
{
    class abundanceCard : public promotion
    {
        string type;
        vector<resourceCard> price;
    public:
        abundanceCard(string type, vector<resourceCard> price);
        int use_card(player &p);
    };
}