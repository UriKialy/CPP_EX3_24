#include "promotion.hpp"
using namespace std;
namespace ariel
{
    class abundanceCard : public promotion
    {
        string type;
        vector<resourceCard> price;
    public:
        abundanceCard(string type, vector<resourceCard> price);
         int buy_card(player &p);
        int use_card(player &p);
    };
}