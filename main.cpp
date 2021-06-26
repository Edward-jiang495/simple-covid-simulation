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
    community test(30,false);
    test.run();

    return 0;
}