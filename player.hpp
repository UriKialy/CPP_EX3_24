#pragma once
#include <string>
#include <vector>
#include "developeCard.hpp"
#include "resourceCard.hpp"
#include "board.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "victoryCard.hpp"
#include "road_building.hpp"
#include "monopolyCard.hpp"
#include "abundanceCard.hpp"
#include "knights.hpp"
#include <sstream>
#include <random>
using namespace std;
namespace ariel
{
    class victoryCard;
    class road_building;
    class abundanceCard;
    class monopolyCard;
    class knights;
    class board;

    class player
    {
        string name;
        int score;
        vector<developeCard *> development_cards;
        vector<resourceCard> resources;
        vector<string> roads;
        vector<string> settlements;
        vector<string> cities;
        static int id;

    public:
        player(string playerName);
        ~player(); // Destructor to free allocated memory
        string getName() const;
        int getScore() const;
        vector<developeCard *> &getDevelopment_cards();
        vector<resourceCard> &getResources();
        void add_development_cards(developeCard *card);
        void add_resourceCard(const resourceCard &card);
        void add_points(int score);
        void buy_card();
        string getrandomcard();
        int use(developeCard *card, player &take1, player &take2, board &board1);
        int getid();
        int buy_road(int id, int edge, board &b, int turn);
        void display_resources();
        void display_development_cards();
        void trade(player &ask1);
        int buy_settlement(int id, int vertex, board &b, int turn);
        int buy_city(int id, int vertex, board &b, int turn);
        int roll_number(board &b, player &p1, player &p2);
        void display_roads();
        void display_settlements();
        void display_cities();
        void add_road(string road);
        void processKnightCard();
        void add_settlement(string settlement);
        void add_city(string city);
        developeCard *createDevelopmentCard(const string &card_type);

        void end_turn();

    private:
        bool hasResources(const vector<string> &required_resources) const;
        void removeResources(const vector<string> &resources_to_remove);
        void processVictoryCard();
        void processMonopolyCard(player &take1, player &take2);
        void process_abundanceCard();
        void processRoadBuildingCard(board &board1);
        bool removeCardOfType(const string &card_type);
        void takeResourceFromPlayer(player &player, const string &resource);
        void to_lowercase(string &str);
    };
}
