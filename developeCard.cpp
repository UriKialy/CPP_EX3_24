#include "developeCard.hpp"
using namespace std;
namespace ariel
{
    developeCard::developeCard(string type, vector<resourceCard> price) : type(type), price(price)
    {
    }
    string developeCard::get_type()
    {
        return type;
    }
    vector<resourceCard> developeCard::get_price()
    {
        return price;
    }
    void developeCard::display()
    {
        cout << "Type: " << type << endl;
        cout << "Price: ";
        for (auto &i : get_price())
        {
            cout << i.get_type() << " ";
        }
        cout << endl;
    }
}