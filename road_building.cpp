#include "road_building.hpp"
using namespace std;
namespace ariel
{
    road_building::road_building(string type, vector<resourceCard> price) : road_building(type, price)
    {    }
    void road_building::display()
    {
             cout << "Type: " << get_type() << endl;
        cout << "Price: ";
        for ( auto &promotion : get_price()) {
            cout << promotion.get_type() << " ";
        }
        cout << endl;
    }
   
}