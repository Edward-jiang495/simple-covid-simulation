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
    std::uniform_int_distribution<int> dir(0,7);
    for(int i=0;i<size;i++){
        person p;
        float x = distributionX(generator);
        float y = distributionY(generator);
        p.setPosition(x,y);
        p.setDirection(dir(generator));
        peoples.push_back(p);
    }
    peoples.at(0).setStatus(person::disease_status::infected);
    //we select the zeroth index patient as the
    //first infected one
    infectedNum=1;
    vulnerableNum =size-1;
    deathNum = 0;
    recoveredNum =0;


}
community::community(int s, bool l){
    //initialize population here
    size =s;
    lockDown= l;
    days=0;
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distributionX(100.0,700.0);
    //generate random number for x coordinates
    std::uniform_real_distribution<float> distributionY(100.0,500.0);
    //generate random number for y coordinates
    std::uniform_int_distribution<int> dir(0,7);
    for(int i=0;i<size;i++){
        person p;
        float x = distributionX(generator);
        float y = distributionY(generator);
        p.setPosition(x,y);
        p.setDirection(dir(generator));
        peoples.push_back(p);
    }
    peoples.at(0).setStatus(person::disease_status::infected);
    infectedNum=1;
    vulnerableNum =size-1;
    deathNum = 0;
    recoveredNum =0;

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

    sf::Font font;
// Load it from a file
    if (!font.loadFromFile("../arial.ttf"))
    {
        cout<<"Cannot open font files"<<endl;
    }

    //creating the display string
    Text vulNum;
    vulNum.setString("Vulnerable: " + to_string(vulnerableNum));
    vulNum.setFont(font);
    vulNum.setStyle(sf::Text::Regular);
    vulNum.setCharacterSize(24);

    Text infNum;
    infNum.setPosition(200,0);
    infNum.setString("Infected: " + to_string(infectedNum));
    infNum.setFont(font);
    infNum.setStyle(sf::Text::Regular);
    infNum.setCharacterSize(24);

    Text deaNum;
    deaNum.setPosition(400,0);
    deaNum.setString("Death: " + to_string(deathNum));
    deaNum.setFont(font);
    deaNum.setStyle(sf::Text::Regular);
    deaNum.setCharacterSize(24);

    Text recNum;
    recNum.setPosition(600,0);
    recNum.setString("Recovered: " + to_string(recoveredNum));
    recNum.setFont(font);
    recNum.setStyle(sf::Text::Regular);
    recNum.setCharacterSize(24);


    while (window.isOpen()) {
// check all the window's events that were triggered since the last iteration of the loop
        Event event{};
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

        }
        // draw everything here...
        window.clear();

        window.draw(border);
        window.draw(vulNum);
        window.draw(infNum);
        window.draw(recNum);
        window.draw(deaNum);
        for(int i=0;i<size;i++){
            peoples.at(i).move(50,750,50,550);
            for(int j=0;j<size;j++){
                if(j==i){
                    continue;
                    //cannot infect himself/herself
                }
                else if(peoples.at(i).getStatus() == person::disease_status::infected){
                    Vector2f pos1 = peoples.at(i).getPosition();
                    Vector2f pos2 = peoples.at(j).getPosition();
                    float dx = pos1.x - pos2.x;
                    float dy = pos1.y - pos2.y;
                    float dis = sqrt(dx*dx + dy*dy);
                    if(dis< 12 && peoples.at(j).getStatus() ==person::disease_status::vulnerable){
                        //only transmit when one is infected and the other is vulnerable
                        //and close enough
                        peoples.at(j).setStatus(person::disease_status::infected);
                        infectedNum++;
                        vulnerableNum--;
                        vulNum.setString("Vulnerable: " + to_string(vulnerableNum));
                        infNum.setString("Infected: " + to_string(infectedNum));
                    }
                }
            }
            window.draw(peoples.at(i).getShape());
        }
        window.display();

    }
}
