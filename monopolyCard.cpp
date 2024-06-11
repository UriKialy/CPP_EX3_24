#include "monopolyCard.hpp"

using namespace std;
namespace ariel
{
    monopolyCard::monopolyCard(string type, vector<resourceCard> price) : monopolyCard(type, price)
    {    }
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