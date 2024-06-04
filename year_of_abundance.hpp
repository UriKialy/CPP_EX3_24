#include "promotion.hpp"
using namespace std;
namespace ariel
{
    class year_of_abundance : public promotion
    {
        string type;
        vector<resourceCard> price;
    public:
        year_of_abundance(string type, vector<resourceCard> price);
        virtual void buy_card(player &p)=0;
        void use_card(player &p);
    };
}