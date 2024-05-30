#include "Tiles.hpp"
namespace ariel
{

    Tiles::Tiles(const string type, const int id, const int value_role) : type(type), id(id), value_role(value_role)
    {
        this->edges = {0, 0, 0, 0, 0, 0};
        this->vertex = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
        this->neighbors = {};
    }
    vector<int> Tiles::get_edges()
    {
        return edges;
    }
    vector<vector<int>> Tiles::get_vertex()
    {
        return vertex;
    }
    string Tiles::get_type() const
    {
        return type;
    }

    int Tiles::get_id() const
    {
        return id;
    }
    vector<Tiles> Tiles::get_neighbors()
    {
        return neighbors;
    }
    int Tiles::get_value_role() const
    {
        return value_role;
    }
    Tiles Tiles::get_tile(string id) const
    {
        return *this;
    } // if we want to get a tile by its id
    int Tiles::set_edge(int index,int player_id)
    {
        if(this->edges.at(index)==0){
        this->edges[index] = player_id;
        return 0;
    }
    return 1;
    }
    int Tiles::set_vertex(int index, int type, int player_id) // 0 for city 1 for suburb
    {
        if(index >=0 && index<6 && this->vertex.at(index).at(0)==0 && type==0 || type==1 && id>=0 && id<3){
        this->vertex.at(index).at(0) = player_id;
        this->vertex.at(index).at(1) = type;
        return 0;
    }    
    return 1; //occupied
    }
    int Tiles::set_neighbor(Tiles& neighbor, int index)
    {
        if (index >= 0 && index < 6)
        {
            this->neighbors.at(index) = neighbor;
            return 0;
        }
        return 1;
    }
    Tiles& Tiles::operator=(const Tiles& other){
        this->type.assign(other.type);
        this->id = other.id;
        this->value_role = other.value_role;
        this->edges = other.edges;
        this->vertex = other.vertex;
        this->neighbors = other.neighbors;
        return *this;
    }
    Tiles::Tiles(const Tiles& other) : type(other.type), id(other.id), 
    value_role(other.value_role), edges(other.edges), vertex(other.vertex), neighbors(other.neighbors){ }// copy ctor
    
};
