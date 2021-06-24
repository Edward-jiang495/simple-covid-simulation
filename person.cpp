//
// Created by 18502 on 6/15/2021.
//

#include "person.h"

person:: person(){
    infectedPeriod = 0;
    mask = false;
    socialDistance =  false;
    srand (time(NULL));
    status = vulnerable;
    //roughly 27% non-elder people in the US has preexisting conditions
    //source: https://www.kff.org/policy-watch/pre-existing-conditions-what-are-they-and-how-many-people-have-them/#:~:text=KFF%20has%20estimated%20that%20in,ACA%20individual%20health%20insurance%20market.
    int ran = rand() %100;
    if(ran<27){
        medicalCondition = true;
    }
    else{
        medicalCondition=false;
    }
    //we assume age is randomly distributed between 15 to 80
    age= rand() % 66+15;

    human.setRadius(6.0f);
    human.setOrigin(Vector2f(6.0f,6.0f));
    if(status == vulnerable){
        human.setFillColor(Color::Blue);
    }
    else if(status == infected){
        human.setFillColor(Color::Red);
    }
    else if(status == dead){
        Color color(128,128,128);
        //this is gray
        human.setFillColor(color);
    }else if(status == immune){
        human.setFillColor(Color::Green);
    }

}

person:: person(bool hasMask, bool isDistanced, disease_status sta){
    infectedPeriod = 0;
    mask = hasMask;
    socialDistance =  isDistanced;
    srand (time(NULL));
    status = sta;

    //roughly 27% non-elder people in the US has preexisting conditions
    //source: https://www.kff.org/policy-watch/pre-existing-conditions-what-are-they-and-how-many-people-have-them/#:~:text=KFF%20has%20estimated%20that%20in,ACA%20individual%20health%20insurance%20market.
    int ran = rand() %100;
    if(ran<27){
        medicalCondition = true;
    }
    else{
        medicalCondition=false;
    }
    //we assume age is randomly distributed between 15 to 80
    age= rand() % 66+15;

    human.setRadius(6.0f);
    human.setOrigin(Vector2f(6.0f,6.0f));
    if(status == vulnerable){
        human.setFillColor(Color::Blue);
    }
    else if(status == infected){
        human.setFillColor(Color::Red);
    }
    else if(status == dead){
        Color color(128,128,128);
        //this is gray
        human.setFillColor(color);
    }else if(status == immune){
        human.setFillColor(Color::Green);
    }
}


person::person(const person& p){
    mask = p.mask;
    medicalCondition = p.medicalCondition;
    socialDistance = p.socialDistance;
    age = p.age;
    status = p.status;
    infectedPeriod=p.infectedPeriod;
    human = p.human;
}
person& person::operator =(const person& p){
    mask = p.mask;
    medicalCondition = p.medicalCondition;
    socialDistance = p.socialDistance;
    age = p.age;
    status = p.status;
    infectedPeriod=p.infectedPeriod;
    human = p.human;
    return *this;
}

person::disease_status person:: getStatus(){
    return status;
}
void person::setStatus(person::disease_status s){
    status=s;
}

CircleShape& person::getShape(){
    return human;
}
void person::setPosition(float x,float y){
    human.setPosition(Vector2f(x,y));
}

void person:: move(){
    //move the people around
    int ran = rand()%4;
    if(ran==0){
        human.move(-1.2f,0.0f);
        //move left
    }
    else if(ran ==1){
        human.move(0.0f,-1.2f);
        //move up
    }
    else if(ran ==2){
        human.move(0.0f,1.2f);
        //move down
    }
    else if(ran ==3){
        human.move(1.2f,0.0f);
        //move right
    }

}