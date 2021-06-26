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
    if(status==infected){
        human.setFillColor(Color::Red);
    }
    else if(status== vulnerable){
        human.setFillColor(Color::Blue);
    }
    else if(status== dead){
        Color color(128,128,128);
        //this is gray
        human.setFillColor(color);
    }
    else if(status==immune){
        human.setFillColor(Color::Green);
    }
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
    //4   0   5
    //1       2
    //6   3   7
    //0,1,2,3 represents up left right down
    //people can move up down left right and diagonally
    cout<<"Direction: "<<direction<<endl;
    if(direction<4){
        moveWayward(xBoundLeft,xBoundRight,yBoundUp,yBoundDown);
    }
    else{
        moveDiagonally(xBoundLeft,xBoundRight,yBoundUp,yBoundDown);
    }

}
void person:: moveWayward(float xBoundLeft,float xBoundRight, float yBoundUp, float yBoundDown){
    Vector2f pos = human.getPosition();
//    cout<<"Direction: "<<direction<<endl;
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

void person:: moveDiagonally(float xBoundLeft,float xBoundRight, float yBoundUp, float yBoundDown){
    Vector2f pos = human.getPosition();

    //this function moves people left up
    if(direction==4){
        if(pos.x> xBoundLeft && pos.y > yBoundUp){
            human.move(-1.2f,-1.2f);
            //move left up
            return;
        }
        else if(pos.x> xBoundLeft && pos.y <= yBoundUp ){
            //we touch the upper bound without touching the left bound
            direction=6;
            //we change direction from left up to left down
            human.move(-1.2f,1.2f);
            //move left down
            return ;
        }
        else if(pos.x <= xBoundLeft && pos.y >yBoundUp){
            //we touch the left bound without touching the upper bound
            direction= 5;
            human.move(1.2f,-1.2f);
            //move left up
            return ;
        }
        else{
            //we touch the very left up corner
            direction = 7;
            human.move(1.2f,1.2f);
            return;
        }
    }

    //this moves right up
    else if(direction==5){
        if(pos.x < xBoundRight && pos.y > yBoundUp){
            human.move(1.2f,-1.2f);
            return;
        }
        else if(pos.x < xBoundRight && pos.y <=yBoundUp){
            //we touch the up boundary without touching the right one
            direction=7;
            human.move(1.2,1.2);
            //move right down
            return;
        }
        else if(pos.x >=xBoundRight && pos.y > yBoundUp){
            //we touch the right boundary with touching the up one
            direction =4;
            human.move(-1.2,-1.2);
            //move left up
            return;
        }
        else{
            //we touch the right up corner
            direction =6;
            human.move(-1.2,1.2);
            //move left down
            return;
        }
    }

    //this function moves left down
    else if(direction==6){
        if(pos.x > xBoundLeft && pos.y < yBoundDown){
            human.move(-1.2,1.2);
            return ;
        }
        else if(pos.x > xBoundLeft && pos.y >=yBoundDown){
            //we touch the lower boundary without touching the left one
            direction =4;
            human.move(-1.2,-1.2);
            return;
        }
        else if(pos.x <=xBoundLeft && pos.y <yBoundDown){
            //we touch the left boundary without touching the lower one
            direction =7;
            human.move(1.2,1.2);
            return;
        }
        else{
            //we touch the left lower corner
            direction =5;
            human.move(1.2,-1.2);
        }
    }

    //this is for moving right down
    else if(direction==7){
        if(pos.x < xBoundRight && pos.y < yBoundDown){
            human.move(1.2,1.2);
            return;
        }
        else if(pos.x <xBoundRight && pos.y >= yBoundDown){
            //we touch the lower bound without touching the right one
            direction = 5;
            human.move(1.2,-1.2);
            return;
        }
        else if(pos.x >= xBoundRight && pos.y <=yBoundDown){
            //we touch the right bound without touching the lower one
            direction = 6;
            human.move(-1.2,1.2);
            return;
        }
        else{
            //we touch the right lower corner
            direction =4;
            human.move(-1.2,-1.2);
            return;
        }
    }
    else{
        cout<<"Invalid direction detected"<<endl;
    }

}
Vector2f person::getPosition(){
    return human.getPosition();
}
void person::infectOther(person& p){
    //each dot(human) radius is 6
    //so we reduce the function calls getRadius
    //and use 6 directly
    //the sum of two circle with radius 6 is 12
    if(status==infected){
        Vector2f pos1 = human.getPosition();
        Vector2f pos2 = p.human.getPosition();
        float dx = pos1.x - pos2.x;
        float dy = pos1.y - pos2.y;
        float dis = sqrt(dx*dx + dy*dy);
        if(dis< 12){
            p.human.setFillColor(Color::Red);
            p.status =infected;
        }
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