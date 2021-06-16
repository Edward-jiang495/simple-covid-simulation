#include <SFML/Graphics.hpp>
#include <iostream>
#include "community.h"
using namespace std;
using namespace sf;

bool locationAllowedUp(Shape& shape);

bool locationAllowedDown(Shape& shape);

bool locationAllowedLeft(Shape& shape);

bool locationAllowedRight(Shape& shape);

int main()
{
// create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window", Style::Close);
//  width(x): 800
//  height(y): 600
    float width =200.0f;
    float height = 100.0f;
    RectangleShape example(Vector2f(width,height));
    example.setFillColor(Color::White);

    example.setOrigin(Vector2f(100.0f,50.0f));
    example.setPosition(Vector2f(100.0f,54.0f));

    Texture exampleTexture;
    exampleTexture.loadFromFile("../sekiro.jpg");
    example.setTexture(&exampleTexture);

    RectangleShape example2(Vector2f(width,height));
    example2.setFillColor(Color::White);

    example2.setOrigin(Vector2f(100.0f,50.0f));
    example2.setPosition(Vector2f(699.0f,54.0f));
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

        }
        if(Mouse::isButtonPressed(Mouse::Left)){
            Vector2i ans = Mouse::getPosition(window);
//            cout<<ans.x<<" "<<ans.y<<endl;
            example.setPosition(static_cast<float>(ans.x), static_cast<float>(ans.y));
        }

        if(Mouse::isButtonPressed(Mouse::Right)){
            Vector2i ans = Mouse::getPosition(window);
//            cout<<ans.x<<" "<<ans.y<<endl;
            example2.setPosition(static_cast<float>(ans.x), static_cast<float>(ans.y));
        }

        if(Keyboard::isKeyPressed(Keyboard::Key::A) && locationAllowedLeft(example)){
            example.move(-0.1f,0.0f);
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::W) && locationAllowedUp(example)){
            example.move(0.0f,-0.1f);
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::S) && locationAllowedDown(example)){
            example.move(0.0f,0.1f);
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::D) && locationAllowedRight(example)){
            example.move(0.1f,0.0f);
        }

        if(Keyboard::isKeyPressed(Keyboard::Key::Left) && locationAllowedLeft(example2)){
            example2.move(-0.1f,0.0f);
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::Up) && locationAllowedUp(example2)){
            example2.move(0.0f,-0.1f);
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::Down) && locationAllowedDown(example2)){
            example2.move(0.0f,0.1f);
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::Right) && locationAllowedRight(example2)){
            example2.move(0.1f,0.0f);
        }
        // clear the window with black color

        Vector2f pos1 =example.getPosition();
        Vector2f pos2 =example2.getPosition();
        float x1 = pos1.x;
        float y1 = pos1.y;
        float x2 = pos2.x;
        float y2 = pos2.y;
        if (x1 < x2 + width &&
            x1 + width > x2 &&
            y1 < y2 + height &&
            y1 + height > y2) {
            cout<<"Collided"<<endl;
//            collision detected!
        }
        window.clear();

        // draw everything here...
        window.draw(example);
        window.draw(example2);
        // end the current frame
        window.display();
    }
//    community test;
//    test.run();

    return 0;
}

bool locationAllowedUp(Shape& shape){
    sf::Vector2f temp = shape.getPosition();
    float y = temp.y - 0.1f;
    if (y < 50) {
        return false;
    }

    return true;
}

bool locationAllowedDown(Shape& shape){
    sf::Vector2f temp = shape.getPosition();
    float y = temp.y + 0.1f;
    if (y > 550) {
        return false;
    }

    return true;
}

bool locationAllowedLeft(Shape& shape){
    sf::Vector2f temp = shape.getPosition();
    float x = temp.x - 0.1f;
    if (x < 100) {
        return false;
    }
    return true;
}

bool locationAllowedRight(Shape& shape){
    sf::Vector2f temp = shape.getPosition();
    float x = temp.x + 0.1f;
    if (x > 700) {
        return false;
    }
    return true;
}