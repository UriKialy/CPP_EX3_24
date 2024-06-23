#include "board.hpp"
#include <cstdlib>
using namespace std;

namespace ariel {
    board::board() // constructor for the board
    {
        vector<int> number_roll = {5, 2, 6, 3, 8, 10, 9, 12, 11, 7, 4, 8, 10, 9, 11, 3, 4, 5, 6};
        vector<string> typeVector = {"Wheat", "Wood", "Brick", "wool", "Wood", "Brick", "Wheat", "steel", "wool", "Desert", "steel",
                                     "Wood", "Wheat", "Wood", "Wheat", "wool", "Wood", "steel", "wool"};
        vector<int> idVector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

        for (int i = 0; i < 19; i++) {
            tiles.emplace_back(Tiles(idVector[i], number_roll[i], typeVector[i]));
        }

        // set all the neighbors
        tiles[0].set_neighbor(tiles[1], 0);
        tiles[0].set_neighbor(tiles[3], 3);
        tiles[0].set_neighbor(tiles[4], 4);
        tiles[0].set_neighbor(tiles[1], 5);
        tiles[1].set_neighbor(tiles[0], 2);
        tiles[1].set_neighbor(tiles[4], 3);
        tiles[1].set_neighbor(tiles[5], 4);
        tiles[1].set_neighbor(tiles[2], 5);
        tiles[2].set_neighbor(tiles[1], 2);
        tiles[2].set_neighbor(tiles[5], 3);
        tiles[2].set_neighbor(tiles[6], 4);
        tiles[3].set_neighbor(tiles[7], 3);
        tiles[3].set_neighbor(tiles[8], 4);
        tiles[3].set_neighbor(tiles[4], 5);
        tiles[4].set_neighbor(tiles[1], 0);
        tiles[4].set_neighbor(tiles[0], 1);
        tiles[4].set_neighbor(tiles[3], 2);
        tiles[4].set_neighbor(tiles[8], 3);
        tiles[4].set_neighbor(tiles[9], 4);
        tiles[4].set_neighbor(tiles[5], 5);
        tiles[5].set_neighbor(tiles[2], 0);
        tiles[5].set_neighbor(tiles[1], 1);
        tiles[5].set_neighbor(tiles[4], 2);
        tiles[5].set_neighbor(tiles[9], 3);
        tiles[5].set_neighbor(tiles[10], 4);
        tiles[5].set_neighbor(tiles[6], 5);
        tiles[6].set_neighbor(tiles[2], 1);
        tiles[6].set_neighbor(tiles[5], 2);
        tiles[6].set_neighbor(tiles[10], 3);
        tiles[6].set_neighbor(tiles[11], 4);
        tiles[7].set_neighbor(tiles[3], 0);
        tiles[7].set_neighbor(tiles[12], 4);
        tiles[7].set_neighbor(tiles[8], 5);
        tiles[8].set_neighbor(tiles[4], 0);
        tiles[8].set_neighbor(tiles[3], 1);
        tiles[8].set_neighbor(tiles[7], 2);
        tiles[8].set_neighbor(tiles[12], 3);
        tiles[8].set_neighbor(tiles[13], 4);
        tiles[8].set_neighbor(tiles[9], 5);
        tiles[9].set_neighbor(tiles[5], 0);
        tiles[9].set_neighbor(tiles[4], 1);
        tiles[9].set_neighbor(tiles[8], 2);
        tiles[9].set_neighbor(tiles[13], 3);
        tiles[9].set_neighbor(tiles[14], 4);
        tiles[9].set_neighbor(tiles[10], 5);
        tiles[10].set_neighbor(tiles[6], 0);
        tiles[10].set_neighbor(tiles[5], 1);
        tiles[10].set_neighbor(tiles[9], 2);
        tiles[10].set_neighbor(tiles[14], 3);
        tiles[10].set_neighbor(tiles[15], 4);
        tiles[10].set_neighbor(tiles[11], 5);
        tiles[11].set_neighbor(tiles[6], 1);
        tiles[11].set_neighbor(tiles[10], 2);
        tiles[11].set_neighbor(tiles[15], 3);
        tiles[12].set_neighbor(tiles[8], 0);
        tiles[12].set_neighbor(tiles[7], 1);
        tiles[12].set_neighbor(tiles[16], 4);
        tiles[12].set_neighbor(tiles[13], 5);
        tiles[13].set_neighbor(tiles[9], 0);
        tiles[13].set_neighbor(tiles[8], 1);
        tiles[13].set_neighbor(tiles[12], 2);
        tiles[13].set_neighbor(tiles[16], 3);
        tiles[13].set_neighbor(tiles[17], 4);
        tiles[13].set_neighbor(tiles[14], 5);
        tiles[14].set_neighbor(tiles[10], 0);
        tiles[14].set_neighbor(tiles[9], 1);
        tiles[14].set_neighbor(tiles[13], 2);
        tiles[14].set_neighbor(tiles[17], 3);
        tiles[14].set_neighbor(tiles[18], 4);
        tiles[14].set_neighbor(tiles[15], 5);
        tiles[15].set_neighbor(tiles[11], 0);
        tiles[15].set_neighbor(tiles[10], 1);
        tiles[15].set_neighbor(tiles[14], 2);
        tiles[15].set_neighbor(tiles[18], 3);
        tiles[16].set_neighbor(tiles[13], 0);
        tiles[16].set_neighbor(tiles[12], 1);
        tiles[16].set_neighbor(tiles[17], 5);
        tiles[17].set_neighbor(tiles[14], 0);
        tiles[17].set_neighbor(tiles[13], 1);
        tiles[17].set_neighbor(tiles[16], 2);
        tiles[17].set_neighbor(tiles[18], 5);
        tiles[18].set_neighbor(tiles[15], 0);
        tiles[18].set_neighbor(tiles[14], 1);
        tiles[18].set_neighbor(tiles[17], 2);
    }

    Tiles& board::getTile(int id) {
        cout << "Accessing tile with id: " << id << endl;
        int num = tiles.size();
        if (id < 0 || id >= num) {
            throw out_of_range("Tile id is out of range: " + to_string(id));
        }
        return tiles[id];
    }

    void board::print_board() {
        vector<string> board_representation(7, string(35, ' '));

        auto format_tile = [](const string &type, int roll) {
            return type + " " + (roll == 0 ? "  " : (roll < 10 ? " " + to_string(roll) : to_string(roll)));
        };

        board_representation[0] = "       sea   sea   sea   sea   sea       ";
        board_representation[1] = "    sea " + format_tile(tiles[0].gettype(), tiles[0].getvalue_roll()) + " " + format_tile(tiles[1].gettype(), tiles[1].getvalue_roll()) + " " + format_tile(tiles[2].gettype(), tiles[2].getvalue_roll()) + " sea ";
        board_representation[2] = "  sea " + format_tile(tiles[3].gettype(), tiles[3].getvalue_roll()) + " " + format_tile(tiles[4].gettype(), tiles[4].getvalue_roll()) + " " + format_tile(tiles[5].gettype(), tiles[5].getvalue_roll()) + " " + format_tile(tiles[6].gettype(), tiles[6].getvalue_roll()) + " sea";
        board_representation[3] = "sea " + format_tile(tiles[7].gettype(), tiles[7].getvalue_roll()) + " " + format_tile(tiles[8].gettype(), tiles[8].getvalue_roll()) + " " + format_tile(tiles[9].gettype(), tiles[9].getvalue_roll()) + " " + format_tile(tiles[18].gettype(), tiles[18].getvalue_roll()) + " " + format_tile(tiles[10].gettype(), tiles[10].getvalue_roll()) + " sea";
        board_representation[4] = "  sea " + format_tile(tiles[11].gettype(), tiles[11].getvalue_roll()) + " " + format_tile(tiles[12].gettype(), tiles[12].getvalue_roll()) + " " + format_tile(tiles[13].gettype(), tiles[13].getvalue_roll()) + " " + format_tile(tiles[14].gettype(), tiles[14].getvalue_roll()) + " sea";
        board_representation[5] = "    sea " + format_tile(tiles[15].gettype(), tiles[15].getvalue_roll()) + " " + format_tile(tiles[16].gettype(), tiles[16].getvalue_roll()) + " " + format_tile(tiles[17].gettype(), tiles[17].getvalue_roll()) + " sea ";
        board_representation[6] = "       sea   sea   sea   sea   sea       ";

        cout << "************ CATAN BOARD ************\n";
        for (const auto &line : board_representation) {
            cout << line << endl;
        }
        cout << "*************************************\n";
    }
}


