#include "developeCard.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"
#pragma once
using namespace std;
namespace ariel
{
    class knights : public developeCard
    {
        string type;
        vector<resourceCard> price;
    public:
        static int knightsCount;
        knights(string type, vector<resourceCard> price);
        int use_card(player &p);
    };
}