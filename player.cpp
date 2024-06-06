#include "player.hpp"
using namespace std;
namespace ariel
{
    player::player(string name ,int id) : id(id), win_counter(0) ,points(2), name(name),resourceCard{},cards{},{}

    int player::get_id() const
    {
        return id;
    }
    void player::add_win()
    {
         win_counter++;
    }
    int player::get_points()
    {
        return points;
    }
    void player::add_points(int added_points)
    {
        points+=added_points;
    }
    int player::get_win_counter() const
    {
        return win_counter;
    }
    void player::add_resource_card(resourceCard rc)
    {
        resource_cards.push_back(rc);
        
    }   
    vector<resourceCard> player::get_resource_cards() 
    {
        return resource_cards;
    }
    void player::add_card(developeCard c)
    {
        cards.push_back(c);
     
    }
    vector<developeCard> player::get_developmentCard()
    {
        return cards;
    }
    int player:: buy_card(developeCard &card)
    {
        bool is_afoordable = true;
        vector<resourceCard>::iterator index;
        for(int i=0 ;i<card.get_price().size(); i++){
            index = find(resource_cards.begin(), resource_cards.end(), card.get_price()[i]);
            if(index != resource_cards.end())
            ////still not finished
            {
                is_afoordable = false;
                break;
            }
            resource_cards.erase(index);
        }
        add_card(card);
        return 1;
      
        cout<<"you don't have enough resources to buy this card"<<endl;
            return 0;
        
    }
    string player::get_name() const
    {
        return name;
    }
    bool player::find_card(string type) //parameter is string  either by the string itself or by using get_type()
    {
        for (auto i : cards)
        {
            if (i.get_type() == type)
            {
                return true;
            }
        }
        return false;
    }
    int trade_card(developeCard &card, player &p)
    {
        cout << p.get_name() << " do you want to trade this card with " << name << " ?" << endl;
        string input;
        cin >> input;
        if (input == "yes") {
            cout << "what card do you suggest instead of?" << card.get_type() << endl;
            cin >> input;
            resourceCard temp(input);
                if (p.find_card(input)) {
                    cout <<name<< " do you agree to trade " << input << " with " << p.get_name() << " ?" << endl;
                    cin >> input;
                    if (input == "yes") {
                        if(typeid(temp) == typeid(resourceCard)) {
                            resource_cards.push_back(temp);
                            p.resource_cards.erase(temp);
                            p.add_card(card);
                            cards.erase(card);
                        return 1;
                    } else if(typeid(temp) == typeid(developeCard)) {
                        add_card(temp);
                        p.cards.erase(temp);
                        p.add_card(card);
                        cards.erase(card);
                        return 0;
                    }
                }
            } else {
            return 0;
        }
    }
    }
} // namespace ariel



