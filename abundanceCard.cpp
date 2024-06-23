#include "abundanceCard.hpp"
using namespace std;
namespace ariel
{
    abundanceCard::abundanceCard(string type, vector<resourceCard> price) : promotion(type, price)
    {    }
    void abundanceCard::display()
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
