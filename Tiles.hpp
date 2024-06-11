#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "player.hpp"

using namespace std;
namespace ariel{
class Tiles {
public:
    Tiles();
    Tiles(int id, int value_roll, const string& type);
    Tiles(const Tiles& other);
    ~Tiles();

    int getid() const;
    int getvalue_roll() const;
    string gettype() const;
    vector<int> getedges() const;
    vector<vector<int>> getvertex() const;
    vector<Tiles> getneighbors() const;

    void display_edges() const;
    void display_vertex() const;
    void display() const;

    int setedges(int index, int id);
    int set_vertex(int index, int type, int player_id);
    void set_neighbor(Tiles& neighbor, int index);

    bool operator==(const Tiles& other) const;
    Tiles& operator=(const Tiles& other);
    bool set_first_round_vertex(player& player, int& index);
    bool set_first_round_edge(Player& p1, int &index);
    void update_collision(int index, int id, int type);

private:
    int id;
    int value_roll;
    string type;
    vector<int> edges;
    vector<vector<int>> vertex;
    vector<Tiles> neighbors;

    int check_before_apply(int index, int id);
    int set_special_edges(int index, int id);
    int apply_edges(int index, int id);
    bool check_roads_set_vertex(int index, int type, int player_id);
    bool check_edges(int index, int type, int player_id);
};
}// namespace ariel


