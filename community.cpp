//
// Created by 18502 on 6/16/2021.
//

#include "community.h"
community::community(){
    //initialize population here
    //we maybe should start with 1 infected patient
    days=0;
    size =30;
    lockDown=false;
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distributionX(100.0,700.0);
    //generate random number for x coordinates
    std::uniform_real_distribution<float> distributionY(100.0,500.0);
    //generate random number for y coordinates
    std::uniform_int_distribution<int> dir(0,3);
    for(int i=0;i<size;i++){
        person p;
        float x = distributionX(generator);
        float y = distributionY(generator);
        p.setPosition(x,y);
        p.setDirection(dir(generator));
        peoples.push_back(p);
    }



}
community::community(int s, bool l){
    //initialize population here
    size =s;
    lockDown= l;
    days=0;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distributionX(100.0,700.0);
    //generate random number for x coordinates
    std::uniform_real_distribution<float> distributionY(100.0,500.0);
    //generate random number for y coordinates
    for(int i=0;i<size;i++){
        person p;
        float x = distributionX(generator);
        float y = distributionY(generator);
        p.setPosition(x,y);
        peoples.push_back(p);
    }

}

void community::run(){
    window.close();
    window.create(sf::VideoMode(800, 600), "Covid Community Simulation", Style::Close);
   //make person move here

    RectangleShape border(Vector2f(700.0f,500.0f));
    border.setFillColor(Color::Black);
    border.setOutlineThickness(3.0f);
    border.setOutlineColor(Color::White);
    border.setOrigin(Vector2f(350.0f,250.0f));
    border.setPosition(Vector2f(400.0f,300.0f));
    //this rectangle shape is designed to be a border that people cannot move out

    while (window.isOpen()) {
// check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

        }
        // draw everything here...
        window.clear();
        window.draw(border);
        for(int i=0;i<size;i++){
            peoples.at(i).move(50,750,50,550);
            window.draw(peoples.at(i).getShape());
        }
        window.display();

    }
}
