#include <iostream>
#include <string>
#include <vector>
#include "developeCard.hpp"
#pragma once
using namespace std;

namespace ariel{
    class victoryCard: public developeCard{
        string type;
        vector <resourceCard> price;
        public:
         static int victoryCardCount;
        victoryCard(string type, vector<resourceCard>& price);        
         void display() ;
        static int get_victoryCardCount();
        static void clean_card();
        
    };
}