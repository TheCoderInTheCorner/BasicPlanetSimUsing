#include <iostream>
#include <cmath>
#include "SFML/Graphics.hpp"
#include "./Include/body.hpp"
// Each planet includes
/*
sf::Vector2f position;
sf::Vector2f velocity;
sf::Vector2f acceleration;
float mass;
float size; //megameters
int id;
*/

//functions 
void drawPlanets(std::vector<PlanetaryBody*> allPlanets, sf::RenderWindow& window);
void updatePlanets(std::vector<PlanetaryBody*> allPlanets);

sf::Vector2f getCorrectPos(sf::Vector2f currentPos);

//Other variables
const double universalG = 6.674e-11;

//window dimensions
unsigned int windowWidth = 1500;
unsigned int windowHeight = 1000;
int main(){
    std::vector<PlanetaryBody*> planets;
    PlanetaryBody bodyOne = PlanetaryBody({0.f,0.f}, {0.f,0.f}, {0.f,0.f}, 5.972e10f, 6.32f);
    PlanetaryBody bodyTwo = PlanetaryBody({300.f,300.f}, {-0.05f,0.f}, {0.f,0.f}, 5.972e10f, 6.f);
    PlanetaryBody bodyThree = PlanetaryBody({-300.f,-300.f}, {0.05f,-0.03f}, {0.f,0.f}, 5.972e10f, 6.f);
    
    
    planets.emplace_back(&bodyOne);
    planets.emplace_back(&bodyTwo);
    planets.emplace_back(&bodyThree);



    std::cout<<"Body One ID: "<<(*planets[0]).getID()<<"\n";
    std::cout<<"Body Two ID: "<<bodyTwo.getID()<<"\n";
    sf::RenderWindow window(sf::VideoMode({windowWidth,windowHeight}), "multBodies");

    while(window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();

            }
        }
        window.clear(sf::Color::Black);
        updatePlanets(planets);
        drawPlanets(planets, window);
        std::cout<<"PLanet Acc: "<<bodyOne.getAcc().x<<", "<<bodyOne.getAcc().y<<")\n";
        window.display();
    }
    return 0;
}

void drawPlanets(std::vector<PlanetaryBody*> allPlanets, sf::RenderWindow& window){
    for(int i = 0; i<allPlanets.size(); i++){
        sf::CircleShape planet((*allPlanets[i]).getSize());
        planet.setOrigin({(*allPlanets[i]).getSize(), (*allPlanets[i]).getSize()});
        planet.setPosition(getCorrectPos((*allPlanets[i]).getPos()));
        planet.setFillColor(sf::Color::White);
        window.draw(planet);
    }  
}

void updatePlanets(std::vector<PlanetaryBody*> allPlanets){
    // update acceleration for each of the planets
    // we get one planet and for each planet in all planets
    // we update accelerationa ccordingly
    //!REMEMBER: CANNOt USE OWN PLANET IN PLANET VECTOR TO UPDATE ACC
    
    for(int planetID = 0; planetID<allPlanets.size(); planetID++){
        PlanetaryBody& planet = *allPlanets[planetID];
        planet.setAcc({0.f,0.f});
        for(int planet2ID = 0; planet2ID<allPlanets.size(); planet2ID++){
            PlanetaryBody& planet2 = *allPlanets[planet2ID];
            if(planet2.getID() != planet.getID()){
                float distance = std::sqrt(std::pow(planet.getPos().x - planet2.getPos().x, 2) + std::pow(planet.getPos().y - planet2.getPos().y, 2) );
                if(distance<=0.0000001){distance = 0.01;}
                sf::Vector2f planetsOffset = {planet2.getPos().x - planet.getPos().x, planet2.getPos().y - planet.getPos().y};
                double force = universalG*((planet2.getMass()*planet.getMass())/std::pow(distance, 2));
                
                
                //!ADD FORCE MULTIPLIER
                sf::Vector2f accToPlan2 = {planetsOffset.x/distance, planetsOffset.y/distance};
                accToPlan2.x*=force/planet.getMass();
                accToPlan2.y*=force/planet.getMass();

                planet.setAcc({planet.getAcc().x+accToPlan2.x, planet.getAcc().y+accToPlan2.y});
            }
        }
        planet.setVel({planet.getVel().x+planet.getAcc().x, planet.getVel().y+planet.getAcc().y});
        planet.setPos({planet.getPos().x+planet.getVel().x, planet.getPos().y+planet.getVel().y});
    }
}


sf::Vector2f getCorrectPos(sf::Vector2f currentPos){
    sf::Vector2f returnVector = {0.f,0.f};
    returnVector.x = (windowWidth/2) + currentPos.x;
    returnVector.y = (windowHeight/2) + (currentPos.y*-1);
    return returnVector;
}

//hey guys so update, now multiple bodies can interact with each other and their masses influence the masses of other objects. still am questioning its accuracy but the thing is I used floating point instead of long doubles so the accuracy is like aactual shit. Im lowk trynna fix it lowk 