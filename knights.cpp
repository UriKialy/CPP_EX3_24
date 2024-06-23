#include "knights.hpp"
using namespace std;
namespace ariel
{
    int knights::knightsCount = 0;
    knights::knights(string type, vector<resourceCard> price) : type(type), price(price)
    {
            knightsCount++;
    }
    int knights::get_knightsCount(){
        return knightsCount;
    }
    void knights::display()
    {
        cout << "Type: " << get_type() << endl;
        cout << "Price: ";
        for (auto &resourceCard : price)
        {
            cout << resourceCard.get_type() << " ";
        }
        cout << endl;
    }
    string knights::get_type() 
    {
        return type;
    }
    void knights::clean_knightsCount(){
        knightsCount = 0;
    }
    vector<resourceCard> knights::get_price()
    {
        return price;
    }
}
   

