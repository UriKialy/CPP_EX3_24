#include "promotion.hpp"
#pragma once
using namespace std;
namespace ariel
{
    class abundanceCard : public promotion
    {
        string type;
        vector<resourceCard> price;
    public:
        abundanceCard(string type, vector<resourceCard> price) ;
        void display() override;
    };
}