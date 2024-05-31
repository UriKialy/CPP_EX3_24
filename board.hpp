#include "Tiles.hpp"
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
    };
}