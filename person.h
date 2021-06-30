//
// Created by 18502 on 6/15/2021.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
using namespace sf;
#ifndef SIMPLE_COVID_SIMULATION_PERSON_H
#define SIMPLE_COVID_SIMULATION_PERSON_H


class person {
public:
    enum disease_status {vulnerable, infected,dead,immune};
    person();
    person(bool,bool,int);
    person(const person&);
    person& operator =(const person&);
    disease_status getStatus();
    void setStatus(disease_status);
    int getDirection();
    void changeDirection();
    void setDirection(int);
    void move(float,float,float,float);
    CircleShape& getShape();
    void setPosition(float,float);
    void moveWayward(float,float,float,float);
    void moveDiagonally(float,float,float,float);
    bool infectOther(person&);
    bool hasMask();
    void setMask(bool);
    Vector2f getPosition();
    bool passAway();
    bool recover();

private:
    int infectedPeriod;
    bool mask;
    bool medicalCondition;
    int age;
    int direction;
    disease_status status;
    CircleShape human;
    float speed =0.07f;
};


#endif //SIMPLE_COVID_SIMULATION_PERSON_H
