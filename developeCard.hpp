#include <iostream>
#include <string>
#include <vector>
#include "resourceCard.hpp"
using namespace std;
namespace ariel
{
    class developeCard
    {
    protected:
        string type;
        vector<resourceCard> price;

    public:
        developeCard(string type, vector<resourceCard> price);
        explicit developeCard() = default;
        virtual string get_type() = 0;
        vector<resourceCard> get_price();
    };
}
// this the developCard class which is a base card for promotion, victory, knights