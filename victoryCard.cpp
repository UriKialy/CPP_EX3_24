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
            cout<<"there is no more than 4 victory cards"<<endl;
        }
        
    }
    int victoryCard::victoryCardCount = 0;
    string victoryCard::get_type(){
        return type;
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