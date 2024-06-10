#include "abundanceCard.hpp"
using namespace std;
namespace ariel
{
    abundanceCard::abundanceCard(string type, vector<resourceCard> price) : type(type), price(price)
    {
    }
    int abundanceCard::use_card(player &p)
    {
        cout << "abundance card used" << endl;
        return 0;
    }
    void abundanceCard::display()
    {
        cout << "Type: " << get_type() << endl;
        cout << "Price: ";
        for (auto &abundance : get_price())
        {
            cout << abundance.get_type() << " ";
        }
        cout << endl;
    }
}
