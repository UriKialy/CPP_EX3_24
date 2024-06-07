#include <iostream>
#include <string>
#include <vector>
#include "resourceCard.hpp"
#include "developeCard.hpp"
#include "road_building.hpp"
#pragma once
#include <algorithm>

using namespace std;
namespace ariel{

class player{
    int id;
    string name;
    int win_counter;
    int points;
    vector<resourceCard> resource_cards;
    vector<developeCard> cards;
    public:
    player(string name, int id);
    //~player()=default;
    string get_name() const;
    int get_id() const;
    void add_win();
    int get_points();
    void add_points(int points);
    int get_win_counter() const;
    void add_resource_card(resourceCard rc);
    vector<resourceCard> get_resource_cards() ;
    void add_card(developeCard c);
    vector<developeCard> get_developmentCard();
    int buy_card(developeCard &card);
    int trade_card(developeCard &card, player &p);
    bool find_card(string type);
};

}