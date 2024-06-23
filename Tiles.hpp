#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "player.hpp"
#include <algorithm>

namespace ariel
{
    class player; 
    class Tiles
    {
    public:
        Tiles();
        Tiles(int id, int value_roll, const std::string &type);
        Tiles(const Tiles &other);
        ~Tiles();

        int getid() const;
        int getvalue_roll() const;
        std::string gettype();
        std::vector<int> getedges();
        std::vector<std::vector<int>> getvertex();
        std::vector<Tiles *> getneighborhood();
        int setedges(int index, int id);
        int set_vertex(int index, int type, int player_id);
        void set_neighbor(Tiles &neighbor, int index);
        void update_collision(int index, int id, int type);
        void display_edges();
        void display_vertixes();
        bool operator==(const Tiles &other) const;
        Tiles &operator=(const Tiles &other);
        void display() const;
        int set_special_edges(int index, int id);
        int check_before_apply(int index, int id);
        int apply_edges(int index, int id);
        bool set_first_round_vertex(player &player, int &index);
        bool set_first_round_edge(player &p1, int &index);

    private:
        int id;
        int value_roll;
        std::string type;
        std::vector<int> edges;
        std::vector<std::vector<int>> vertexes;
        bool check_roads_set_vertex(int index, int type, int player_id);
        bool check_edges(int index, int type, int player_id);
        Tiles *neighbors[6];
    };
} // namespace ariel
