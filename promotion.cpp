#include "promotion.hpp"
using namespace std;
namespace ariel
{
   promotion::promotion(string type, vector<resourceCard> price) : type(type), price(price)
    {    }
    string promotion::get_type() 
    {
        return type;
    }
    promotion::~promotion() 
    {    }
    promotion::promotion() 
    {      }
 

}