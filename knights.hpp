#include "developeCard.hpp"
#include <iostream>
#include <string>
#include <vector>
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
        string get_type() override;
        static int get_knightsCount();
    };
}