

#include "player.hpp"
#include <vector>
#include <iostream>
#include "board.hpp"
#include "Tiles.hpp"

using namespace std;
namespace ariel {
    class Catan {
    private:
        std::vector<player> Player_arr; // Ensure Player_arr is std::vector
        board game_board;
        int turn;

    public:
        // Constructor that initializes the players
        Catan(const player& player1, const player& player2, const player& player3);
        
        // Method to display player information
        void displayPlayers() const;
        void ChooseStartingPlayer();
    };
}

