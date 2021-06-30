#include <SFML/Graphics.hpp>
#include <iostream>
#include "community.h"
using namespace std;
using namespace sf;
//here is my covid simulation project
int main()
{
//first parameter is the size of the community
//second parameter is about whether the community is under lockdown or not
//this is currently implementing
//we recommend using this constructor over the default constructor
//because sometimes default constructor does not have enough randomness
    community test(50);
    test.run();

    return 0;
}