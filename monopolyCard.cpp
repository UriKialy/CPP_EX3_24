#include "monopolyCard.hpp"

using namespace std;
namespace ariel
{
    monopolyCard::monopolyCard(string type, vector<resourceCard> price) : monopolyCard(type, price)
    {    }
    int monopolyCard::use_card(player &p)
    {
        cout << "promotion card used" << endl;
        return 0;
    }
    void monopolyCard::display()
    {
            cout << "Type: " << get_type() << endl;
        cout << "Price: ";
        for ( auto &promotion : get_price()) {
            cout << promotion.get_type() << " ";
        }
        cout << endl;
    }
  
}