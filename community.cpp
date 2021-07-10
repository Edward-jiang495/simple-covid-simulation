//
// Created by 18502 on 6/16/2021.
//

#include "community.h"
community::community(){
    //initialize population here
    //we maybe should start with 1 infected patient
    days=1;
    //start on day 1
    size =30;
    width=1000;
    height=600;
    vacDevTime=5;
    maskMandate =0.2;
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distributionX(200.0,width-200);
    //generate random number for x coordinates
    std::uniform_real_distribution<float> distributionY(100.0,height-100);
    //generate random number for y coordinates
    //generating random number for people ages
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
community::community(int s, int m, int d, double ma){
    //initialize population here
    size =s;
    days=1;
    //start on day 1
    width=1000;
    height=600;
    vacDevTime =d;
    maskMandate=ma;
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distributionX(200.0,width-200);
    //generate random number for x coordinates
    std::uniform_real_distribution<float> distributionY(100.0,height-100);
    //generate random number for y coordinates
    std::uniform_int_distribution<int> dir(0,7);
    std::uniform_int_distribution<int> distributionPreCond(0,100);
    //generate random number for people with or without preexisting condition
    //roughly 27% non-elder people in the US has preexisting conditions
    //source: https://www.kff.org/policy-watch/pre-existing-conditions-what-are-they-and-how-many-people-have-them/#:~:text=KFF%20has%20estimated%20that%20in,ACA%20individual%20health%20insurance%20market.
    std::uniform_int_distribution<int> distributionAge(0,62);
    std::uniform_int_distribution<int> masks(0,99);
    bool hasMask=false;
    bool hasCond =false;
    for(int i=0;i<size;i++){
        if(distributionPreCond(generator) <27){
            hasCond=true;
        }
        if(masks(generator) < m){
            hasMask=true;
        }
        int age = distributionAge(generator)+18;
//        cout<<age<<" ";
        person p(hasMask,hasCond,age);
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
    window.create(sf::VideoMode(width, height), "Covid Community Simulation", Style::Close);
   //make person move here

    float borderWidth = width-300.0f;
    float borderHeight = height-100.0f;
    RectangleShape border(Vector2f(borderWidth,borderHeight));
    border.setFillColor(Color::Black);
    border.setOutlineThickness(3.0f);
    border.setOutlineColor(Color::White);
    border.setOrigin(Vector2f(borderWidth/2,borderHeight/2));
    border.setPosition(Vector2f(width/2,height/2));
    //this rectangle shape is designed to be a border that people cannot move out

    sf::Font font;
// Load it from a file
    if (!font.loadFromFile("../arial.ttf"))
    {
        cout<<"Cannot open font files"<<endl;
    }

    //creating the display string
    //this is the number of day passed
    Text day;
    day.setString("Day: " + to_string(days));
    day.setFont(font);
    day.setStyle(sf::Text::Regular);
    day.setCharacterSize(24);
//    day.setPosition(0,0);

    Text vulNum;
    vulNum.setString("Vulnerable: " + to_string(vulnerableNum));
    vulNum.setFont(font);
    vulNum.setStyle(sf::Text::Regular);
    vulNum.setCharacterSize(24);
    vulNum.setPosition(150,0);

    Text infNum;
    infNum.setPosition(400,0);
    infNum.setString("Infected: " + to_string(infectedNum));
    infNum.setFont(font);
    infNum.setStyle(sf::Text::Regular);
    infNum.setCharacterSize(24);

    Text deaNum;
    deaNum.setPosition(600,0);
    deaNum.setString("Death: " + to_string(deathNum));
    deaNum.setFont(font);
    deaNum.setStyle(sf::Text::Regular);
    deaNum.setCharacterSize(24);

    Text recNum;
    recNum.setPosition(800,0);
    recNum.setString("Recovered: " + to_string(recoveredNum));
    recNum.setFont(font);
    recNum.setStyle(sf::Text::Regular);
    recNum.setCharacterSize(24);


    Clock clock;
    //begin our timer
    int startdate=-1;
    //starting date to create the vaccine
    //we assume that the vaccination will take 5 days

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

        window.draw(day);
        window.draw(border);
        window.draw(vulNum);
        window.draw(infNum);
        window.draw(recNum);
        window.draw(deaNum);
        Time time = clock.getElapsedTime();
        float sec  = time.asSeconds();
        if(deathNum/double(infectedNum) > 0.1 && startdate ==-1){
            //if death rate reaches over 10% in the infected population
            //start vaccinating people
            //in real life, vaccination takes time to invent and
            //some might need a booster shoot
            //in this simulation we assume one shot is sufficient and vaccinated
            //individual will not catch the disease anymore
            startdate =days;
        }
        if(sec > 1.0f){
            int seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine generator(seed);
            std::uniform_int_distribution<int> dist(0,100);
            for(int k=0;k<peoples.size();k++){
                //this for loop is responsible for day counts
                //and whether infected person passed away or recovered
                int chance = dist(generator);
                bool dead = peoples.at(k).passAway(chance);
                if(dead){
                    deathNum++;
                    infectedNum--;
                    infNum.setString("Infected: " + to_string(infectedNum));
                    deaNum.setString("Death: " + to_string(deathNum));
                }
                chance = dist(generator);
                bool recovered = peoples.at(k).recover(chance);
                if(recovered){
                    recoveredNum++;
                    infectedNum--;
                    infNum.setString("Infected: " + to_string(infectedNum));
                    recNum.setString("Recovered: " + to_string(recoveredNum));
                }

                if(deathNum/double(infectedNum) > maskMandate){
                    peoples.at(k).setMask(true);
                    //mask mandate starts at the same time
                    //when vaccination is in development
                }

                if(days - startdate >=vacDevTime){
                    chance = dist(generator);
                    bool vaccinated = peoples.at(k).vaccinate(chance);
                    if(vaccinated){
                        recoveredNum++;
                        vulnerableNum--;
                        vulNum.setString("Vulnerable: " + to_string(vulnerableNum));
                        recNum.setString("Recovered: " + to_string(recoveredNum));
                    }
                }


                window.draw(peoples.at(k).getShape());

            }
            days++;
            day.setString("Day: " + to_string(days));
            clock.restart();
        }

        for(int i=0;i<size;i++){
            //we use brute force method for collision detection between multiple people
            if(peoples.at(i).getStatus() != person::disease_status::dead){
                peoples.at(i).move((width-borderWidth)/2,(width+borderWidth)/2,(height-borderHeight)/2,(height+borderHeight)/2);
                for(int j=0;j<size;j++){
                    if(j==i){
                        continue;
                        //cannot infect himself/herself
                    }
                    else if(peoples.at(i).getStatus() == person::disease_status::infected){
                        bool infected = peoples.at(i).infectOther(peoples.at(j));
                        if(infected){
                            infectedNum++;
                            vulnerableNum--;
                            vulNum.setString("Vulnerable: " + to_string(vulnerableNum));
                            infNum.setString("Infected: " + to_string(infectedNum));
                        }
                    }
                }

            }
            window.draw(peoples.at(i).getShape());
        }

        window.display();


    }
}
