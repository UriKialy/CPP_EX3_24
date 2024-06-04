#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"
#include "resourceCard.hpp"
using namespace std;

/// this is the card class the most abstract one- whcih will be the base class for the developCard,constructionCard and the resourceCard
namespace ariel{
    class card{
        string type;
        vector <resourceCard> price;
        public:
        card(string type, vector<card> price);
       virtual void buy_card(player &p)=0;
       virtual  void use_card(player &p)=0;
    };
}