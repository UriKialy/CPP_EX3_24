#include "player.hpp"
using namespace std;
namespace ariel
{
    player::player(string name ,int id) : id(id), win_counter(0) ,points(0), name(name),resourceCard{},cards{},{}

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
    int player::add_resource_card(resourceCard rc)
    {
        resource_cards.push_back(rc);
        return 0;
    }   
    vector<resourceCard> player::get_resource_cards() 
    {
        return resource_cards;
    }
    int player::add_card(developeCard c)
    {
        cards.push_back(c);
        return 0;
    }
    vector<developeCard> player::get_developmentCard()
    {
        return cards;
    }
    int player::buy_card(developeCard &p)
    {
        if(resource_cards.contains(*p.get_price()))
        {
            add_card(*p);
            resource_cards.erase(*p.get_price());
            return 1;
        }
        else
        {
            cout<<"you don't have enough resources to buy this card"<<endl;
            return 0;
        }
    }
} // namespace ariel



