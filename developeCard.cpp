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
    string developeCard::get_type()
    {
        return type;
    }
}