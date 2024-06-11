#include "abundanceCard.hpp"
using namespace std;
namespace ariel
{
    abundanceCard::abundanceCard(string type, vector<resourceCard> price) : type(type), price(price)
    {    }
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
