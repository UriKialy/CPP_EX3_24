#include <iostream>
#include <string>
#include <vector>
#include "promotion.hpp"
#pragma once
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
        void display();
    };
}
