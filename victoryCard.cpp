#include "victoryCard.hpp"
using namespace std;
namespace ariel
{
    int victoryCard::victoryCardCount = 0;
    victoryCard::victoryCard(string type, vector<resourceCard> &price) : developeCard(type, price)
    {
        cout<<"uri"<<victoryCardCount<<endl;
        victoryCardCount++;
    }

    string victoryCard::get_type()
    {
        return type;
    }
    int victoryCard::get_victoryCardCount()
    {
        return victoryCardCount;
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
     void victoryCard::clean_card()
    {
        victoryCardCount=0;
    }

}