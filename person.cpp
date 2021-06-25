//
// Created by 18502 on 6/15/2021.
//

#include "person.h"

person:: person(){
    infectedPeriod = 0;
    mask = false;
    socialDistance =  false;

    //direction here represents up down left right
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
//    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    direction =0;
    status = vulnerable;
    //roughly 27% non-elder people in the US has preexisting conditions
    //source: https://www.kff.org/policy-watch/pre-existing-conditions-what-are-they-and-how-many-people-have-them/#:~:text=KFF%20has%20estimated%20that%20in,ACA%20individual%20health%20insurance%20market.
    std::uniform_int_distribution<int> distributionPreCond(0,100);
    int ran = distributionPreCond(generator);
    medicalCondition = ran < 27;
    //we assume age is randomly distributed between 15 to 80
    std::uniform_int_distribution<int> distributionAge(0,66);
    age= distributionAge(generator)+15;

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
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    direction = 0;
    status = sta;
    //direction here represents up down left right

    //roughly 27% non-elder people in the US has preexisting conditions
    //source: https://www.kff.org/policy-watch/pre-existing-conditions-what-are-they-and-how-many-people-have-them/#:~:text=KFF%20has%20estimated%20that%20in,ACA%20individual%20health%20insurance%20market.
    std::uniform_int_distribution<int> distributionPreCond(0,100);
    int ran = distributionPreCond(generator);
    medicalCondition = ran < 27;
    //we assume age is randomly distributed between 15 to 80
    std::uniform_int_distribution<int> distributionAge(0,66);
    age= distributionAge(generator)+15;

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
    direction= p.direction;
    status = p.status;
    infectedPeriod=p.infectedPeriod;
    human = p.human;
}
person& person::operator =(const person& p){
    mask = p.mask;
    medicalCondition = p.medicalCondition;
    socialDistance = p.socialDistance;
    direction= p.direction;
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
int person::getDirection(){
    return direction;
}

void person::setDirection(int d){
    //use setdirection with engine in community for randomness

    direction=d;
}
CircleShape& person::getShape(){
    return human;
}
void person::setPosition(float x,float y){
    human.setPosition(Vector2f(x,y));
}

void person:: move(float xBoundLeft,float xBoundRight, float yBoundUp, float yBoundDown){
    //the four parameters here are the x and y boundary
    //this function moves people around
    //direction diagram
    //    1
    //0       2
    //    3
    Vector2f pos = human.getPosition();
    cout<<"Direction: "<<direction<<endl;
    if(direction==0 && pos.x>xBoundLeft){
        human.move(-1.2f,0.0f);
        //move left
    }
    else if(direction==0 && pos.x<=xBoundLeft){
        direction =2;
        human.move(1.2f,0.0f);
        //making the people "bounce" from the boundries
    }

    else if(direction ==1 && pos.y>yBoundUp){
        human.move(0.0f,-1.2f);
        //move up
    }
    else if(direction==1 && pos.y<=yBoundUp){
        direction =3;
        human.move(0.0f,1.2f);
        //bounce down
    }

    else if(direction ==2 && pos.x<xBoundRight){
        human.move(1.2f,0.0f);
        //move right
    }
    else if(direction ==2 && pos.x>=xBoundRight){
        direction=0;
        human.move(-1.2f,0.0f);
        //bounce left
    }
    else if(direction ==3 && pos.y<yBoundDown){
        human.move(0.0f,1.2f);
        //move down
    }
    else if(direction==3 && pos.y>= yBoundDown){
        direction=1;
        human.move(0.0f,-1.2f);
        //bounce up
    }

}


void person::changeDirection(){
    //abondoned
    //not random enough
    int pre = direction;
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0,3);
    while(pre==direction){
        direction =distribution(generator);
    }

    //here we change the direction randomly to another one
}