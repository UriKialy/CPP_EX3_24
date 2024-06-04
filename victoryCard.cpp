#include "vicoctoryCard.hpp"
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
    void victoryCard::use_card(player &p)
    {
        cout << "victory card used" << endl;
    }
    void victoryCard::buy_card(player &p)
    {
        cout << "victory card bought" << endl;
    }
}