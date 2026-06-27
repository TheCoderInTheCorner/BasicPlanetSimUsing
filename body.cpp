#include <iostream>
#include "SFML/Graphics.hpp"
#include "./Include/body.hpp"

int PlanetaryBody::num = 0;

PlanetaryBody::PlanetaryBody(sf::Vector2f p,sf::Vector2f vel,sf::Vector2f acc, float m,float s){
    position = p;
    velocity=vel;
    acceleration = acc;
    mass = m;
    size = s;
    num++;
    id = num;
}

//getters
sf::Vector2f PlanetaryBody::getPos(){return position;}
sf::Vector2f PlanetaryBody::getVel(){return velocity;}
sf::Vector2f PlanetaryBody::getAcc(){return acceleration;}
float PlanetaryBody::getMass(){return mass;}
float PlanetaryBody::getSize(){return size;}
float PlanetaryBody::getID(){return id;}

//Setters
void PlanetaryBody::setPos(sf::Vector2f newPos){position = newPos;}
void PlanetaryBody::setVel(sf::Vector2f newVel){velocity=newVel;}
void PlanetaryBody::setAcc(sf::Vector2f newAcc){acceleration=newAcc;}
void PlanetaryBody::setMass(float newMass){mass=newMass;}
void PlanetaryBody::setSize(float newSize){size=newSize;}