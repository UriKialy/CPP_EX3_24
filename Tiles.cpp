#include "Tiles.hpp"
namespace ariel
{

    Tiles::Tiles(const string type, const int id, const int value_role) : type(type), id(id), value_role(value_role)
    {
        this->edges = {0, 0, 0, 0, 0, 0};
        this->vertex = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}; // the first element is the player id and the second is city/subberb
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
        try
        {
            return neighbors;
        }
        catch (const exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    int Tiles::get_value_role() const
    {
        return value_role;
    }
    Tiles Tiles::get_tile(string id) const
    {
        return *this;
    } // if we want to get a tile by its id

    int Tiles::set_vertex(int index, int type, int player_id) // 0 for city 1 for suburb
    {
        if (index >= 0 && index < 6 && this->vertex.at(index).at(0) == 0 && type == 0 || type == 1 && id >= 0 && id < 3)
        {
            this->vertex.at(index).at(0) = player_id;
            this->vertex.at(index).at(1) = type;
            return 0;
        }
        return 1; // occupied
    }
    int Tiles::set_neighbor(Tiles &neighbor, int index) // index is in coralation with the the number of neighbors in the array of the tile itself
    {
        if (index >= 0 && index < 6)
        {
            this->neighbors.at(index) = neighbor;
            return 0;
        }
        return 1;
    }
    Tiles &Tiles::operator=(const Tiles &other)
    {
        this->type.assign(other.type);
        this->id = other.id;
        this->value_role = other.value_role;
        this->edges = other.edges;
        this->vertex = other.vertex;
        this->neighbors = other.neighbors;
        return *this;
    }
    bool Tiles::operator==(const Tiles &other)
    {
        return (this->type == other.type && this->id == other.id && this->value_role == other.value_role &&
                this->edges == other.edges && this->vertex == other.vertex && this->neighbors == other.neighbors);
    }
    bool Tiles::operator!=(const Tiles &other)
    {
        return !(*this == other);
    }

    string Tiles::get_yeild() const
    {
        if (type == "forest")
        {
            return "wood";
        }
        else if (type == "hill")
        {
            return "brick";
        }
        else if (type == "mountain")
        {
            return "steel";
        }
        else if (type == "agrictulture_land")
        {
            return "oats";
        }
        else
        {
            return "wool";
        }
    }

    int Tiles::set_edge(int index, int id) // edge is the id of the edge and id is the id of the tile
    {
        bool is_edge_occupied = this->edges.at(index) == 0; // check if the edge is occupied
        bool is_edges_occuipied_by_player = false;
        // consdider if we set at second edge that we
        bool check_firstedge = this->get_neighbors().at((index + 1) % 6).get_edges().at((index + 3 % 6)) == 0; // check if the edge is occupied from prallel tile
        bool is_vertexes_occuiped_by_player = false;
        if (index != 0) // check if the vertexes are occupied by the player who is building the road
        {
            is_vertexes_occuiped_by_player = this->vertex.at(index).at(0) == id || this->vertex.at(index - 1).at(0) == id;
        }
        else
        {
            is_vertexes_occuiped_by_player = this->vertex.at(index).at(0) == id || this->vertex.at(5).at(0) == id;
        }
        if (index != 0 && index != 5)
        { // check if one of the neighbor edges are the players
            is_edges_occuipied_by_player = this->edges.at(index - 1) == id || this->edges.at(index + 1) == id;
        }
        else if (index == 0)
        {
            is_edges_occuipied_by_player = this->edges.at(5) == id || this->edges.at(1) == id;
        }
        else
        { // index==5
            is_edges_occuipied_by_player = this->edges.at(4) == id || this->edges.at(0) == id;
        }
        if (check_firstedge || is_edge_occupied || is_vertexes_occuiped_by_player || is_edges_occuipied_by_player)
        {
            this->edges.at(index) = id;
            this->get_neighbors().at((index + 1) % 6).get_edges().at((index + 3 % 6)) = id;
            return 1;
        }
        else{
            cout<<"you can't build a road here"<<endl;
            return 0;
        
        }
    }
    int Tiles::set_vertex(int index, int type, int player_id)
    {// recall: the vertex vector have the first element as the player id and the second is city/subberb
        if (this->vertex.at(index).at(0) == 0 && (type == 1 || type == 0) && (player_id >= 1 && player_id < 4) && index >= 0 && index < 6)
        {
            int temp = index;
            int first = this->get_neighbors().at(index % 6).get_id();
            int second = this->get_neighbors().at((index + 1) % 6).get_id();
            if (first >= 0 && second >= 0 && first < 19 && second < 19) // check if the neighbors are valid
            {
                // remember to check that if i want to upgarde my suburb to a town here could be problems
                bool check_firstvertex = this->get_neighbors().at(index % 6).get_vertex().at(0).at((index + 2) % 6) == 0;
                bool check_secondvertex = this->get_neighbors().at(index + 1 % 6).get_vertex().at(0).at((index + 4) % 6) == 0;
                bool check_road_back = this->get_edges().at((index - 1) % 6) == player_id;
                bool check_road_foward = this->get_edges().at((index - 1) % 6) == player_id;
                bool is_near_by

                if ((check_firstvertex && check_secondvertex && this->vertex.at(0).at(index) == 0) && (check_road_back || check_road_foward))
                {
                    this->vertex.at(0).at(index) = player_id;
                    {
                        this->vertex.at(0).at(index) = player_id;
                        this->vertex.at(1).at(index) = type;
                        return 1;
                    }
                }
            }
            else
            {
                return 0;
            }
        }
    }
    int Tiles::set_firstRound_vertex(int player_id,int index){
        if(this->vertex.at(index)[0]==0){ // check if the vertex is empty and if so set the data
            this->vertex.at(index).at(0)=player_id;
            this->vertex.at(index).at(1)=1;
            return 1;
        }
        else{
            cout<<"you can't build a suberb here cause this place is taken"<<endl;
            return 0;
        }
    }
    int Tiles::set_firstRound_edge(int player_id,int index){
        if(this->edges.at(index)==0){ // check if the edge is empty and if so set the data
            this->edges.at(index)=player_id;
            return 1;
        }
        else{
            cout<<"you can't build a road here cause this place is taken"<<endl;
            return 0;
        }
    }
};
