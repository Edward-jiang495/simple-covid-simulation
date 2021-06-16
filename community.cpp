//
// Created by 18502 on 6/16/2021.
//

#include "community.h"
community::community(){
    //initialize population here
    //we maybe should start with 1 infected patient
    days=0;
    size =50;
    lockDown=false;

}
community::community(int s, bool l){
    //initialize population here
    size =s;
    lockDown= l;
    days=0;

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
        window.clear();

        // draw everything here...
        window.draw(border);
        // end the current frame
        window.display();
    }
}
