#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace ariel
{
    class Tiles
    {
        string type;
        int id;
        int value_role;             // 2-12
        vector<int> edges;          // the index is the edge and the value is the player id
        vector<vector<int>> vertex; // the first element is the player id and the second is city/subberb
        vector<Tiles> neighbors{6};

    public:
        ~Tiles()=default;
        Tiles(string type, int id, int value_role);
        int set_edge(int edge, int player_id);
        int set_vertex(int index, int type, int player_id); // 0 for city 1 for suburb
        int set_neighbor(Tiles &neighbor, int index);
        vector<int> get_edges();
        vector<vector<int>> get_vertex();
        string get_type() const;
        int get_id() const;
        vector<Tiles> get_neighbors();
        string get_yeild() const;
        int get_value_role() const;
        Tiles get_tile(string id) const; // if we want to get a tile by its id
        Tiles &operator=(const Tiles &other);
        bool operator==(const Tiles &other);
        bool operator!=(const Tiles &other);
    };
}
