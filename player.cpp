#include "player.hpp"
using namespace std;

namespace ariel {
    int player::id = 1;

    player::player(string playerName) : name(playerName), score(0) {
        id++;
    }

    player::~player() {
        for (auto developeCard : development_cards) {
            delete developeCard;
        }
    }

    string player::getName() const {
        return name;
    }

    int player::getScore() const {
        return score;
    }

    vector<developeCard*>& player::getDevelopment_cards() {
        return development_cards;
    }

    vector<resourceCard>& player::getResources() {
        return resources;
    }

      void player::add_development_cards(developeCard* card) {
        development_cards.push_back(card);
    }

    void player::add_resources_card(const resourceCard& card) {
        resources.push_back(card);
    }

    void player::add_const_score(int score) {
        this->score += score;
    }
   
    void player::add_road(string road) {
        roads.push_back(road);
    }
   
    void player::add_settlement(string settlement) {
        settlements.push_back(settlement);
    }
   
    void player::add_city(string city) {
        cities.push_back(city);
    }
   
    void player::display_roads() {
        cout << getName() << " your Roads are: " << endl;
        for (size_t i = 0; i < roads.size(); i++) {
            cout << roads.at(i) << endl;
        }
    }

    void player::display_development_cards() {
        for (const auto& card : getDevelopment_cards()) {
            card->display();
        }
    }

    void player::display_settlements() {
        for (const auto& settlement : settlements) {
            cout << settlement << endl;
        }
    }

    void player::display_cities() {
        for (const auto& city : cities) {
            cout << city << endl;
        }
    }

    void player::buy_card() {
        cout << "Buying a card" << endl;
        if (hasResources({"Sheep", "Clay", "Wheat"})) {
            removeResources({"Sheep", "Clay", "Wheat"});
            add_development_cards(createDevelopmentCard(getrandomcard()));
        } else {
            cout << "You do not have the required resources" << endl;
        }
    }

    string player::getrandomcard() {
        srand(static_cast<unsigned int>(time(NULL)));
        if (victoryCard::get_victoryCardCount() > 5 && knights::get_knightsCount() > 4) {
            switch (rand() % 3) {
                case 1: return "abundanceCard";
                case 2: return "Monopoly";
                default: return "road_building";
            }
        }
        if (victoryCard::get_victoryCardCount() > 5) {
            switch (rand() % 4) {
                case 1: return "abundanceCard";
                case 2: return "Monopoly";
                case 3: return "road_building";
                default: return "Knight";
            }
        }
        if (knights::get_knightsCount() > 4) {
            switch (rand() % 4) {
                case 1: return "Victory";
                case 2: return "abundanceCard";
                case 3: return "Monopoly";
                default: return "road_building";
            }
        }
        switch (rand() % 5) {
            case 0: return "Victory";
            case 1: return "abundanceCard";
            case 2: return "Monopoly";
            case 3: return "road_building";
            default: return "Knight";
        }
    }

    int player::use(developeCard* card, player& take1, player& take2, board& board1) {
        string card_type = card->get_type();
        if (card_type == "Victory") {
            processVictoryCard();
        } else if (card_type == "Knight") {
            processKnightCard();
        } else if (card_type == "Monopoly") {
            processMonopolyCard(take1, take2);
        } else if (card_type == "abundanceCard") {
            processYearOfHappyCard();
        } else if (card_type == "road_building") {
            processRoadBuildingCard(board1);
        }
        return 0;
    }

    bool player::hasResources(const vector<string>& required_resources) const {
        for (const auto& res : required_resources) {
            if (none_of(resources.begin(), resources.end(), [&](const resourceCard& rc) { return rc.get_type() == res; })) {
                return false;
            }
        }
        return true;
    }

    void player::removeResources(const vector<string>& resources_to_remove) {
        vector<string> to_remove = resources_to_remove;
        for (auto it = to_remove.begin(); it != to_remove.end(); ++it) {
            auto res_it = find_if(resources.begin(), resources.end(), [&](resourceCard& rc) {
                return rc.get_type() == *it;
            });
            if (res_it != resources.end()) {
                resources.erase(res_it);
            }
        }
    }

    developeCard* player::createDevelopmentCard(const string& card_type) {
        vector<resourceCard> price = { resourceCard("Sheep"), resourceCard("Clay"), resourceCard("Wheat") };
        if (card_type == "Victory") return new victoryCard(card_type, price);
        if (card_type == "abundanceCard") return new abundanceCard(card_type, price);
        if (card_type == "Monopoly") return new monopolyCard(card_type, price);
        if (card_type == "road_building") return new road_building(card_type, price);
        return new knights(card_type, price);
    }

    void player::processVictoryCard() {
        if (removeCardOfType("Victory")) {
            add_const_score(1);
        }
    }

    void player::processKnightCard() {
        if (count_if(development_cards.begin(), development_cards.end(), [](developeCard* c) { return c->get_type() == "Knight"; }) >= 3) {
            add_const_score(2);
            removeCardOfType("Knight");
        }
    }

    void player::processMonopolyCard(player& take1, player& take2) {
        cout << "Choose a resource to monopolize: ";
        string resource;
        cin >> resource;
        takeResourceFromPlayer(take1, resource);
        takeResourceFromPlayer(take2, resource);
        removeCardOfType("Monopoly");
    }

    void player::processYearOfHappyCard() {
        for (int i = 0; i < 2; ++i) {
            cout << "Choose a resource you want to take: ";
            string resource;
            cin >> resource;
            add_resources_card(resourceCard(resource));
        }
        removeCardOfType("abundanceCard");
    }

    void player::processRoadBuildingCard(board& board1) {
        for (int count = 0; count < 2; ++count) {
            int id, edge;
            cout << "Enter the tile id and edge id you want to set: ";
            cin >> id >> edge;
            while (!board1.getTile(id).setedges(edge, id)) {
                cout << "Enter the tile id and edge id you want to set: ";
                cin >> id >> edge;
            }
        }
        removeCardOfType("road_building");
    }

    bool player::removeCardOfType(const string& card_type) {
        auto it = find_if(development_cards.begin(), development_cards.end(), [&](developeCard* c) { return c->get_type() == card_type; });
        if (it != development_cards.end()) {
            delete *it;
            development_cards.erase(it);
            return true;
        }
        return false;
    }

    void player::takeResourceFromPlayer(player& player, const string& resource) {
        auto& player_resources = player.getResources();
        auto it = remove_if(player_resources.begin(), player_resources.end(), [&](resourceCard& rc) { return rc.get_type() == resource; });
        resources.insert(resources.end(), player_resources.begin(), it);
        player_resources.erase(it, player_resources.end());
    }

    int player::getid() {
        return id;
    }

    int player::roll_number(board& b, player& p1, player &p2) {
        srand(static_cast<unsigned int>(time(0)));
        int roll = rand() % 6 + 1 + rand() % 6 + 1;
        cout << "The number is: " << roll << endl;

        if (roll == 7) {
            if (getResources().size() > 7) {
                cout << getName() << " has more than 7 resources. Cutting resources by half." << endl;
                int numResourcesToRemove = getResources().size() / 2;
                for (int i = 0; i < numResourcesToRemove; ++i) {
                    string resource;
                    cout << "Enter the resource you want to remove: ";
                    cin >> resource;
                    removeResources({resource});
                }
            } else {
                cout << getName() << " has 7 or fewer resources. No need to remove resources." << endl;
            }

            if (p1.getResources().size() > 7) {
                cout << p1.getName() << " has more than 7 resources. Cutting resources by half." << endl;
                int numResourcesToRemove = p1.getResources().size() / 2;
                for (int i = 0; i < numResourcesToRemove; ++i) {
                    string resource;
                    cout << "Enter the resource you want to remove: ";
                    cin >> resource;
                    p1.removeResources({resource});
                }
            } else {
                cout << p1.getName() << " has 7 or fewer resources. No need to remove resources." << endl;
            }

            if (p2.getResources().size() > 7) {
                cout << p2.getName() << " has more than 7 resources. Cutting resources by half." << endl;
                int numResourcesToRemove = p2.getResources().size() / 2;
                for (int i = 0; i < numResourcesToRemove; ++i) {
                    string resource;
                    cout << "Enter the resource you want to remove: ";
                    cin >> resource;
                    p2.removeResources({resource});
                }
            } else {
                cout << p2.getName() << " has 7 or fewer resources. No need to remove resources." << endl;
            }
            return 1;
        }

        for (int i = 0; i < 19; i++) {
            try {
                const auto& vertexes = b.getTile(i).getvertex();
                if (b.getTile(i).getvalue_roll() == roll) {
                    for (int j = 0; j < 6; j++) {
                        try {
                            const auto& type = vertexes[j][1];
                            const auto& id = vertexes[j][0];

                            if (id == p1.getid()) {
                                if (type == 2) {
                                    p1.add_resources_card(resourceCard(b.getTile(i).gettype()));
                                    p1.add_resources_card(resourceCard(b.getTile(i).gettype()));
                                } else if (type == 1) {
                                    p1.add_resources_card(resourceCard(b.getTile(i).gettype()));
                                }
                            }
                            if (id == p2.getid()) {
                                if (type == 2) {
                                    p2.add_resources_card(resourceCard(b.getTile(i).gettype()));
                                    p2.add_resources_card(resourceCard(b.getTile(i).gettype()));
                                } else if (type == 1) {
                                    p2.add_resources_card(resourceCard(b.getTile(i).gettype()));
                                }
                            }
                            if (id == getid()) {
                                if (type == 2) {
                                    add_resources_card(resourceCard(b.getTile(i).gettype()));
                                    add_resources_card(resourceCard(b.getTile(i).gettype()));
                                } else if (type == 1) {
                                    add_resources_card(resourceCard(b.getTile(i).gettype()));
                                }
                            }
                        } catch (const out_of_range& e) {
                            cerr << "Out of range exception in roll_number: " << e.what() << endl;
                            continue;
                        }
                    }
                }
            } catch (const out_of_range& e) {
                cerr << "Out of range exception in roll_number: " << e.what() << endl;
                continue;
            }
        }
        return 1;
    }

    int player::buy_road(int tile, int edge, board& b, int turn) {
        if (turn == 0) {
            cout << "first round" << endl;
            cout << this->getid() << endl;

            if (b.getTile(tile).setedges(edge, id)) {
                cout << "Road was bought at id: " << tile << " edge " << edge << endl;
                string type = "you have road at id: " + to_string(tile) + " vertex " + to_string(edge);
                add_road(type);
                return 1;
            }
        }
        if (hasResources({"Brick", "Wood"})) {
            if (b.getTile(tile).setedges(edge, id)) {
                cout << "orel " << id << " nissan " << edge << endl;
                removeResources({"Brick", "Wood"});
                cout << "Road was bought at id: " << tile << " edge " << edge << endl;
                string type = "you have road at id: " + to_string(tile) + " vertex " + to_string(edge);
                add_road(type);
                return 1;
            } else {
                cout << "Road was not bought at id: " << id << " edge " << edge << endl;
                return 0;
            }
        }
        cout << "Road was not bought because you don't have the resources" << endl;
        return 0;
    }

    int player::buy_city(int tile, int vertex, board& b, int turn) {
        if (turn == 0) {
            cout << "first round" << endl;
            cout << this->getid() << endl;

            if (b.getTile(tile).set_vertex(vertex, 2, id)) {
                cout << "City was bought at tile: " << tile << " vertex " << vertex << endl;
                string type = "you have city at id: " + to_string(tile) + " vertex " + to_string(vertex);
                add_city(type);
                return 1;
            }
        }
        if (hasResources({"Clay", "Clay", "Wheat", "Clay", "Wheat"})) {
            if (b.getTile(tile).set_vertex(vertex, 2, id)) {
                removeResources({"Clay", "Clay", "Wheat", "Clay", "Wheat"});
                cout << "Settlement was bought at id: " << id << " vertex " << vertex << endl;
                b.getTile(tile).getvertex().at(vertex).at(1) = 2;
                add_const_score(1);
                cout << "you have now " << getScore() << " points" << endl;
                string type = "you have city at id: " + to_string(tile) + " vertex " + to_string(vertex);
                add_city(type);
                return 1;
            } else {
                cout << "Settlement was not bought at tile: " << tile << " vertex " << vertex << endl;
                return 0;
            }
        }
        cout << "Settlement was not bought because you don't have the resources" << endl;
        return 0;
    }

    int player::buy_settlement(int id, int vertex, board& b, int turn) {
        if (turn == 0) {
            if (b.getTile(id).set_vertex(vertex, 1, getid())) {
                cout << "Settlement was bought at id: " << id << " vertex " << vertex << endl;
                string type = "you have settlement at id: " + to_string(id) + " vertex " + to_string(vertex);
                add_const_score(1);
                add_settlement(type);
                return 1;
            }
        }
        if (hasResources({"Clay", "Wood", "Wheat", "Sheep"})) {
            if (b.getTile(id).set_vertex(vertex, 1, getid())) {
                removeResources({"Clay", "Wood", "Wheat", "Sheep"});
                cout << "Settlement was bought at id: " << id << " vertex " << vertex << endl;
                add_const_score(1);
                string type = "you have settlement at id: " + to_string(id) + " vertex " + to_string(vertex);
                add_settlement(type);
                return 1;
            } else {
                cout << "Settlement was not bought at id: " << id << " vertex " << vertex << endl;
                return 0;
            }
        }
        cout << "Settlement was not bought because you don't have the resources" << endl;
        return 0;
    }

    void player::display_resources() {
        cout << getName() << " your resources are: " << endl;
        for ( auto& res : resources) {
            cout << res.get_type() << endl;
        }
    }

    void to_lowercase(string& str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    vector<string> splitStringByComma(const string& str) {
        vector<string> result;
        istringstream stream(str);
        string token;

        while (getline(stream, token, ',')) {
            token.erase(0, token.find_first_not_of(" \t\n\r\f\v"));
            token.erase(token.find_last_not_of(" \t\n\r\f\v") + 1);
            result.push_back(token);
        }

        return result;
    }

    void player::trade(player& ask1) {
        string resource_take;
        string resource_give;
        cout << "Enter the resource you want to trade: ";
        cin >> resource_take;
        cout << "Enter the resource you want to give: ";
        cin >> resource_give;
        vector<resourceCard> resources_take = ask1.getResources();
        vector<resourceCard> resources2_give = getResources();
        vector<string> resources_give_str = splitStringByComma(resource_give);
        vector<string> resources_take_str = splitStringByComma(resource_take);
        cout << "The offer is take: " << resource_take << " give: " << resource_give << endl;
        char answer;
        cout << "Do you accept the trade? (y/n): ";
        cin >> answer;
        if (answer == 'Y' || answer == 'y') {
            if (this->hasResources(resources_give_str) && ask1.hasResources(resources_take_str)) {
                this->removeResources(resources_give_str);
                ask1.removeResources(resources_take_str);
                for (const auto& res : resources_give_str) {
                    ask1.add_resources_card(resourceCard(res));
                }
                for (const auto& res : resources_take_str) {
                    this->add_resources_card(resourceCard(res));
                }
                cout << "Trade was accepted" << endl;
                cout << "Your resources after trade: " << endl;
                this->display_resources();
            } else {
                cout << "Trade was not accepted" << endl;
            }
        } else {
            cout << "Trade was not accepted" << endl;
        }
    }

    void player::end_turn() {
        cout << "Ending turn" << endl;
        cout << "Your score: " << getScore() << endl;
        display_roads();
        cout << "Your settlements: " << endl;
        display_settlements();
        display_cities();
        display_resources();
        display_development_cards();
    }
}