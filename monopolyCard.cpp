#include "monopolyCard.hpp"

using namespace std;
namespace ariel
{
    monopolyCard::monopolyCard(string type, vector<resourceCard> price) : promotion(type, price)
    {    }
    void monopolyCard::display() {
            cout << "Type: " << get_type() << endl;
        cout << "Price: wool steel Wheat ";
        cout << endl;
    }  
}