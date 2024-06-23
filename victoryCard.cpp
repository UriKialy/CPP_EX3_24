#include "victoryCard.hpp"
using namespace std;
namespace ariel
{
    int victoryCard::victoryCardCount = 0;
    victoryCard::victoryCard(string type, vector<resourceCard> &price) : developeCard(type, price)
    {
        victoryCardCount++;
        cout<<"the num of victorycard is  increased to:"<<victoryCardCount<<endl;
    }

    
    int victoryCard::get_victoryCardCount()
    {
        return victoryCardCount;
    }

     void victoryCard::clean_card()
    {
        victoryCardCount=0;
    }
    void victoryCard::display()
    {
        cout << "Type: " << get_type() << endl;
        cout << "Price: ";
        for (auto &resourceCard : get_price())
        {
            cout << resourceCard.get_type() << " ";
        }
        cout << endl;
    }
    

}