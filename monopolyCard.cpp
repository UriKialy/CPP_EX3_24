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
  
}