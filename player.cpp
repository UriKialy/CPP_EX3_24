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
    int player::add_card(developmentCard c)
    {
        cards.push_back(c);
        return 0;
    }
    vector<developmentCard> player::get_developmentCard()
    {
        return cards;
    }
} // namespace ariel



