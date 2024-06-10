#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"
#include "developeCard.hpp"
#pragma once
using namespace std;

/// this is the card class the most abstract one- whcih will be the base class for the developCard,constructionCard and the resourceCard
namespace ariel{
    class victoryCard: public developeCard{
        string type;
        vector <resourceCard> price;
        public:
         static int victoryCardCount;
        victoryCard(string type, vector<resourceCard>& price);
         int use_card(player &p);
         void display();
    };
}