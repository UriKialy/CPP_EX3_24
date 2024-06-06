#include "victoryCard.hpp"
using namespace std;
namespace ariel
{
    victoryCard::victoryCard(string type, vector<resourceCard> price)
    {
        if(victoryCardCount<4)
        {
            victoryCardCount++;
            this->type = type;
            this->price = price;            
        }
        else
        {
            cout<<"you can't have more than 4 victory cards"<<endl;
        }
        
    }
    int victoryCard::use_card(player &p)
    {
        p.add_point();
    }
    
}