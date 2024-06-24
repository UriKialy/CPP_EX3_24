#include "road_building.hpp"
using namespace std;
namespace ariel
{
    road_building::road_building(string type, vector<resourceCard> price) : promotion(type, price)
    {    }
    void road_building::display()
    {
             cout << "Type: " << get_type() << endl;
             cout << "Price: wool steel Wheat ";
                cout << endl;
    }
  
   
}