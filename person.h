//
// Created by 18502 on 6/15/2021.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace sf;
#ifndef SIMPLE_COVID_SIMULATION_PERSON_H
#define SIMPLE_COVID_SIMULATION_PERSON_H


class person {
public:
    enum disease_status {vulnerable, infected,dead,immune};
    person();
    person(bool,bool,disease_status);
    person(const person&);
    person& operator =(const person&);
    disease_status getStatus();
    void setStatus(disease_status);
    void move();
    CircleShape& getShape();
    void setPosition(float,float);
private:
    int infectedPeriod;
    bool mask;
    bool medicalCondition;
    bool socialDistance;
    int age;
    disease_status status;
    CircleShape human;
};


#endif //SIMPLE_COVID_SIMULATION_PERSON_H
