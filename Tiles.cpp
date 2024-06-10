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

    int Tiles::set_edge(int index, int id) // edge is the id of the edge and id is the id of the user
    {
        if (index < 0 || index > 5 || id < 1 || id > 3)
        {
            cout << "index out of range" << endl;
            return 0;
        }
        if (this->edges.at(index) != 0)
        {
            cout << "you can't build a road here cause this place is taken" << endl;
            return 0;
        } // check if the edge is occupied
        if (set_special_edges(index, id) == 1)
        {
            return 1;
        }

        bool check_firstedge = false, check_neighbor_edges1 = false, check_neighbor_edges2 = false;
        // consdider if we set at second edge that we
        try
        {
            check_firstedge = this->get_neighbors().at((index + 1) % 6).get_edges().at((index + 3 % 6)) == 0; // check if the edge is occupied from prallel tile
        }
        catch (nullptr_t &e)
        {
            check_firstedge = true;
        }

        try
        {
            check_neighbor_edges1 = this->get_neighbors().at((index + 1) % 6).get_edges().at((index + 2) % 6) == 0;
        }
        catch (nullptr_t &e)
        {
            check_neighbor_edges1 = true;
        }
        try
        {
            check_neighbor_edges2 = this->get_neighbors().at((index + 1) % 6).get_edges().at((index + 4) % 6) == 0;
        }
        catch (nullptr_t &e)
        {
            check_neighbor_edges2 = true;
        }
        bool check_neighbor_edges = check_neighbor_edges1 || check_neighbor_edges2;
        if (check_firstedge || check_neighbor_edges || check_before_apply(index, id))
        {
            return apply_edges(index, id);
        }
        else
        {
            cout << "you can't build a road here" << endl;
            return 0;
        }
    }
    int Tiles::check_before_apply(int index, int id) // the general checks that are coomon to all the tiles
    {
        // check if one of the neighbor edges are the players, the plus 6 is to make sure that the index is not negative
        bool is_edges_occuipied_by_player = this->edges.at((6 + index - 1) % 6) == id || this->edges.at((index + 1) % 6) == id;
        // check if the vertexes are occupied by the player who is building the road
        bool is_vertexes_occuiped_by_player = this->vertex.at((6 + index - 1) % 6).at(0) == id || this->vertex.at((index + 1) % 6).at(0) == id;
        return is_edges_occuipied_by_player || is_vertexes_occuiped_by_player;
    }
    // function for special tiles whom needed a speciwl checks
    int Tiles::set_special_edges(int index, int id)
    {
        bool check_upper = false, left_side = false, right_side = false, bottom = false;
        bool is_edges_occuipied_by_player = this->edges.at((6 + index - 1) % 6) == id || this->edges.at((index + 1) % 6) == id;
        int no_neighbors_edges[] = {0, 7, 10, 16, 18, 11, 2};
        for (int i = 0; i < 6; i++)
        {
            if (no_neighbors_edges[i] == this->id && index == i || is_edges_occuipied_by_player)
            {
                this->edges.at(index) = id;
                return 1;
            }
        }
        if (this->id < 3 && index == 0 || index == 5)
        {
            for (int i = 0; i < 2; i++)
            {
                if (this->id == i && index == 5)
                {
                    check_upper = this->neighbors.at(5).get_edges().at(0) == id || this->neighbors.at(5).get_edges().at(1) == id;
                }
            }
            if (index == 0 && (this->id == 1 || this->id == 2))
            {
                check_upper = this->neighbors.at(2).get_edges().at(5) == id || this->neighbors.at(2).get_edges().at(4) == id;
            }
            if (check_before_apply(index, id) || check_upper)
            {
                return apply_edges(index, id);
            }
        }
        if ((index == 1 || index == 2 || index == 3) && this->id == 0 || this->id == 3 || this->id == 7 || this->id == 12 || this->id == 16)
        { // the tiles at the left side
            if (this->id == 0 && index == 1)
            {
                if (this->edges.at(0) == id || this->edges.at(2) == id || this->get_neighbors().at(3).get_edges().at(5) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if (this->id == 3 && index == 0 || this->id == 7 && index == 0)
            {
                if (this->edges.at(5) == id || this->edges.at(1) == id || this->get_neighbors().at(0).get_edges().at(1) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if (this->id == 3 && index == 1)
            {
                if (this->edges.at(2) == id || this->edges.at(0) == id || this->get_neighbors().at(3).get_edges().at(0) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if (this->id == 7 && index == 2 || this->id == 12 && index == 2)
            {
                if (this->edges.at(3) == id || this->edges.at(1) == id || this->get_neighbors().at(3).get_edges().at(1) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if (this->id == 16 && index == 1)
            {
                if (this->edges.at(0) == id || this->edges.at(2) == id || this->get_neighbors().at(1).get_edges().at(2) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
        }
        if (index == 16 || index == 17 || index == 18)
        { // the tiles at the bottom
            if (this->id == 16 && index == 3)
            {
                if (this->edges.at(2) == id || this->edges.at(4) == id || this->get_neighbors().at(5).get_edges().at(2) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if (this->id == 17 && index == 2 || this->id == 18 && index == 2)
            {
                if (this->edges.at(1) == id || this->edges.at(3) == id || this->get_neighbors().at(2).get_edges().at(3) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if (this->id == 17 && index == 3)
            {
                if (this->edges.at(2) == id || this->edges.at(3) == id || this->get_neighbors().at(5).get_edges().at(3) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
        }
        if(index>2){
            if(this->id==2 && index ==4){
                if(this->edges.at(3)==id || this->edges.at(5)==id || this->get_neighbors().at(4).get_edges().at(5)==id || check_before_apply(index,id)){
                    return apply_edges(index,id);
                }
            }
            else if(this->id==6 && index ==5){
                if(this->edges.at(0)==id || this->edges.at(4)==id || this->get_neighbors().at(1).get_edges().at(4)==id || check_before_apply(index,id)){
                    return apply_edges(index,id);
                }
            }
            else if(this->id==6 && index ==4){
                if(this->edges.at(3)==id || this->edges.at(5)==id || this->get_neighbors().at(4).get_edges().at(5)==id || check_before_apply(index,id)){
                    return apply_edges(index,id);
                }
            }
            else if(this->id==11 && index ==5){
                if(this->edges.at(0)==id || this->edges.at(4)==id || this->get_neighbors().at(1).get_edges().at(4)==id || check_before_apply(index,id)){
                    return apply_edges(index,id);
                }
            }
             else if(this->id==11 && index ==3 || this->id==15 && index ==3){
                if(this->edges.at(2)==id || this->edges.at(4)==id || this->get_neighbors().at(3).get_edges().at(4)==id || check_before_apply(index,id)){
                    return apply_edges(index,id);
                }
            }
            else if(this->id==15 && index ==4 || this->id==108 && index ==4){
                if(this->edges.at(3)==id || this->edges.at(5)==id || this->get_neighbors().at(0).get_edges().at(3)==id || check_before_apply(index,id)){
                    return apply_edges(index,id);
                }
            }
        }


        return 0;
    }
    int Tiles::apply_edges(int index, int id)
    {
        this->edges.at(index) = id;
        try
        {
            this->get_neighbors().at((index + 1) % 6).get_edges().at((index + 3 % 6)) = id;
        }
        catch (nullptr_t &e)
        {
            cout << "no nighbor to set edge on" << endl;
        }
        return 1;
    }
    int Tiles::set_vertex(int index, int type, int player_id)
    { // recall: the vertex vector have the first element as the player id and the second is city/subberb
        if (this->vertex.at(index).at(0) == 0 && (type == 1 || type == 0) && (player_id >= 1 && player_id < 4) && index >= 0 && index < 6)
        {
            int temp = index;
            int first = this->get_neighbors().at(index % 6).get_id();
            int second = this->get_neighbors().at((index + 1) % 6).get_id();
            bool first_check = false, second_check = false, third_check = false;
            if (first >= 0 && second >= 0 && first < 19 && second < 19) // check if the neighbors are valid
            {
                // remember to check that if i want to upgarde my suburb to a town here could be problems
                bool check_firstvertex = this->get_neighbors().at(index % 6).get_vertex().at(0).at((index + 2) % 6) == 0;
                bool check_secondvertex = this->get_neighbors().at(index + 1 % 6).get_vertex().at(0).at((index + 4) % 6) == 0;
                bool check_road_back = this->get_edges().at((index - 1) % 6) == player_id;
                bool check_road_foward = this->get_edges().at((index - 1) % 6) == player_id;
                bool is_near_by_vertex = false;
                switch (index)
                {
                case 0:
                    first_check = this->get_neighbors().at(0).get_vertex().at(1).at(0) == 0;
                    second_check = this->get_vertex().at(5).at(0) == 0;
                    second_check = this->get_vertex().at(1).at(0) == 0;
                    break;
                case 1:
                    first_check = this->get_neighbors().at(1).get_vertex().at(2).at(0) == 0;
                    first_check = this->get_neighbors().at(1).get_vertex().at(4).at(0) == 0;
                    second_check = this->get_vertex().at(2).at(0) == 0;
                    break;
                case 2:
                    first_check = this->get_neighbors().at(2).get_vertex().at(3).at(0) == 0;
                    second_check = this->get_vertex().at(1).at(0) == 0;
                    second_check = this->get_vertex().at(3).at(0) == 0;
                    break;
                case 3:
                    first_check = this->get_neighbors().at(4).get_vertex().at(2).at(0) == 0;
                    second_check = this->get_vertex().at(2).at(0) == 0;
                    second_check = this->get_vertex().at(4).at(0) == 0;
                    break;
                case 4:
                    first_check = this->get_neighbors().at(4).get_vertex().at(5).at(0) == 0;
                    first_check = this->get_neighbors().at(4).get_vertex().at(1).at(0) == 0;
                    second_check = this->get_vertex().at(5).at(0) == 0;
                    break;
                case 5:
                    first_check = this->get_neighbors().at(0).get_vertex().at(4).at(0) == 0;
                    first_check = this->get_neighbors().at(0).get_vertex().at(2).at(0) == 0;
                    second_check = this->get_vertex().at(4).at(0) == 0;
                    break;
                default:
                    break;
                }
                bool toatl = first_check && second_check && third_check;
                bool is_near_by_edge = false;
                if (index != 5)
                {
                    is_near_by_edge = this->get_edges().at(index) == player_id && this->get_edges().at(index + 1) == player_id;
                }
                else
                {
                    is_near_by_edge = this->get_edges().at(5) == player_id && this->get_edges().at(0) == player_id;
                }
                if ((check_firstvertex && check_secondvertex && this->vertex.at(0).at(index) == 0) && (check_road_back || check_road_foward) &&
                    toatl && is_near_by_edge)
                {
                    this->vertex.at(0).at(index) = player_id;
                    this->vertex.at(0).at(index) = player_id;
                    this->vertex.at(1).at(index) = type;
                    this->get_neighbors().at(index).get_vertex().at((index + 2) % 6).at(0) = player_id; // set the vertex of the neighbor
                    this->get_neighbors().at(index).get_vertex().at((index + 2) % 6).at(1) = type;
                    this->get_neighbors().at(index + 1).get_vertex().at((index + 4) % 6).at(0) = player_id; // set the vertex of the 2nd neighbor
                    this->get_neighbors().at(index + 1).get_vertex().at((index + 4) % 6).at(1) = type;
                    return 1;
                }
            }
            else
            {
                return 0;
            }
        }
    }
    int Tiles::set_firstRound_vertex(int player_id, int index)
    {
        if (this->vertex.at(index)[0] == 0)
        { // check if the vertex is empty and if so set the data
            this->vertex.at(index).at(0) = player_id;
            this->vertex.at(index).at(1) = 1;
            return 1;
        }
        else
        {
            cout << "you can't build a suberb here cause this place is taken" << endl;
            return 0;
        }
    }
    int Tiles::set_firstRound_edge(int player_id, int index)
    {
        if (this->edges.at(index) == 0)
        { // check if the edge is empty and if so set the data
            this->edges.at(index) = player_id;
            return 1;
        }
        else
        {
            cout << "you can't build a road here cause this place is taken" << endl;
            return 0;
        }
    }
};
