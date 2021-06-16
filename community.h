//
// Created by 18502 on 6/16/2021.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include "person.h"
using namespace std;
using namespace sf;
#ifndef SIMPLE_COVID_SIMULATION_COMMUNITY_H
#define SIMPLE_COVID_SIMULATION_COMMUNITY_H


class community {
private:
    int size;
    int days;
    bool lockDown;
    RenderWindow window;
public:
    community();
    community(int,bool);
    void run();
    void move();

};


#endif //SIMPLE_COVID_SIMULATION_COMMUNITY_H
