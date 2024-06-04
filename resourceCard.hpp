#include "player.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace ariel
{
    class resourceCard 
    {
        string type;
    public:
        resourceCard(string type):type(type){};
        string get_type(){
            return type;
        }       
    };
} // namespace ariel