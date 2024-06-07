#include <iostream>
#include <string>
#include <vector>
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
        virtual string get_type()=0;
        vector<resourceCard> get_price();
    };
}
// this the developCard class which is a base card for promotion, victory, knights