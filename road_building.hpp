#include "promotion.hpp"
#pragma once
using namespace std;
namespace ariel
{
    class road_building : public promotion
    {
        string type;
        vector<resourceCard> price;
    public:
        road_building(string type, vector<resourceCard> price); 
        void display() override;
        
    };
}