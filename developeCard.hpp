#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "resourceCard.hpp"
using namespace std;
namespace ariel
{
    class developeCard
    {
    protected:
        string type;
        vector<resourceCard> price;

    public:
        developeCard(string type, vector<resourceCard> price);
        explicit developeCard() = default;
        virtual string get_type();
        virtual vector<resourceCard> get_price();
        virtual void display()=0;
        virtual ~developeCard() = default;
    };
}
// this the developCard class which is a base card for promotion, victory, knights