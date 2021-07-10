#include <SFML/Graphics.hpp>
#include <iostream>
#include "community.h"
using namespace std;
using namespace sf;
//here is my covid simulation project
int main()
{
//first parameter is the size of the community
//the second parameter represents the percenatage of people wearing masks
//third parameter determines the speed of vaccination in simulated days
//set the third parameter to a large number (like 99999) to disable vaccine
//forth parameter determines the mask mandate when death rate reaches a certain threshold
//set the forth parameter over 1 to disable mask mandate
//we recommend using this constructor over the default constructor
//because sometimes default constructor does not have enough randomness

    community test(50,0,10,0.2);
    test.run();

    return 0;
}