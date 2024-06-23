#include "promotion.hpp"
using namespace std;
namespace ariel
{
    promotion::promotion(string type, vector<resourceCard> price) : type(type), price(price)
    {
    }
    string promotion::get_type()
    {
        return type;
    }
    promotion::~promotion()
    {
    }
    promotion::promotion()
    {
    }
    void promotion::display()
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