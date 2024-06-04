#include "monopolyCard.hpp"

using namespace std;
namespace ariel
{
    monopoly::monopoly(string type, vector<resourceCard> price) : developCard(type, price)
    {    }
    void monopoly::use_card(player &p)
    {
        cout << "promotion card used" << endl;
    }
    void promotion::buy_card(player &p)
    {
        cout << "promotion card bought" << endl;
    }
}