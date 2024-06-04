#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"
#include "developCard.hpp"
using namespace std;

/// this is the card class the most abstract one- whcih will be the base class for the developCard,constructionCard and the resourceCard
namespace ariel{
    class victoryCard: public developCard{
        string type;
        vector <resourceCard> price;
        public:
        static int victoryCardCount=0;
        card(string type, vector<card> price);
        int buy_card(player &p);
         int use_card(player &p);
    };
}