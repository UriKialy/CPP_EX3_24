#include <iostream>
#include <string>
#include <vector>
#include "resourceCard.hpp"
#include "developmentCard.hpp"
using namespace std;
namespace ariel{

class player{
    int id;
    string name;
    int win_counter;
    int points;
    vector<resourceCard> resource_cards;
    vector<developmentCard> cards;
    public:
    player(string name, int id);
    //~player()=default;
    int get_id() const;
    void add_win();
    int get_points();
    void add_points(int points);
    int get_win_counter() const;
    int add_resource_card(resourceCard rc);
    vector<resourceCard> get_resource_cards() ;
    int add_card(developmentCard c);
    vector<developmentCard> get_developmentCard();
    
};

}