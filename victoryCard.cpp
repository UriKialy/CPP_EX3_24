#include "victoryCard.hpp"
using namespace std;
namespace ariel
{
    victoryCard::victoryCard(string type, vector<resourceCard>& price)
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
    int victoryCard::get_victoryCardCount()
    {
        return victoryCardCount;
    }
    void victoryCard::display()
    {
        cout<<"Type: "<<get_type()<<endl;
        cout<<"Price: ";
        for(auto &promotion: get_price())
        {
            cout<<promotion.get_type()<<" ";
        }
        cout<<endl;
    }
    
}