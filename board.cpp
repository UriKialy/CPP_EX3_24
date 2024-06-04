#include "board.hpp"
#include <cstdlib>
using namespace std;
namespace ariel
{

    board::board()//constructor for the board
    {
        vector<Tiles> tiles(19);
        for (int i = 0; i < 19; i++)
        {
            if (i != 9)
            {
                tiles.at(i) = Tiles(choseRandomType(), i, choseRandomRole());
            }
        }
        tiles.at(9) = Tiles(" desert", 0, rand() % 11 + 2);
        //set all the neighbors
        tiles.at(0).set_neighbor(tiles.at(1), 0);
        tiles[0].set_neighbor(tiles[3],3);
         tiles[0].set_neighbor(tiles[4],4);
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
        //desetrt 9
        tiles[9].set_neighbor(tiles[5],0);
        tiles[9].set_neighbor(tiles[4],1);
        tiles[9].set_neighbor(tiles[8],2);
        tiles[9].set_neighbor(tiles[13],3);
        tiles[9].set_neighbor(tiles[14],4);
        tiles[9].set_neighbor(tiles[10],5);
        tiles[10].set_neighbor(tiles[6],0);
        tiles[10].set_neighbor(tiles[5],1);
        tiles[10].set_neighbor(tiles[9],2);
        tiles[10].set_neighbor(tiles[14],3);
        tiles[10].set_neighbor(tiles[15],4);
        tiles[10].set_neighbor(tiles[11],5);
        tiles[11].set_neighbor(tiles[6],1);
        tiles[11].set_neighbor(tiles[10],2);
        tiles[11].set_neighbor(tiles[15],3);
        tiles[12].set_neighbor(tiles[8],0);
        tiles[12].set_neighbor(tiles[7],1);
        tiles[12].set_neighbor(tiles[16],4);
        tiles[12].set_neighbor(tiles[13],5);
        tiles[13].set_neighbor(tiles[9],0);
        tiles[13].set_neighbor(tiles[8],1);
        tiles[13].set_neighbor(tiles[12],2);
        tiles[13].set_neighbor(tiles[16],3);
        tiles[13].set_neighbor(tiles[17],4);
        tiles[13].set_neighbor(tiles[14],5);
        tiles[14].set_neighbor(tiles[10],0);
        tiles[14].set_neighbor(tiles[9],1);
        tiles[14].set_neighbor(tiles[13],2);
        tiles[14].set_neighbor(tiles[17],3);
        tiles[14].set_neighbor(tiles[18],4);
        tiles[14].set_neighbor(tiles[15],5);
        tiles[15].set_neighbor(tiles[11],0);
        tiles[15].set_neighbor(tiles[10],1);
        tiles[15].set_neighbor(tiles[14],2);
        tiles[15].set_neighbor(tiles[18],3);
        tiles[16].set_neighbor(tiles[13],0);
        tiles[16].set_neighbor(tiles[12],1);
        tiles[16].set_neighbor(tiles[17],5);
        tiles[17].set_neighbor(tiles[14],0);
        tiles[17].set_neighbor(tiles[13],1);
        tiles[17].set_neighbor(tiles[16],2);
        tiles[17].set_neighbor(tiles[18],5);
        tiles[18].set_neighbor(tiles[15],0);
        tiles[18].set_neighbor(tiles[14],1);
        tiles[18].set_neighbor(tiles[17],2);

    }
    int board::choseRandomRole()//randomly choose a role for the tile between 2-12 while all the numbers will be chosen
    {
        bool chosen = false;
        int role;
        do {
            role = rand() % 11 + 2;//set number between 2-12
            chosen = true;
            for(int i=0;i<19;i++){
            if(tiles.at(i).get_value_role()==role){//check if the number is already chosen
                chosen=false;
                break;
            }
            }
        } while (!chosen);//if the number is already chosen choose another one
        return role;
    }
    string board::choseRandomType()//randomly choose a type of tile
    {
        int forest = 0;
        int hill = 0;
        int mountain = 0;
        int agrictulture_land = 0;
        int pastureland = 0;
        for (int i = 0; i < 19; i++)
        {
            if (tiles.at(i).get_type() == "forest")
            {
                forest++;
            }
            else if (tiles.at(i).get_type() == "hill")
            {
                hill++;
            }
            else if (tiles.at(i).get_type() == "mountain")
            {
                mountain++;
            }
            else if (tiles.at(i).get_type() == "agrictulture_land")
            {
                agrictulture_land++;
            }
            else
            {
                pastureland++;
            }
        }
        int random = rand() % 5;
        if (random == 0 && forest < 4)
        {
            return "forest";
        }
        else if (random == 1 && hill < 4)
        {
            return "hill";
        }
        else if (random == 2 && mountain < 4)
        {
            return "mountain";
        }
        else if (random == 3 && agrictulture_land < 4)
        {
            return "agrictulture_land";
        }
        else if (pastureland < 4)
        {
            return "pastureland";
        }
    }
    int board::roll_dice()
    {
        return rand() % 11 + 2;
    }
    // Tiles board::get_tile(int id)
    //     {    
    //         return
    //     }
}