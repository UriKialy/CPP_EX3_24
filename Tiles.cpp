#include "Tiles.hpp"
using namespace std;
namespace ariel
{

    Tiles::Tiles() : id(0), value_roll(0), type("")
    {
        this->edges = {0, 0, 0, 0, 0, 0};
        this->vertexes = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
        for (int i = 0; i < 6; ++i)
        {
            neighbors[i] = nullptr;
        }
    }

    Tiles::Tiles(int id, int value_roll, const string &type) : id(id), value_roll(value_roll), type(type)
    {
        this->edges = {0, 0, 0, 0, 0, 0};
        this->vertexes = {{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
        for (int i = 0; i < 6; ++i)
        {
            neighbors[i] = nullptr;
        }
    }

    Tiles::Tiles(const Tiles &other) : id(other.id), value_roll(other.value_roll), type(other.type), edges(other.edges), vertexes(other.vertexes)
    {
        for (int i = 0; i < 6; ++i)
        {
            neighbors[i] = other.neighbors[i];
        }
    }

    Tiles::~Tiles()
    {
        // No need to clear vectors as they are managed by the standard library
    }

    int Tiles::getid() const
    {
        return id;
    }

    int Tiles::getvalue_roll() const
    {
        return value_roll;
    }

    string Tiles::gettype()
    {
        return type;
    }

    vector<int> Tiles::getedges()
    {
        return edges;
    }

    vector<vector<int>> Tiles::getvertex()
    {
        return vertexes;
    }

    vector<Tiles *> Tiles::getneighborhood()
    {
        vector<Tiles *> neighborhood_list(neighbors, neighbors + 6);
        return neighborhood_list;
    }
    void Tiles::display_edges()
    {
        for (size_t i = 0; i < edges.size(); i++)
        {
            cout << edges.at(i) << endl;
        }
    }
    void Tiles::display_vertixes()
    {
        int counter = 0;
        for (size_t i = 0; i < vertexes.size(); i++)
        {
            counter++;
        }
        cout << "ll" << counter << endl;
    }

    int Tiles::setedges(int index, int id) // edge is the id of the edge and id is the id of the user
    {
        if (index < 0 || index > 5 || id < 1 || id > 3)
        {
            cout << "index out of range" << endl;
            return 0;
        }
        if (this->edges.at(index) != 0)
        {
            cout << "you can't build a road here because this place is taken" << endl;
            return 0;
        } // check if the edge is occupied
        if (set_special_edges(index, id) == 1)
        {
            return 1;
        }

        bool check_firstedge = false, check_neighbor_edges1 = false, check_neighbor_edges2 = false;

        try
        {
            if (getneighborhood().at((index + 1) % 6) != nullptr)
            {
                check_firstedge = getneighborhood().at((index + 1) % 6)->getedges().at((index + 3) % 6) == 0;
            }
        }
        catch (const exception &e)
        {
            cout << "Error checking first edge: " << e.what() << endl;
            check_firstedge = true; // Assume failure if exception occurs
        }

        try
        {
            if (getneighborhood().at((index + 1) % 6) != nullptr)
            {
                check_neighbor_edges1 = getneighborhood().at((index + 1) % 6)->getedges().at((index + 2) % 6) == 0;
            }
        }
        catch (const exception &e)
        {
            cout << "Error checking neighbor edge 1: " << e.what() << endl;
            check_neighbor_edges1 = true; // Assume failure if exception occurs
        }

        try
        {
            if (getneighborhood().at((index + 1) % 6) != nullptr)
            {
                check_neighbor_edges2 = getneighborhood().at((index + 1) % 6)->getedges().at((index + 4) % 6) == 0;
            }
        }
        catch (const exception &e)
        {
            cout << "Error checking neighbor edge 2: " << e.what() << endl;
            check_neighbor_edges2 = true; // Assume failure if exception occurs
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

    int Tiles::check_before_apply(int index, int id) // the general checks that are common to all the Tiless
    {
        // check if one of the neighbor edges are the player's, the plus 6 is to make sure that the index is not negative
        bool is_edges_occuipied_by_player = this->edges.at((6 + index - 1) % 6) == id || this->edges.at((index + 1) % 6) == id;
        // check if the vertexes are occupied by the player who is building the road
        bool is_vertexes_occuiped_by_player = this->vertexes.at((6 + index - 1) % 6).at(0) == id || this->vertexes.at((index + 1) % 6).at(0) == id;
        return is_edges_occuipied_by_player || is_vertexes_occuiped_by_player;
    }

    // function for special Tiless that need special checks
    int Tiles::set_special_edges(int index, int id)
    {
        bool check_upper = false;
        bool is_edges_occuipied_by_player = this->edges.at((6 + index - 1) % 6) == id || this->edges.at((index + 1) % 6) == id;
        int no_neighbors_edges[] = {0, 7, 10, 16, 18, 11, 2};
        for (int i = 0; i < 6; i++)
        {
            if (no_neighbors_edges[i] == this->id && (index == i || is_edges_occuipied_by_player))
            {
                this->edges.at(index) = id;
                return 1;
            }
        }
        if (this->id < 3 && (index == 0 || index == 5))
        {
            for (int i = 0; i < 2; i++)
            {
                if (this->id == i && index == 5)
                {
                    try
                    {
                        if (getneighborhood().at(5) != nullptr)
                        {
                            check_upper = getneighborhood().at(5)->getedges().at(0) == id || getneighborhood().at(5)->getedges().at(1) == id;
                        }
                    }
                    catch (const exception &e)
                    {
                        cout << "Error checking upper edge: " << e.what() << endl;
                    }
                }
            }
            if (index == 0 && (this->id == 1 || this->id == 2))
            {
                try
                {
                    if (getneighborhood().at(2) != nullptr)
                    {
                        check_upper = getneighborhood().at(2)->getedges().at(5) == id || getneighborhood().at(2)->getedges().at(4) == id;
                    }
                }
                catch (const exception &e)
                {
                    cout << "Error checking upper edge: " << e.what() << endl;
                }
            }
            if (check_before_apply(index, id) || check_upper)
            {
                return apply_edges(index, id);
            }
        }
        if ((index == 1 || index == 2 || index == 3) && (this->id == 0 || this->id == 3 || this->id == 7 || this->id == 12 || this->id == 16))
        { // the Tiless on the left side
            if (this->id == 0 && index == 1)
            {
                if (this->edges.at(0) == id || this->edges.at(2) == id || this->getneighborhood().at(3)->getedges().at(5) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if ((this->id == 3 && index == 0) || (this->id == 7 && index == 0))
            {
                if (this->edges.at(5) == id || this->edges.at(1) == id || this->getneighborhood().at(0)->getedges().at(1) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if (this->id == 3 && index == 1)
            {
                if (this->edges.at(2) == id || this->edges.at(0) == id || this->getneighborhood().at(3)->getedges().at(0) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if ((this->id == 7 && index == 2) || (this->id == 12 && index == 2))
            {
                if (this->edges.at(3) == id || this->edges.at(1) == id || this->getneighborhood().at(3)->getedges().at(1) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if (this->id == 16 && index == 1)
            {
                if (this->edges.at(0) == id || this->edges.at(2) == id || this->getneighborhood().at(1)->getedges().at(2) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
        }
        if (index == 16 || index == 17 || index == 18)
        { // the Tiless at the bottom
            if (this->id == 16 && index == 3)
            {
                if (this->edges.at(2) == id || this->edges.at(4) == id || this->getneighborhood().at(5)->getedges().at(2) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if ((this->id == 17 && index == 2) || (this->id == 18 && index == 2))
            {
                if (this->edges.at(1) == id || this->edges.at(3) == id || this->getneighborhood().at(2)->getedges().at(3) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if (this->id == 17 && index == 3)
            {
                if (this->edges.at(2) == id || this->edges.at(4) == id || this->getneighborhood().at(1)->getedges().at(4) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if (this->id == 18 && index == 3)
            {
                if (this->edges.at(2) == id || this->edges.at(4) == id || this->getneighborhood().at(0)->getedges().at(4) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
        }
        if (index == 4 || index == 5)
        { // the Tiless at the right side
            if (this->id == 10 && index == 4)
            {
                if (this->edges.at(3) == id || this->edges.at(5) == id || this->getneighborhood().at(4)->getedges().at(5) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if (this->id == 11 && index == 5)
            {
                if (this->edges.at(0) == id || this->edges.at(4) == id || this->getneighborhood().at(1)->getedges().at(4) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if ((this->id == 11 && index == 3) || (this->id == 15 && index == 3))
            {
                if (this->edges.at(2) == id || this->edges.at(4) == id || this->getneighborhood().at(3)->getedges().at(4) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
                }
            }
            else if ((this->id == 15 && index == 4) || (this->id == 18 && index == 4))
            {
                if (this->edges.at(3) == id || this->edges.at(5) == id || this->getneighborhood().at(0)->getedges().at(3) == id || check_before_apply(index, id))
                {
                    return apply_edges(index, id);
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
            if (getneighborhood().at((index + 1) % 6) != nullptr)
            {
                getneighborhood().at((index + 1) % 6)->getedges().at((index + 3) % 6) = id;
            }
        }
        catch (const exception &e)
        {
            cout << "Error applying edge to neighbor: " << e.what() << endl;
        }
        return 1;
    }

    int Tiles::set_vertex(int index, int type, int player_id)
    {
        cout << "dani" << endl;
        bool check1 = check_roads_set_vertex(index, type, player_id);
        cout << "uri" << check1 << endl;
        bool check2 = check_edges(index, type, player_id);
        cout << "orel" << check2 << endl;
        if (check1 && check2)
        {
            vertexes.at(0)[index] = player_id;
            vertexes.at(1)[index] = type;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    bool Tiles::check_roads_set_vertex(int index, int type, int player_id)
    {
        cout << "Entering check_roads_set_vertex with index: " << index << endl;
        try
        {
            if (index == 0)
            {
                cout << "Checking index 0" << endl;
                bool check_first_side = (vertexes.at(0).at(0) != player_id && vertexes.at(0).at(0) != 0) ||
                                        (vertexes.at(0).at(5) != player_id && vertexes.at(0).at(5) != 0);
                bool check_second_side = check_first_side;

                try
                {
                    if (getneighborhood().at(0) != nullptr)
                    {
                        check_first_side = check_first_side || (getneighborhood().at(0)->getvertex().at(0).at(1) != player_id && getneighborhood().at(0)->getvertex().at(0).at(1) != 0);
                    }
                    cout << "Checked getneighborhood() for check_first_side at index 0" << endl;
                }
                catch (const exception &e)
                {
                    cerr << "Error in check_first_side: " << e.what() << "\n";
                    check_first_side = true; // Assume failure if exception occurs
                }

                try
                {
                    if (getneighborhood().at(1) != nullptr)
                    {
                        check_second_side = check_second_side || (getneighborhood().at(1)->getvertex().at(0).at(5) != player_id && getneighborhood().at(1)->getvertex().at(0).at(5) != 0);
                    }
                    cout << "Checked getneighborhood() for check_second_side at index 0" << endl;
                }
                catch (const exception &e)
                {
                    cerr << "Error in check_second_side: " << e.what() << "\n";
                    check_second_side = true; // Assume failure if exception occurs
                }

                if (check_first_side || check_second_side)
                {
                    return false;
                }
                return true;
            }
            else if (index == 1)
            {
                cout << "Checking index 1" << endl;
                bool check_first_side = (vertexes.at(0).at(1) != player_id && vertexes.at(0).at(1) != 0) ||
                                        (vertexes.at(0).at(0) != player_id && vertexes.at(0).at(0) != 0);
                bool check_second_side = check_first_side;

                try
                {
                    if (getneighborhood().at(1) != nullptr)
                    {
                        check_first_side = check_first_side || (getneighborhood().at(1)->getvertex().at(0).at(3) != player_id && getneighborhood().at(1)->getvertex().at(0).at(3) != 0);
                    }
                    cout << "Checked getneighborhood() for check_first_side at index 1" << endl;
                }
                catch (const exception &e)
                {
                    cerr << "Error in check_first_side: " << e.what() << "\n";
                    check_first_side = true; // Assume failure if exception occurs
                }

                try
                {
                    if (getneighborhood().at(2) != nullptr)
                    {
                        check_second_side = check_second_side || (getneighborhood().at(2)->getvertex().at(0).at(5) != player_id && getneighborhood().at(2)->getvertex().at(0).at(5) != 0);
                    }
                    cout << "Checked getneighborhood() for check_second_side at index 1" << endl;
                }
                catch (const exception &e)
                {
                    cerr << "Error in check_second_side: " << e.what() << "\n";
                    check_second_side = true; // Assume failure if exception occurs
                }

                if (check_first_side || check_second_side)
                {
                    return false;
                }
                return true;
            }
            else if (index == 2)
            {
                cout << "Checking index 2" << endl;
                bool check_first_side = (vertexes.at(0).at(2) != player_id && vertexes.at(0).at(2) != 0) ||
                                        (vertexes.at(0).at(1) != player_id && vertexes.at(0).at(1) != 0);
                bool check_second_side = check_first_side;

                try
                {
                    if (getneighborhood().at(2) != nullptr)
                    {
                        check_first_side = check_first_side || (getneighborhood().at(2)->getvertex().at(0).at(4) != player_id && getneighborhood().at(2)->getvertex().at(0).at(4) != 0);
                    }
                    cout << "Checked getneighborhood() for check_first_side at index 2" << endl;
                }
                catch (const exception &e)
                {
                    cerr << "Error in check_first_side: " << e.what() << "\n";
                    check_first_side = true; // Assume failure if exception occurs
                }

                try
                {
                    if (getneighborhood().at(3) != nullptr)
                    {
                        check_second_side = check_second_side || (getneighborhood().at(3)->getvertex().at(0).at(0) != player_id && getneighborhood().at(3)->getvertex().at(0).at(0) != 0);
                    }
                    cout << "Checked getneighborhood() for check_second_side at index 2" << endl;
                }
                catch (const exception &e)
                {
                    cerr << "Error in check_second_side: " << e.what() << "\n";
                    check_second_side = true; // Assume failure if exception occurs
                }

                if (check_first_side || check_second_side)
                {
                    return false;
                }
                return true;
            }
            else if (index == 3)
            {
                cout << "Checking index 3" << endl;
                bool check_first_side = (vertexes.at(0).at(3) != player_id && vertexes.at(0).at(3) != 0) ||
                                        (vertexes.at(0).at(2) != player_id && vertexes.at(0).at(2) != 0);
                bool check_second_side = check_first_side;

                try
                {
                    if (getneighborhood().at(3) != nullptr)
                    {
                        check_first_side = check_first_side || (getneighborhood().at(3)->getvertex().at(0).at(5) != player_id && getneighborhood().at(3)->getvertex().at(0).at(5) != 0);
                    }
                    cout << "Checked getneighborhood() for check_first_side at index 3" << endl;
                }
                catch (const exception &e)
                {
                    cerr << "Error in check_first_side: " << e.what() << "\n";
                    check_first_side = true; // Assume failure if exception occurs
                }

                try
                {
                    if (getneighborhood().at(4) != nullptr)
                    {
                        check_second_side = check_second_side || (getneighborhood().at(4)->getvertex().at(0).at(1) != player_id && getneighborhood().at(4)->getvertex().at(0).at(1) != 0);
                    }
                    cout << "Checked getneighborhood() for check_second_side at index 3" << endl;
                }
                catch (const exception &e)
                {
                    cerr << "Error in check_second_side: " << e.what() << "\n";
                    check_second_side = true; // Assume failure if exception occurs
                }

                if (check_first_side || check_second_side)
                {
                    return false;
                }
                return true;
            }
            else if (index == 4)
            {
                cout << "Checking index 4" << endl;
                bool check_first_side = (vertexes.at(0).at(4) != player_id && vertexes.at(0).at(4) != 0) ||
                                        (vertexes.at(0).at(3) != player_id && vertexes.at(0).at(3) != 0);
                bool check_second_side = check_first_side;

                try
                {
                    if (getneighborhood().at(4) != nullptr)
                    {
                        check_first_side = check_first_side || (getneighborhood().at(4)->getvertex().at(0).at(0) != player_id && getneighborhood().at(4)->getvertex().at(0).at(0) != 0);
                    }
                    cout << "Checked getneighborhood() for check_first_side at index 4" << endl;
                }
                catch (const exception &e)
                {
                    cerr << "Error in check_first_side: " << e.what() << "\n";
                    check_first_side = true; // Assume failure if exception occurs
                }

                try
                {
                    if (getneighborhood().at(5) != nullptr)
                    {
                        check_second_side = check_second_side || (getneighborhood().at(5)->getvertex().at(0).at(2) != player_id && getneighborhood().at(5)->getvertex().at(0).at(2) != 0);
                    }
                    cout << "Checked getneighborhood() for check_second_side at index 4" << endl;
                }
                catch (const exception &e)
                {
                    cerr << "Error in check_second_side: " << e.what() << "\n";
                    check_second_side = true; // Assume failure if exception occurs
                }

                if (check_first_side || check_second_side)
                {
                    return false;
                }
                return true;
            }
            else if (index == 5)
            {
                cout << "Checking index 5" << endl;
                bool check_first_side = (vertexes.at(0).at(5) != player_id && vertexes.at(0).at(5) != 0) ||
                                        (vertexes.at(0).at(4) != player_id && vertexes.at(0).at(4) != 0);
                bool check_second_side = check_first_side;

                try
                {
                    if (getneighborhood().at(5) != nullptr)
                    {
                        check_first_side = check_first_side || (getneighborhood().at(5)->getvertex().at(0).at(1) != player_id && getneighborhood().at(5)->getvertex().at(0).at(1) != 0);
                    }
                    cout << "Checked getneighborhood() for check_first_side at index 5" << endl;
                }
                catch (const exception &e)
                {
                    cerr << "Error in check_first_side: " << e.what() << "\n";
                    check_first_side = true; // Assume failure if exception occurs
                }

                try
                {
                    if (getneighborhood().at(0) != nullptr)
                    {
                        check_second_side = check_second_side || (getneighborhood().at(0)->getvertex().at(0).at(3) != player_id && getneighborhood().at(0)->getvertex().at(0).at(3) != 0);
                    }
                    cout << "Checked getneighborhood() for check_second_side at index 5" << endl;
                }
                catch (const exception &e)
                {
                    cerr << "Error in check_second_side: " << e.what() << "\n";
                    check_second_side = true; // Assume failure if exception occurs
                }

                if (check_first_side || check_second_side)
                {
                    return false;
                }
                return true;
            }
        }
        catch (const exception &e)
        {
            cerr << "Error in outer try block: " << e.what() << "\n";
            return false;
        }
        return false; // Default return value in case index does not match any condition
    }

    bool Tiles::check_edges(int index, int type, int player_id)
    {
        try
        {
            if (index == 0)
            {
                bool check_first_side = (edges.at(0) != player_id && edges.at(0) != 0) ||
                                        (edges.at(5) != player_id && edges.at(5) != 0);
                bool check_second_side = check_first_side;

                try
                {
                    if (getneighborhood().at(0) != nullptr)
                    {
                        check_first_side = check_first_side || (getneighborhood().at(0)->getedges().at(1) != player_id && getneighborhood().at(0)->getedges().at(1) != 0);
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << '\n';
                    check_first_side = true; // Assume failure if exception occurs
                }

                try
                {
                    if (getneighborhood().at(1) != nullptr)
                    {
                        check_second_side = check_second_side || (getneighborhood().at(1)->getedges().at(5) != player_id && getneighborhood().at(1)->getedges().at(5) != 0);
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << '\n';
                    check_second_side = true; // Assume failure if exception occurs
                }

                if (check_first_side || check_second_side)
                {
                    return false;
                }
                return true;
            }
            else if (index == 1)
            {
                bool check_first_side = (edges.at(1) != player_id && edges.at(1) != 0) ||
                                        (edges.at(0) != player_id && edges.at(0) != 0);
                bool check_second_side = check_first_side;

                try
                {
                    if (getneighborhood().at(1) != nullptr)
                    {
                        check_first_side = check_first_side || (getneighborhood().at(1)->getedges().at(3) != player_id && getneighborhood().at(1)->getedges().at(3) != 0);
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << '\n';
                    check_first_side = true; // Assume failure if exception occurs
                }

                try
                {
                    if (getneighborhood().at(2) != nullptr)
                    {
                        check_second_side = check_second_side || (getneighborhood().at(2)->getedges().at(5) != player_id && getneighborhood().at(2)->getedges().at(5) != 0);
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << '\n';
                    check_second_side = true; // Assume failure if exception occurs
                }

                if (check_first_side || check_second_side)
                {
                    return false;
                }
                return true;
            }
            else if (index == 2)
            {
                bool check_first_side = (edges.at(2) != player_id && edges.at(2) != 0) ||
                                        (edges.at(1) != player_id && edges.at(1) != 0);
                bool check_second_side = check_first_side;

                try
                {
                    if (getneighborhood().at(2) != nullptr)
                    {
                        check_first_side = check_first_side || (getneighborhood().at(2)->getedges().at(4) != player_id && getneighborhood().at(2)->getedges().at(4) != 0);
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << '\n';
                    check_first_side = true; // Assume failure if exception occurs
                }

                try
                {
                    if (getneighborhood().at(3) != nullptr)
                    {
                        check_second_side = check_second_side || (getneighborhood().at(3)->getedges().at(0) != player_id && getneighborhood().at(3)->getedges().at(0) != 0);
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << '\n';
                    check_second_side = true; // Assume failure if exception occurs
                }

                if (check_first_side || check_second_side)
                {
                    return false;
                }
                return true;
            }
            else if (index == 3)
            {
                bool check_first_side = (edges.at(3) != player_id && edges.at(3) != 0) ||
                                        (edges.at(2) != player_id && edges.at(2) != 0);
                bool check_second_side = check_first_side;

                try
                {
                    if (getneighborhood().at(3) != nullptr)
                    {
                        check_first_side = check_first_side || (getneighborhood().at(3)->getedges().at(5) != player_id && getneighborhood().at(3)->getedges().at(5) != 0);
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << '\n';
                    check_first_side = true; // Assume failure if exception occurs
                }

                try
                {
                    if (getneighborhood().at(4) != nullptr)
                    {
                        check_second_side = check_second_side || (getneighborhood().at(4)->getedges().at(1) != player_id && getneighborhood().at(4)->getedges().at(1) != 0);
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << '\n';
                    check_second_side = true; // Assume failure if exception occurs
                }

                if (check_first_side || check_second_side)
                {
                    return false;
                }
                return true;
            }
            else if (index == 4)
            {
                bool check_first_side = (edges.at(4) != player_id && edges.at(4) != 0) ||
                                        (edges.at(3) != player_id && edges.at(3) != 0);
                bool check_second_side = check_first_side;

                try
                {
                    if (getneighborhood().at(4) != nullptr)
                    {
                        check_first_side = check_first_side || (getneighborhood().at(4)->getedges().at(0) != player_id && getneighborhood().at(4)->getedges().at(0) != 0);
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << '\n';
                    check_first_side = true; // Assume failure if exception occurs
                }

                try
                {
                    if (getneighborhood().at(5) != nullptr)
                    {
                        check_second_side = check_second_side || (getneighborhood().at(5)->getedges().at(2) != player_id && getneighborhood().at(5)->getedges().at(2) != 0);
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << '\n';
                    check_second_side = true; // Assume failure if exception occurs
                }

                if (check_first_side || check_second_side)
                {
                    return false;
                }
                return true;
            }
            else if (index == 5)
            {
                bool check_first_side = (edges.at(5) != player_id && edges.at(5) != 0) ||
                                        (edges.at(4) != player_id && edges.at(4) != 0);
                bool check_second_side = check_first_side;

                try
                {
                    if (getneighborhood().at(5) != nullptr)
                    {
                        check_first_side = check_first_side || (getneighborhood().at(5)->getedges().at(1) != player_id && getneighborhood().at(5)->getedges().at(1) != 0);
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << '\n';
                    check_first_side = true; // Assume failure if exception occurs
                }

                try
                {
                    if (getneighborhood().at(0) != nullptr)
                    {
                        check_second_side = check_second_side || (getneighborhood().at(0)->getedges().at(3) != player_id && getneighborhood().at(0)->getedges().at(3) != 0);
                    }
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << '\n';
                    check_second_side = true; // Assume failure if exception occurs
                }

                if (check_first_side || check_second_side)
                {
                    return false;
                }
                return true;
            }
        }
        catch (const exception &e)
        {
            cerr << "Error: " << e.what() << '\n';
            return false;
        }
        return false; // Default return value in case index does not match any condition
    }

    void Tiles::display() const
    {
        cout << "Tiles ID: " << id << endl;
        cout << "Value Roll: " << value_roll << endl;
        cout << "Type: " << type << endl;
        cout << "Edges: ";
        for (int i = 0; i < 6; ++i)
        {
            cout << edges[i] << " ";
        }
        cout << endl;
        cout << "Vertexes: ";
        for (int i = 0; i < 6; ++i)
        {
            cout << vertexes.at(0)[i] << " ";
        }
        cout << endl;
        cout << "Neighborhood: ";
        for (int i = 0; i < 6; ++i)
        {
            if (neighbors[i])
            {
                cout << neighbors[i]->getid() << " ";
            }
            else
            {
                cout << "0 ";
            }
        }
        cout << endl;
    }

bool Tiles::set_first_round_vertex(player &player, int &index)
{
    // Set initial vertex where index is the vertex number
    if (index < 0 || index >= 7)
    {
        cerr << "Index out of bounds." << endl;
        return false;
    }
    if (vertexes.at(0)[index] == 0)
    { // Check if the vertex is empty
        vertexes.at(0)[index] = player.getid(); // Set player ID
        vertexes.at(1)[index] = 1;
        string settlement_path = "the Tiles " + to_string(this->id) + " put settlement in vertex " + to_string(index) + "\n";
        // Set initial building type (settlement)
        player.add_settlement(settlement_path);

        // Check and print available positions for setting roads
        vector<int> available_positions;
        if (edges[index] == 0)
            available_positions.push_back(index);
        if (edges[(index + 1) % 6] == 0)
            available_positions.push_back((index + 1) % 6);
        
        int neighbor1_index = (index + 1) % 6;
        int neighbor2_index = (6 + index - 2) % 6;
        Tiles* neighbor1 = nullptr;
        Tiles* neighbor2 = nullptr;
        try
        {
            neighbor1 = getneighborhood().at(neighbor1_index);
        }
        catch (const out_of_range&) {}
        try
        {
            neighbor2 = getneighborhood().at(neighbor2_index);
        }
        catch (const out_of_range&) {}

        if (neighbor1 && neighbor1->getedges().at(neighbor2_index) == 0)
            available_positions.push_back(7); // Adding option 7 for neighbor

        // Print available positions
        cout << "You can add a road at the following positions: ";
        for (size_t i = 0; i < available_positions.size(); ++i)
        {
            if (available_positions[i] == 7)
                cout << "Press 7 to set at neighbor Tiles " << neighbor1->getid() << " at road " << neighbor2_index;
            else
                cout << available_positions[i];
            if (i < available_positions.size() - 1)
                cout << ", ";
        }
        cout << endl;

        // Get user's choice
        int road_index;
        bool valid_choice = false;
        while (!valid_choice)
        {
            cin >> road_index;
            if (find(available_positions.begin(), available_positions.end(), road_index) != available_positions.end())
            {
                valid_choice = true;
            }
            else
            {
                cout << "Invalid choice. Please choose from the available positions: ";
                for (size_t i = 0; i < available_positions.size(); ++i)
                {
                    if (available_positions[i] == 7)
                        cout << "Press 7 to set at neighbor Tiles " << neighbor1->getid() << " at road " << neighbor2_index;
                    else
                        cout << available_positions[i];
                    if (i < available_positions.size() - 1)
                        cout << ", ";
                }
                cout << endl;
            }
        }

        // Set the road based on the user's valid choice
        if (road_index == 7)
        {
            neighbor1->getedges().at(neighbor2_index) = player.getid();
            string road_path = "the Tiles " + to_string(neighbor1->getid()) + " put road in edge " + to_string(neighbor2_index) + "\n";
            player.add_road(road_path);
        }
        else
        {
            edges[road_index] = player.getid(); // Assign road to player
            string road_path = "the Tiles " + to_string(this->id) + " put road in edge " + to_string(road_index) + "\n";
            player.add_road(road_path);
        }
        player.add_points(1);
        return true;
    }
    else
    {
        cerr << "Vertex is already occupied." << endl;
        return false;
    }
}




    bool Tiles::set_first_round_edge(player &p1, int &index)
    {
        if (index < 0 || index >= 7)
        {
            cerr << "Index out of bounds." << endl;
            return false;
        }
        if (edges[index] == 0)
        {                              // Check if the edge is empty
            edges[index] = p1.getid(); // Assign road to player
            string path = "the Tiles " + to_string(this->id) + " put road in edge " + to_string(index) + "\n";
            p1.add_road(path);
            return true;
        }
        else
        {
            cerr << "Edge is already occupied." << endl;
            return false;
        }
    }

    void Tiles::set_neighbor(Tiles &neighbor, int index)
    {
        if (index >= 0 && index < 6)
        {
            neighbors[index] = &neighbor;
        }
    }

    bool Tiles::operator==(const Tiles &other) const
    {
        return id == other.id && value_roll == other.value_roll && type == other.type &&
               edges == other.edges && vertexes == other.vertexes;
    }

    Tiles &Tiles::operator=(const Tiles &other)
    {
        if (this == &other)
            return *this;
        id = other.id;
        value_roll = other.value_roll;
        type = other.type;
        edges = other.edges;
        vertexes = other.vertexes;
        for (int i = 0; i < 6; ++i)
        {
            neighbors[i] = other.neighbors[i];
        }
        return *this;
    }
    void Tiles::update_collision(int index, int id, int type)
    {
        for (int i : {index % 6, (index + 1) % 6})
        {
            if (neighbors[i])
            {
                if (i == index % 6)
                {
                    neighbors[i]->vertexes.at(0)[(index + 2) % 6] = id;
                    neighbors[i]->vertexes.at(1)[(index + 2) % 6] = type;
                }
                if (i == (index + 1) % 6)
                {
                    neighbors[i]->vertexes.at(0)[(index + 4) % 6] = id;
                    neighbors[i]->vertexes.at(1)[(index + 4) % 6] = type;
                }
            }
        }
    }
}
