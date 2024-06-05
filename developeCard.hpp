#include <iostream>
#include <string>
#include <vector>
#pragma "player.hpp"
#include "resourceCard.hpp"
using namespace std;
namespace ariel
{
    class developeCard 
    {
        string type;
        vector<resourceCard> price;
    public:
        developeCard(string type, vector<resourceCard> price);
        string get_type();
        vector<resourceCard> get_price();
            };
}
// this the developCard class which is a base card for promotion, victory, knights