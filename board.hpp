#pragma once
#include "Tiles.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;
namespace ariel
{
    class Tiles;
    class board
    {
        vector<Tiles> tiles;

    public:
        board();
        ~board() = default;
        Tiles& getTile(int id);
        string choseRandomType();
        int choseRandomRole();
        void print_board();
    };
}