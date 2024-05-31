#include "player.hpp"

namespace ariel
{
    player::player(int id) : id(id), win_counter(0) {}

    int player::get_id() const
    {
        return id;
    }
    void player::add_win()
    {
         win_counter++;
    }
} // namespace ariel