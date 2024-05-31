#include <iostream>
#include <string>
using namespace std;
namespace ariel{

class player{
    int id;
    int win_counter;
    public:
    player(int id);
    ~player()=default;
    int get_id() const;
    void add_win();
    
};

}