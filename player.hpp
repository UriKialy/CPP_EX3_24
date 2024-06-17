#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "resourceCard.hpp"
#include "developeCard.hpp"
#include "board.hpp"
#include "victoryCard.hpp"
#include "abundanceCard.hpp"
#include "road_building.hpp"
#include "monopolyCard.hpp"
#include "knights.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;
namespace ariel {

    class board;

class player {
public:
    player(string playerName);
    ~player();

    string getName() const;
    int getScore() const;
    vector<developeCard*>& getDevelopment_cards();
    vector<resourceCard>& getResources();

    void add_development_cards(developeCard* card);
    void add_resources_card(const resourceCard& card);
    void add_const_score(int score);
    void add_road(string road);
    void add_settlement(string settlement);
    void add_city(string city);

    void display_roads();
    void display_development_cards();
    void display_settlements();
    void display_cities();
    void display_resources();

    void buy_card();
    string getrandomcard();
    int use(developeCard* card, player& take1, player& take2, board& board1);

    bool hasResources(const vector<string>& required_resources) const;
    void removeResources(const vector<string>& resources_to_remove);

    developeCard* createDevelopmentCard(const string& card_type);
    void processVictoryCard();
    void processKnightCard();
    void processMonopolyCard(player& take1, player& take2);
    void processYearOfHappyCard();
    void processRoadBuildingCard(board& board1);

    bool removeCardOfType(const string& card_type);
    void takeResourceFromPlayer(player& player, const string& resource);

    int getid();
    int roll_number(board& b, player& p1, player &p2);
    int buy_road(int tile, int edge, board& b, int turn);
    int buy_city(int tile, int vertex, board& b, int turn);
    int buy_settlement(int id, int vertex, board& b, int turn);

    void trade(player& ask1);
    void end_turn();

private:
    static int id;
    string name;
    int score;
    vector<resourceCard> resources;
    vector<developeCard*> development_cards;
    vector<string> roads;
    vector<string> settlements;
    vector<string> cities;
};

void to_lowercase(string& str);
vector<string> splitStringByComma(const string& str);

} // namespace ariel
