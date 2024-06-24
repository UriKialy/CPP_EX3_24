#include "promotion.hpp"
using namespace std;
namespace ariel
{
    promotion::promotion(string type, vector<resourceCard> price) : type(type), price({resourceCard("wool"),resourceCard("steel"),resourceCard("wheat")})
    {
    }
    string promotion::get_type()
    {
        return type;
    }
    vector<resourceCard> promotion::get_price()
    {
        cout << "Price: ";
        return price;
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
        cout << "Price: wool steel Wheat";  
        cout << endl;
    }
   
    
 

}