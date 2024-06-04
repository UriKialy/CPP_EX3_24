#include "card.hpp"
#include "player.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace ariel
{
    class resourceCard : public card
    {
        string type;
        vector<card> price;

    public:
        resourceCard(string type);
        void buy_card(player &p);
        void use_card(player &p);
    };
} // namespace ariel