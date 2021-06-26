//
// Created by 18502 on 6/16/2021.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
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
    vector<person> peoples;
    RenderWindow window;
    int infectedNum;
    int vulnerableNum;
    int deathNum;
    int recoveredNum;
    //vaccinated shares the same status with recovered
public:
    community();
    community(int,bool);
    void run();
    void move();

};


#endif //SIMPLE_COVID_SIMULATION_COMMUNITY_H
