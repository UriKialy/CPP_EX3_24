#include "Tiles.hpp"
using namespace std;
namespace ariel {

Tiles::Tiles() : id(0), value_roll(0), type("") {
    this->edges = {0, 0, 0, 0, 0, 0};
    this->vertex = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    this->neighbors = {};
}

Tiles::Tiles(int id, int value_roll, const string& type) : id(id), value_roll(value_roll), type(type) {
    this->edges = {0, 0, 0, 0, 0, 0};
    this->vertex = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    this->neighbors = {};
}

Tiles::Tiles(const Tiles& other) : id(other.id), value_roll(other.value_roll), type(other.type), edges(other.edges), vertex(other.vertex), neighbors(other.neighbors) {}

Tiles::~Tiles() {
    // No need to clear vectors as they are managed by the standard library
}

int Tiles::getid() const {
    return id;
}

int Tiles::getvalue_roll() const {
    return value_roll;
}

string Tiles::gettype() const {
    return type;
}

vector<int> Tiles::getedges() const {
    return edges;
}

vector<vector<int>> Tiles::getvertex() const {
    return vertex;
}

vector<Tiles> Tiles::getneighbors() const {
    return neighbors;
}

void Tiles::display_edges() const {
    for(int i = 0; i < edges.size(); i++) {
        cout << edges.at(i) << endl;
    }
}

void Tiles::display_vertex() const {
    for (const auto& v : vertex) {
        cout << "Player ID: " << v[0] << ", Type: " << v[1] << endl;
    }
}

int Tiles::setedges(int index, int id) {
    if (index < 0 || index > 5 || id < 1 || id > 3) {
        cout << "index out of range" << endl;
        return 0;
    }
    if (this->edges.at(index) != 0) {
        cout << "you can't build a road here because this place is taken" << endl;
        return 0;
    }

    if (set_special_edges(index, id) == 1) {
        return 1;
    }

    bool check_firstedge = false, check_neighbor_edges1 = false, check_neighbor_edges2 = false;

    try {
        if (neighbors.at((index + 1) % 6).getedges().at((index + 3) % 6) == 0) {
            check_firstedge = true;
        }
    } catch (const exception& e) {
        cout << "Error checking first edge: " << e.what() << endl;
        check_firstedge = true; // Assume failure if exception occurs
    }

    try {
        if (neighbors.at((index + 1) % 6).getedges().at((index + 2) % 6) == 0) {
            check_neighbor_edges1 = true;
        }
    } catch (const exception& e) {
        cout << "Error checking neighbor edge 1: " << e.what() << endl;
        check_neighbor_edges1 = true; // Assume failure if exception occurs
    }

    try {
        if (neighbors.at((index + 1) % 6).getedges().at((index + 4) % 6) == 0) {
            check_neighbor_edges2 = true;
        }
    } catch (const exception& e) {
        cout << "Error checking neighbor edge 2: " << e.what() << endl;
        check_neighbor_edges2 = true; // Assume failure if exception occurs
    }

    bool check_neighbor_edges = check_neighbor_edges1 || check_neighbor_edges2;
    if (check_firstedge || check_neighbor_edges || check_before_apply(index, id)) {
        return apply_edges(index, id);
    } else {
        cout << "you can't build a road here" << endl;
        return 0;
    }
}

int Tiles::check_before_apply(int index, int id) {
    bool is_edges_occuipied_by_player = this->edges.at((6 + index - 1) % 6) == id || this->edges.at((index + 1) % 6) == id;
    bool is_vertexes_occuiped_by_player = this->vertex.at((6 + index - 1) % 6).at(0) == id || this->vertex.at((index + 1) % 6).at(0) == id;
    return is_edges_occuipied_by_player || is_vertexes_occuiped_by_player;
}

int Tiles::set_special_edges(int index, int id) {
    bool check_upper = false, left_side = false, right_side = false, bottom = false;
    bool is_edges_occuipied_by_player = this->edges.at((6 + index - 1) % 6) == id || this->edges.at((index + 1) % 6) == id;
    int no_neighbors_edges[] = {0, 7, 10, 16, 18, 11, 2};
    for (int i = 0; i < 6; i++) {
        if (no_neighbors_edges[i] == this->id && index == i || is_edges_occuipied_by_player) {
            this->edges.at(index) = id;
            return 1;
        }
    }
    if (this->id < 3 && (index == 0 || index == 5)) {
        for (int i = 0; i < 2; i++) {
            if (this->id == i && index == 5) {
                try {
                    if (neighbors.at(5).getedges().at(0) == id || neighbors.at(5).getedges().at(1) == id) {
                        check_upper = true;
                    }
                } catch (const exception& e) {
                    cout << "Error checking upper edge: " << e.what() << endl;
                }
            }
        }
        if (index == 0 && (this->id == 1 || this->id == 2)) {
            try {
                if (neighbors.at(2).getedges().at(5) == id || neighbors.at(2).getedges().at(4) == id) {
                    check_upper = true;
                }
            } catch (const exception& e) {
                cout << "Error checking upper edge: " << e.what() << endl;
            }
        }
        if (check_before_apply(index, id) || check_upper) {
            return apply_edges(index, id);
        }
    }
    if ((index == 1 || index == 2 || index == 3) && (this->id == 0 || this->id == 3 || this->id == 7 || this->id == 12 || this->id == 16)) {
        if (this->id == 0 && index == 1) {
            if (this->edges.at(0) == id || this->edges.at(2) == id || neighbors.at(3).getedges().at(5) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        } else if ((this->id == 3 && index == 0) || (this->id == 7 && index == 0)) {
            if (this->edges.at(5) == id || this->edges.at(1) == id || neighbors.at(0).getedges().at(1) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        } else if (this->id == 3 && index == 1) {
            if (this->edges.at(2) == id || this->edges.at(0) == id || neighbors.at(3).getedges().at(0) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        } else if ((this->id == 7 && index == 2) || (this->id == 12 && index == 2)) {
            if (this->edges.at(3) == id || this->edges.at(1) == id || neighbors.at(3).getedges().at(1) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        } else if (this->id == 16 && index == 1) {
            if (this->edges.at(0) == id || this->edges.at(2) == id || neighbors.at(1).getedges().at(2) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        }
    }
    if (index == 16 || index == 17 || index == 18) {
        if (this->id == 16 && index == 3) {
            if (this->edges.at(2) == id || this->edges.at(4) == id || neighbors.at(5).getedges().at(2) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        } else if ((this->id == 17 && index == 2) || (this->id == 18 && index == 2)) {
            if (this->edges.at(1) == id || this->edges.at(3) == id || neighbors.at(2).getedges().at(3) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        } else if (this->id == 17 && index == 3) {
            if (this->edges.at(2) == id || this->edges.at(4) == id || neighbors.at(1).getedges().at(4) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        } else if (this->id == 18 && index == 3) {
            if (this->edges.at(2) == id || this->edges.at(4) == id || neighbors.at(0).getedges().at(4) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        }
    }
    if (index == 4 || index == 5) {
        if (this->id == 10 && index == 4) {
            if (this->edges.at(3) == id || this->edges.at(5) == id || neighbors.at(4).getedges().at(5) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        } else if (this->id == 11 && index == 5) {
            if (this->edges.at(0) == id || this->edges.at(4) == id || neighbors.at(1).getedges().at(4) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        } else if ((this->id == 11 && index == 3) || (this->id == 15 && index == 3)) {
            if (this->edges.at(2) == id || this->edges.at(4) == id || neighbors.at(3).getedges().at(4) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        } else if ((this->id == 15 && index == 4) || (this->id == 18 && index == 4)) {
            if (this->edges.at(3) == id || this->edges.at(5) == id || neighbors.at(0).getedges().at(3) == id || check_before_apply(index, id)) {
                return apply_edges(index, id);
            }
        }
    }

    return 0;
}

int Tiles::apply_edges(int index, int id) {
    this->edges.at(index) = id;
    try {
        if (neighbors.at((index + 1) % 6).getedges().at((index + 3) % 6) == 0) {
            neighbors.at((index + 1) % 6).edges.at((index + 3) % 6) = id;
        }
    } catch (const exception& e) {
        cout << "Error applying edge to neighbor: " << e.what() << endl;
    }
    return 1;
}

int Tiles::set_vertex(int index, int type, int player_id) {
    bool check1 = check_roads_set_vertex(index, type, player_id);
    bool check2 = check_edges(index, type, player_id);
    if (check1 && check2) {
        vertex[index][0] = player_id;
        vertex[index][1] = type;
        return 1;
    } else {
        return 0;
    }
}

bool Tiles::check_roads_set_vertex(int index, int type, int player_id) {
    try {
        if (index == 0) {
            bool check_first_side = (vertex[0][0] != player_id && vertex[0][0] != 0) || (vertex[5][0] != player_id && vertex[5][0] != 0);
            bool check_second_side = check_first_side;

            try {
                if (!neighbors.empty() && neighbors.at(0).vertex[0][1] != player_id && neighbors.at(0).vertex[0][1] != 0) {
                    check_first_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error in check_first_side: " << e.what() << "\n";
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (!neighbors.empty() && neighbors.at(1).vertex[0][5] != player_id && neighbors.at(1).vertex[0][5] != 0) {
                    check_second_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error in check_second_side: " << e.what() << "\n";
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 1) {
            bool check_first_side = (vertex[1][0] != player_id && vertex[1][0] != 0) || (vertex[0][0] != player_id && vertex[0][0] != 0);
            bool check_second_side = check_first_side;

            try {
                if (!neighbors.empty() && neighbors.at(1).vertex[0][3] != player_id && neighbors.at(1).vertex[0][3] != 0) {
                    check_first_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error in check_first_side: " << e.what() << "\n";
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (!neighbors.empty() && neighbors.at(2).vertex[0][5] != player_id && neighbors.at(2).vertex[0][5] != 0) {
                    check_second_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error in check_second_side: " << e.what() << "\n";
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 2) {
            bool check_first_side = (vertex[2][0] != player_id && vertex[2][0] != 0) || (vertex[1][0] != player_id && vertex[1][0] != 0);
            bool check_second_side = check_first_side;

            try {
                if (!neighbors.empty() && neighbors.at(2).vertex[0][4] != player_id && neighbors.at(2).vertex[0][4] != 0) {
                    check_first_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error in check_first_side: " << e.what() << "\n";
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (!neighbors.empty() && neighbors.at(3).vertex[0][0] != player_id && neighbors.at(3).vertex[0][0] != 0) {
                    check_second_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error in check_second_side: " << e.what() << "\n";
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 3) {
            bool check_first_side = (vertex[3][0] != player_id && vertex[3][0] != 0) || (vertex[2][0] != player_id && vertex[2][0] != 0);
            bool check_second_side = check_first_side;

            try {
                if (!neighbors.empty() && neighbors.at(3).vertex[0][5] != player_id && neighbors.at(3).vertex[0][5] != 0) {
                    check_first_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error in check_first_side: " << e.what() << "\n";
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (!neighbors.empty() && neighbors.at(4).vertex[0][1] != player_id && neighbors.at(4).vertex[0][1] != 0) {
                    check_second_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error in check_second_side: " << e.what() << "\n";
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 4) {
            bool check_first_side = (vertex[4][0] != player_id && vertex[4][0] != 0) || (vertex[3][0] != player_id && vertex[3][0] != 0);
            bool check_second_side = check_first_side;

            try {
                if (!neighbors.empty() && neighbors.at(4).vertex[0][0] != player_id && neighbors.at(4).vertex[0][0] != 0) {
                    check_first_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error in check_first_side: " << e.what() << "\n";
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (!neighbors.empty() && neighbors.at(5).vertex[0][2] != player_id && neighbors.at(5).vertex[0][2] != 0) {
                    check_second_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error in check_second_side: " << e.what() << "\n";
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 5) {
            bool check_first_side = (vertex[5][0] != player_id && vertex[5][0] != 0) || (vertex[4][0] != player_id && vertex[4][0] != 0);
            bool check_second_side = check_first_side;

            try {
                if (!neighbors.empty() && neighbors.at(5).vertex[0][1] != player_id && neighbors.at(5).vertex[0][1] != 0) {
                    check_first_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error in check_first_side: " << e.what() << "\n";
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (!neighbors.empty() && neighbors.at(0).vertex[0][3] != player_id && neighbors.at(0).vertex[0][3] != 0) {
                    check_second_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error in check_second_side: " << e.what() << "\n";
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        }
    } catch (const exception& e) {
        cerr << "Error in outer try block: " << e.what() << "\n";
        return false;
    }
    return false; // Default return value in case index does not match any condition
}

bool Tiles::check_edges(int index, int type, int player_id) {
    try {
        if (index == 0) {
            bool check_first_side = (edges[0] != player_id && edges[0] != 0) || (edges[5] != player_id && edges[5] != 0);
            bool check_second_side = check_first_side;

            try {
                if (!neighbors.empty() && neighbors.at(0).edges[1] != player_id && neighbors.at(0).edges[1] != 0) {
                    check_first_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (!neighbors.empty() && neighbors.at(1).edges[5] != player_id && neighbors.at(1).edges[5] != 0) {
                    check_second_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 1) {
            bool check_first_side = (edges[1] != player_id && edges[1] != 0) || (edges[0] != player_id && edges[0] != 0);
            bool check_second_side = check_first_side;

            try {
                if (!neighbors.empty() && neighbors.at(1).edges[3] != player_id && neighbors.at(1).edges[3] != 0) {
                    check_first_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (!neighbors.empty() && neighbors.at(2).edges[5] != player_id && neighbors.at(2).edges[5] != 0) {
                    check_second_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 2) {
            bool check_first_side = (edges[2] != player_id && edges[2] != 0) || (edges[1] != player_id && edges[1] != 0);
            bool check_second_side = check_first_side;

            try {
                if (!neighbors.empty() && neighbors.at(2).edges[4] != player_id && neighbors.at(2).edges[4] != 0) {
                    check_first_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (!neighbors.empty() && neighbors.at(3).edges[0] != player_id && neighbors.at(3).edges[0] != 0) {
                    check_second_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 3) {
            bool check_first_side = (edges[3] != player_id && edges[3] != 0) || (edges[2] != player_id && edges[2] != 0);
            bool check_second_side = check_first_side;

            try {
                if (!neighbors.empty() && neighbors.at(3).edges[5] != player_id && neighbors.at(3).edges[5] != 0) {
                    check_first_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (!neighbors.empty() && neighbors.at(4).edges[1] != player_id && neighbors.at(4).edges[1] != 0) {
                    check_second_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 4) {
            bool check_first_side = (edges[4] != player_id && edges[4] != 0) || (edges[3] != player_id && edges[3] != 0);
            bool check_second_side = check_first_side;

            try {
                if (!neighbors.empty() && neighbors.at(4).edges[0] != player_id && neighbors.at(4).edges[0] != 0) {
                    check_first_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (!neighbors.empty() && neighbors.at(5).edges[2] != player_id && neighbors.at(5).edges[2] != 0) {
                    check_second_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 5) {
            bool check_first_side = (edges[5] != player_id && edges[5] != 0) || (edges[4] != player_id && edges[4] != 0);
            bool check_second_side = check_first_side;

            try {
                if (!neighbors.empty() && neighbors.at(5).edges[1] != player_id && neighbors.at(5).edges[1] != 0) {
                    check_first_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (!neighbors.empty() && neighbors.at(0).edges[3] != player_id && neighbors.at(0).edges[3] != 0) {
                    check_second_side = true;
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return false;
    }
    return false; // Default return value in case index does not match any condition
}

void Tiles::display() const {
    cout << "Tile ID: " << id << endl;
    cout << "Value Roll: " << value_roll << endl;
    cout << "Type: " << type << endl;
    cout << "Edges: ";
    for (int i = 0; i < 6; ++i) {
        cout << edges[i] << " ";
    }
    cout << endl;
    cout << "Vertex: ";
    for (const auto& v : vertex) {
        cout << "(" << v[0] << ", " << v[1] << ") ";
    }
    cout << endl;
    cout << "Neighborhood: ";
    for (const auto& neighbor : neighbors) {
        cout << neighbor.getid() << " ";
    }
    cout << endl;
}

bool Tiles::set_first_round_vertex(player &player, int& index) {
    if (index < 0 || index >= 6) {
        cerr << "Index out of bounds." << endl;
        return false;
    }
    if (vertex[index][0] == 0) {
        vertex[index][0] = player.getid();
        vertex[index][1] = 1;
        string path = "the player set the vertex the player name " + player.getName() + "\n";
        player.add_settlement(path);
        return true;
    } else {
        cerr << "Vertex is already occupied." << endl;
        return false;
    }
}

bool Tiles::set_first_round_edge(player& p1, int &index) {
    if (index < 0 || index >= 6) {
        cerr << "Index out of bounds." << endl;
        return false;
    }
    if (edges[index] == 0) {
        edges[index] = p1.getid();
        string path = "the player " + p1.getName() + " put road in edge " + to_string(index) + "\n";
        p1.add_road(path);
        return true;
    } else {
        cerr << "Edge is already occupied." << endl;
        return false;
    }
}

void Tiles::set_neighbor(Tiles& neighbor, int index) {
    if (index >= 0 && index < 6) {
        neighbors[index] = neighbor;
    }
}

bool Tiles::operator==(const Tiles& other) const {
    return id == other.id && value_roll == other.value_roll && type == other.type && edges == other.edges && vertex == other.vertex;
}

Tiles& Tiles::operator=(const Tiles& other) {
    if (this == &other) return *this;
    id = other.id;
    value_roll = other.value_roll;
    type = other.type;
    edges = other.edges;
    vertex = other.vertex;
    neighbors = other.neighbors;
    return *this;
}

void Tiles::update_collision(int index, int id, int type) {
    for (int i : {index % 6, (index + 1) % 6}) {
        if (neighbors[i]) {
            if (i == index % 6) {
                neighbors[i].vertex[(index + 2) % 6][0] = id;
                neighbors[i].vertex[(index + 2) % 6][1] = type;
            }
            if (i == (index + 1) % 6) {
                neighbors[i].vertex[(index + 4) % 6][0] = id;
                neighbors[i].vertex[(index + 4) % 6][1] = type;
            }
        }
    }
}
} // namespace ariel