#include "player.hpp"

using namespace std;

namespace ariel {
    int player::id = -2;

    player::player(string playerName) : name(playerName), score(0) {
        id++;
    }

    player::~player() {
        for (auto card : development_cards) {
            delete card;
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

    void player::add_resourceCard(const resourceCard& card) { // Ensure this matches the declaration
        resources.push_back(card);
    }

    void player::add_points(int score) {
        this->score += score;
    }
    void player::add_road(string road)
    {
        roads.push_back(road);
    }
    void player:: add_settlement(string settlement)
    {
        settlements.push_back(settlement);
    }
    void player:: add_city(string city)
    {
        cities.push_back(city);
    }
    void player:: display_roads()
    {
        cout << getName()<<" your Roads are: " << endl;
       for(size_t i=0;i<roads.size();i++)
       {
           cout<<roads.at(i)<<endl;
       }
    }
 void player::display_development_cards()
{
    if (getDevelopment_cards().empty())
    {
        cout << getName() << ", you don't have any development cards." << endl;
    }
    else
    {
        for (const auto &card : getDevelopment_cards())
        {
            card->display();
        }
    }
}
    void player:: display_settlements()
    {
        for (const auto& settlement : settlements) {
            cout << settlement << endl;
        }
    }
 void player::display_cities()
{
    if (cities.empty())
    {
        cout << getName() << ", you don't have any cities." << endl;
    }
    else
    {
        for (const auto &city : cities)
        {
            cout << city << endl;
        }
    }
}
    


    void player::buy_card() {
        cout << "Buying a card" << endl;
        if (hasResources({"wool", "steel", "Wheat"})) {
            removeResources({"wool", "steel", "Wheat"});
            add_development_cards(createDevelopmentCard(getrandomcard()));
        } else {
            cout << "You do not have the required resources" << endl;
        }
    }
    

    string player::getrandomcard() {
        srand((time(NULL)));
        if(victoryCard::get_victoryCardCount()>5&&knights::get_knightsCount()>4) {
            switch (rand() % 3) {
            case 1: return "abundanceCard";
            case 2: return "monopolyCard";
            default: return "road_building";
        }
        }
        if(victoryCard::get_victoryCardCount()>5) {
            switch (rand() % 4) {
            case 1: return "abundanceCard";
            case 2: return "monopolyCard";
            case 3: return "road_building";
            default: return "knights";
        }
        }
        if(knights::get_knightsCount()>4) {
            switch (rand() % 4) {
            case 1: return "victoryCard";
            case 2: return "abundanceCard";
            case 3: return "monopolyCard";
            default: return "road_building";
        }
        }
        switch (rand() % 5) {
            case 0: return "victoryCard";
            case 1: return "abundanceCard";
            case 2: return "monopolyCard";
            case 3: return "road_building";
            default: return "knights";
        }
    }

    int player::use(developeCard* card, player& take1, player& take2, board& board1) {
        string card_type = card->get_type();
        if (card_type == "victoryCard") {
            processVictoryCard();
            return 1;
        } else if (card_type == "knights") {
            processKnightCard();
            return 1;
        } else if (card_type == "monopolyCard") {
            processMonopolyCard(take1, take2);
            return 1;
        } else if (card_type == "abundanceCard") {
            process_abundanceCard();
            return 1;
        } else if (card_type == "road_building") {
            processRoadBuildingCard(board1);
            return 1;
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
    // Create a copy of the resources to remove to keep track of what has been removed
    vector<string> to_remove = resources_to_remove;

    for (auto it = to_remove.begin(); it != to_remove.end(); ++it) {
        // Find the resource in the player's resources
        auto res_it = find_if(resources.begin(), resources.end(),
            [&](resourceCard& rc) {
                return rc.get_type() == *it;
            });

        // If found, remove the resource
        if (res_it != resources.end()) {
            resources.erase(res_it);
        }
    }
}

    developeCard* player::createDevelopmentCard(const string& card_type) {
        vector<resourceCard> price = { resourceCard("wool"), resourceCard("steel"), resourceCard("Wheat") };
        if (card_type == "victoryCard")  cout<<"torl"<<endl; new victoryCard(card_type, price);
        if (card_type == "abundanceCard") return new abundanceCard(card_type, price);
        if (card_type == "monopolyCard") return new monopolyCard(card_type, price);
        if (card_type == "road_building") return new road_building(card_type, price);
        return new knights(card_type, price);
    }

    void player::processVictoryCard() {

        if (removeCardOfType("victoryCard")) {
            add_points(1);
        }
    }

    void player::processKnightCard() {
        if (count_if(development_cards.begin(), development_cards.end(), [](developeCard* c) { return c->get_type() == "knights"; }) >= 3) {
            this->add_points(2);
            removeCardOfType("knights");
        }
    }

    void player::processMonopolyCard(player& take1, player& take2) {
        cout << "Choose a resource to monopolize: ";
        string resource;
        cin >> resource;
        takeResourceFromPlayer(take1, resource);
        takeResourceFromPlayer(take2, resource);
        removeCardOfType("monopolyCard");
    }

    void player::process_abundanceCard() {
        for (int i = 0; i < 2; ++i) {
            cout << "Choose a resource you want to take: ";
            string resource;
            cin >> resource;
            add_resourceCard(resourceCard(resource));
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

    if (roll == 7) {
        // Handle resources for the current player
        if (getResources().size() > 7) {
            display_resources();
            cout << getName() << " has more than 7 resources. Cutting resources by half." << endl;
            int numResourcesToRemove = getResources().size() / 2;
            for (int i = 0; i < numResourcesToRemove; ++i) {
                string resource;
                cout << "Enter the resource you want to remove: ";
                cin >> resource;
                if (hasResources({resource})) {
                    removeResources({resource});
                } else {
                    cout << "Resource not found. Please enter a valid resource." << endl;
                    --i;
                }
            }
        } else {
            cout << getName() << " has 7 or fewer resources. No need to remove resources." << endl;
        }

        // Handle resources for player 1
        if (p1.getResources().size() > 7) {
            p1.display_resources();
            cout << p1.getName() << " has more than 7 resources. Cutting resources by half." << endl;
            int numResourcesToRemove = p1.getResources().size() / 2;
            for (int i = 0; i < numResourcesToRemove; ++i) {
                string resource;
                cout << "Enter the resource you want to remove: ";
                cin >> resource;
                if (p1.hasResources({resource})) {
                    p1.removeResources({resource});
                } else {
                    cout << "Resource not found. Please enter a valid resource." << endl;
                    --i;
                }
            }
        } else {
            cout << p1.getName() << " has 7 or fewer resources. No need to remove resources." << endl;
        }

        // Handle resources for player 2
        if (p2.getResources().size() > 7) {
            p2.display_resources();
            cout << p2.getName() << " has more than 7 resources. Cutting resources by half." << endl;
            int numResourcesToRemove = p2.getResources().size() / 2;
            for (int i = 0; i < numResourcesToRemove; ++i) {
                string resource;
                cout << "Enter the resource you want to remove: ";
                cin >> resource;
                if (p2.hasResources({resource})) {
                    p2.removeResources({resource});
                } else {
                    cout << "Resource not found. Please enter a valid resource." << endl;
                    --i;
                }
            }
        } else {
            cout << p2.getName() << " has 7 or fewer resources. No need to remove resources." << endl;
        }
        return 1;
    }

    for (int i = 0; i < 19; ++i) {
        try {
            const auto& vertexes = b.getTile(i).getvertex();
            if (b.getTile(i).getvalue_roll() == roll) {
                for (int j = 0; j < 6; ++j) {
                    try {
                        const auto& type = vertexes.at(1).at(j);
                        const auto& id = vertexes.at(0).at(j);

                        if (id == p1.getid()) {
                            if (type == 2) {
                                cout << "player 1 gets 2 resources of type " << b.getTile(i).gettype() << endl;
                                p1.add_resourceCard(resourceCard(b.getTile(i).gettype()));
                                p1.add_resourceCard(resourceCard(b.getTile(i).gettype()));
                            } else if (type == 1) {
                                                                cout << "player 1 gets 1 resources of type " << b.getTile(i).gettype() << endl;
                                p1.add_resourceCard(resourceCard(b.getTile(i).gettype()));
                            }
                        }
                        if (id == p2.getid()) {
                            if (type == 2) {
                                cout << "player 2 gets 2 resources of type " << b.getTile(i).gettype() << endl;
                                p2.add_resourceCard(resourceCard(b.getTile(i).gettype()));
                                p2.add_resourceCard(resourceCard(b.getTile(i).gettype()));
                            } else if (type == 1) {
                                p2.add_resourceCard(resourceCard(b.getTile(i).gettype()));
                            }
                        }
                        if (id == getid()) {
                            if (type == 2) {
                                cout << "You get 2 resources of type " << b.getTile(i).gettype() << endl;
                                add_resourceCard(resourceCard(b.getTile(i).gettype()));
                                add_resourceCard(resourceCard(b.getTile(i).gettype()));
                            } else if (type == 1) {
                                add_resourceCard(resourceCard(b.getTile(i).gettype()));
                            }
                        }
                    } catch (const out_of_range& e) {
                        cerr << "Out of range exception in roll_number (inner loop): " << e.what() << endl;
                        continue; // Skip to the next iteration
                    }
                }
            }
        } catch (const out_of_range& e) {
            cerr << "Out of range exception in roll_number (outer loop): " << e.what() << endl;
            continue; // Skip to the next iteration
        }
    }
    return 1;
}

    int player::buy_road(int tile,int edge,board& b,int turn){
        if(hasResources({"Brick", "Wood"})){
            if(b.getTile(id).setedges(edge,id)&&turn!=3)
            {
                cout<<"orel"<<id<<" nissan "<<edge<<endl;
                removeResources({"Brick", "Wood"});
                cout<<"Road was bought at id:"<<tile<<" edge "<<edge<<endl;
                 string type="you have city at id:"+to_string(tile)+" vertex "+to_string(edge);
                add_road(type);
                return 1;
            }
            else{
                cout<<"Road was not bought at id:"<<id<<" edge "<<edge<<endl;
                return 0;
            }
            if(!hasResources({"Brick", "Wood"}))
            {
                cout<<"Road was not bought at you dont have the resources"<<endl;
                return 0;
            }
            if (!b.getTile(id).setedges(edge,id))
            {
                cout<<"Road was not bought beacuse there is road"<<endl;
            }
            removeResources({"wool", "steel"});
            cout<<"Road was bought at id:"<<id<<" edge "<<edge<<endl;
            return 1;
        }
        return 0;  
    }
    int player::buy_city(int tile,int vertex,board& b,int turn)
    {
        int y=0;
        if(turn==0)
        {
            y++;
        }
        if(hasResources({"steel","steel", "Wheat", "steel","Wheat"})){
            if(b.getTile(tile).getvertex().at(0).at(0)==id)
            {
                removeResources({"steel","steel", "Wheat", "steel","Wheat"});
                cout<<"Stelment was bought at id:"<<id<<" vertex "<<vertex<<endl;
                b.getTile(tile).getvertex().at(1).at(vertex)=2;
                add_points(1);
                cout<<"you have now "<<getScore()<<" points"<<endl;
                string type="you have city at id:"+to_string(id)+" vertex "+to_string(vertex);
                add_city(type);
                return 1;
            }
            else{
                cout<<"Stelment was not bought at tile:"<<tile<<" vertex "<<vertex<<endl;
                return 0;
            }
            if(!hasResources({"steel","steel", "Wheat", "steel","Wheat"}))
            {
                cout<<"Stelment was not bought at you dont have the resources"<<endl;
                return 0;
            }
            if (!b.getTile(tile).setedges(vertex,getid()))
            {
                cout<<"Stelment was not bought beacuse there is stelment"<<endl;
            }
            removeResources({"steel","steel", "Wheat", "steel","Wheat"});
            cout<<"Stelment was bought at id:"<<id<<" vertex "<<vertex<<endl;
        }
        return 1;
    }
    int player::buy_settlement(int id,int vertex,board &b,int turn)
    {
         int y=0;
        if(turn==0)
        {
            y++;
        }
        if(hasResources({"steel","Wood", "Wheat", "wool"})){
            if(b.getTile(id).set_vertex(vertex,id,getid()))
            {
                removeResources({"steel","Wood", "Wheat", "wool"});
                cout<<"Stelment was bought at id:"<<id<<" vertex "<<vertex<<endl;
                add_points(1);
              string type="the tile"+to_string(id)+"put settlement in vertex"+to_string(vertex);
                add_settlement(type);
                return 1;
            }
            else{
                cout<<"Stelment was not bought at id:"<<id<<" vertex "<<vertex<<endl;
                return 0;
            }
            if(!hasResources({"steel","Wood", "Wheat", "wool"}))
            {
                cout<<"Stelment was not bought at you dont have the resources"<<endl;
                return 0;
            }
            if (!b.getTile(id).set_vertex(vertex,id,getid()))
            {
                cout<<"Stelment was not bought beacuse there is stelment"<<endl;
            }
            removeResources({"steel","Wood", "Wheat", "wool"});
            cout<<"Stelment was bought at id:"<<id<<" vertex "<<vertex<<endl;
            return 1;
        }
        return 0;
    }

 void player::display_resources()
{
    cout << getName() << " your resources are:" << endl;
    if (resources.empty())
    {
        cout << "You don't have any resources." << endl;
    }
    else
    {
        for (const auto &res : resources)
        {
            cout << res.get_type() << endl;
        }
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
        // Trim whitespace
        token.erase(0, token.find_first_not_of(" \t\n\r\f\v"));
        token.erase(token.find_last_not_of(" \t\n\r\f\v") + 1);
        result.push_back(token);
    }

    return result;
}


void player::trade(player& ask1) {
    string resource_take;
    string resource_give;
    cout << "Enter the resource you want to trade:";
    cin >> resource_take;    
    cout << "Enter the resource you want to give:";
    cin >> resource_give;
    vector<resourceCard> resources_take = ask1.getResources();
    vector<resourceCard> resources2_give = getResources();
    vector<string> resources_give_str=splitStringByComma(resource_give);
    vector<string> resources_take_str=splitStringByComma(resource_take);
    cout << "the ofer is take:"<<resource_take<<" give:"<<resource_give<<endl;
    char answer;
    cout << "Do you accept the trade? (y/n):";
    cin >> answer;
    if(answer=='Y'||answer=='y')
    {
        if(this->hasResources(resources_give_str)&&ask1.hasResources(resources_take_str))
        {
            this->removeResources(resources_give_str);
            ask1.removeResources(resources_take_str);
            for(const auto& res:resources_give_str)
            {
                ask1.add_resourceCard(resourceCard(res));
            }
            for(const auto& res:resources_take_str)
            {
                this->add_resourceCard(resourceCard(res));
            }
            cout << "Trade was accepted" << endl;
            cout << "Your resources after trade:" << endl;
            this->display_resources();
        }
        else
        {
            cout << "Trade was not accepted" << endl;
        }
    }
    else
    {
        cout << "Trade was not accepted" << endl;
    }
}
    void player::end_turn() {
        cout << "Ending turn" <<  endl;
        cout << "Your score: " << getScore() << endl;
        display_roads();
        cout << "Your settlements: " << endl;
        display_settlements();
        display_cities();
        display_resources();
        display_development_cards();
}
}
