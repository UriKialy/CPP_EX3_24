#include "abundanceCard.hpp"
using namespace std;
namespace ariel
{
    abundanceCard::abundanceCard(string type, vector<resourceCard> price) : promotion(type, price)
    { }
 
    int abundanceCard::use_card(player &p)
    {
        cout << "abundance card used" << endl;
    }
}
    