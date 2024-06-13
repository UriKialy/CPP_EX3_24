#include <iostream>
#include <string>
#include "player.hpp"
#include "board.hpp"
#include "resourceCard.hpp"
#include "developeCard.hpp"
#include "abundanceCard.hpp"
#include "road_building.hpp"
#include "monopolyCard.hpp"
#include "knights.hpp"
#include "victoryCard.hpp"
#include "catan.hpp"

using namespace std;

namespace ariel {

void initialize_game(player &p1, player &p2, player &p3, board &b);
void print_menu();

int main() {
    player p1("Orel");
    cout << p1.getName() << endl; // should print Orel
    player p2("Nir");
    cout << p2.getName() << endl; // should print Nir
    player p3("Amit");
    cout << p3.getName() << endl; // should print Amit

    board b;
    b.print_board();

    resourceCard r1("Wood");
    resourceCard r2("Brick");
    resourceCard r3("Sheep");
    resourceCard r4("Wheat");
    resourceCard r5("Clay");
    resourceCard r6("Wood");
    resourceCard r7("Brick");
    resourceCard r8("Sheep");
    resourceCard r9("Wheat");
    resourceCard r10("Clay");
    resourceCard r11("Wood");
    resourceCard r12("Brick");
    resourceCard r13("Sheep");
    resourceCard r14("Wheat");
    resourceCard r15("Clay");

    // Adding resources to players
    p1.add_resources_card(r1);
    p1.add_resources_card(r2);
    p1.add_resources_card(r3);
    p1.add_resources_card(r4);
    p1.add_resources_card(r5);

    p2.add_resources_card(r6);
    p2.add_resources_card(r7);
    p2.add_resources_card(r8);
    p2.add_resources_card(r9);
    p2.add_resources_card(r10);

    p3.add_resources_card(r11);
    p3.add_resources_card(r12);
    p3.add_resources_card(r13);
    p3.add_resources_card(r14);
    p3.add_resources_card(r15);

    p1.display_resources();
    p2.display_resources();
    p3.display_resources();

    initialize_game(p1, p2, p3, b);

    int turn = 0;
    player *curr_player = nullptr;

    while (p1.getScore() <= 10 && p2.getScore() <= 10 && p3.getScore() <= 10) {
        if (turn % 3 == 0) {
            curr_player = &p1;
        } else if (turn % 3 == 1) {
            curr_player = &p2;
        } else {
            curr_player = &p3;
        }

        curr_player->roll_number(b, p1, p2);
        curr_player->display_resources();

        bool end_turn = false;
        while (!end_turn) {
            print_menu();
            int press;
            cin >> press;

            switch (press) {
            case 1:
                // print board
                b.print_board();
                break;
            case 2:
                // display the roads
                p1.display_roads();
                break;
            case 3:
                // display settlements
                p1.display_settlements();
                break;
            case 4:
                // display cities
                curr_player->display_cities();
                break;
            case 5:
                // buy road
                {
                    int tile, edge;
                    cout << "Enter tile and edge for the road: ";
                    cin >> tile >> edge;
                    if (curr_player->buy_road(tile, edge, b, turn)) {
                        cout << "Road built successfully." << endl;
                    } else {
                        cout << "Failed to build road." << endl;
                    }
                }
                break;
            case 6:
                // buy settlement
                {
                    int tile, vertex;
                    cout << "Enter tile and vertex for the settlement: ";
                    cin >> tile >> vertex;
                    if (curr_player->buy_settlement(tile, vertex, b, turn)) {
                        cout << "Settlement built successfully." << endl;
                    } else {
                        cout << "Failed to build settlement." << endl;
                    }
                }
                break;
            case 7:
                // buy city
                {
                    int tile, vertex;
                    cout << "Enter tile and vertex for the city: ";
                    cin >> tile >> vertex;
                    if (curr_player->buy_city(tile, vertex, b, turn)) {
                        cout << "City built successfully." << endl;
                    } else {
                        cout << "Failed to build city." << endl;
                    }
                }
                break;
            case 8:
                // buy card
                curr_player->buy_card();
                break;
            case 9:
                // use card
                {
                    string card_type;
                    cout << "Enter card type to use: ";
                    cin >> card_type;
                    developeCard *card = curr_player->createDevelopmentCard(card_type);
                    if (card) {
                        curr_player->use(card, p1, p2, b);
                        delete card;
                    } else {
                        cout << "Invalid card type." << endl;
                    }
                }
                break;
            case 10:
                // trade
                {
                    int player_id;
                    cout << "Enter player ID to trade with (1: Orel, 2: Nir, 3: Amit): ";
                    cin >> player_id;
                    player *other_player = nullptr;
                    if (player_id == 1) other_player = &p1;
                    else if (player_id == 2) other_player = &p2;
                    else if (player_id == 3) other_player = &p3;

                    if (other_player && other_player != curr_player) {
                        curr_player->trade(*other_player);
                    } else {
                        cout << "Invalid player selected." << endl;
                    }
                }
                break;
            case 11:
                // show resources
                curr_player->display_resources();
                break;
            case 12:
                // show development cards
                curr_player->display_development_cards();
                break;
            case 13:
                // end turn
                curr_player->end_turn();
                end_turn = true;
                turn++;
                break;
            default:
                cout << "Invalid option" << endl;
                break;
            }
        }
        turn++;
    }

    return 0;
}

void print_menu() {
    cout << "1. Show Board" << endl;
    cout << "2. Show Roads" << endl;
    cout << "3. Show Settlements" << endl;
    cout << "4. Show Cities" << endl;
    cout << "5. Build Road" << endl;
    cout << "6. Build Settlement" << endl;
    cout << "7. Build City" << endl;
    cout << "8. Buy Development Card" << endl;
    cout << "9. Use Development Card" << endl;
    cout << "10. Trade" << endl;
    cout << "11. Show Resources" << endl;
    cout << "12. Show Development Cards" << endl;
    cout << "13. End Turn" << endl;
}

void initialize_game(player &p1, player &p2, player &p3, board &b) {
    int tile, edge, vertex;
    int counter_roads = 0;
    int counter_settlement = 0;

    // Initialize for Player 1
    while (counter_roads < 2 || counter_settlement < 2) {
        if (counter_roads < 2) {
            cout << "Player 1: Enter the tile and edge you want to set your road:" << endl;
            cin >> tile >> edge;
            try {
                if (b.getTile(tile).set_first_round_edge(p1, edge)) {
                    counter_roads++;
                }
            } catch (const out_of_range& e) {
                cerr << "Out of range exception while Player 1 buys road: " << e.what() << endl;
            }
        }
        if (counter_settlement < 2) {
            cout << "Player 1: Enter the tile and vertex you want to set your settlement:" << endl;
            cin >> tile >> vertex;
            try {
                if (b.getTile(tile).set_first_round_vertex(p1, vertex)) {
                    counter_settlement++;
                }
            } catch (const out_of_range& e) {
                cerr << "Out of range exception while Player 1 buys city: " << e.what() << endl;
            }
        }
    }

    // Reset counters for Player 2
    counter_roads = 0;
    counter_settlement = 0;

    // Initialize for Player 2
    while (counter_roads < 2 || counter_settlement < 2) {
        if (counter_roads < 2) {
            cout << "Player 2: Enter the tile and edge you want to set your road:" << endl;
            cin >> tile >> edge;
            try {
                if (b.getTile(tile).set_first_round_edge(p2, edge)) {
                    counter_roads++;
                }
            } catch (const out_of_range& e) {
                cerr << "Out of range exception while Player 2 buys road: " << e.what() << endl;
            }
        }
        if (counter_settlement < 2) {
            cout << "Player 2: Enter the tile and vertex you want to set your settlement:" << endl;
            cin >> tile >> vertex;
            try {
                if (b.getTile(tile).set_first_round_vertex(p2, vertex)) {
                    counter_settlement++;
                }
            } catch (const out_of_range& e) {
                cerr << "Out of range exception while Player 2 buys city: " << e.what() << endl;
            }
        }
    }

    // Reset counters for Player 3
    counter_roads = 0;
    counter_settlement = 0;

    // Initialize for Player 3
    while (counter_roads < 2 || counter_settlement < 2) {
        if (counter_roads < 2) {
            cout << "Player 3: Enter the tile and edge you want to set your road:" << endl;
            cin >> tile >> edge;
            try {
                if (b.getTile(tile).set_first_round_edge(p3, edge)) {
                    counter_roads++;
                }
            } catch (const out_of_range& e) {
                cerr << "Out of range exception while Player 3 buys road: " << e.what() << endl;
            }
        }
        if (counter_settlement < 2) {
            cout << "Player 3: Enter the tile and vertex you want to set your settlement:" << endl;
            cin >> tile >> vertex;
            try {
                if (b.getTile(tile).set_first_round_vertex(p3, vertex)) {
                    counter_settlement++;
                }
            } catch (const out_of_range& e) {
                cerr << "Out of range exception while Player 3 buys city: " << e.what() << endl;
            }
        }
    }
}

} // namespace ariel
