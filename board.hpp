#include "Tiles.hpp"
#pragma once
using namespace std;
namespace ariel
{
    class board
    {
        vector<Tiles> tiles;
        public:
        board();
        ~board()=default;
        Tiles get_tile(int id);
        string choseRandomType();
        int roll_dice();
        int choseRandomRole();
        void print_board();
        
    };
}