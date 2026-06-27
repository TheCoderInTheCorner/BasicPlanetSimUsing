#ifndef BODY_CLASS
#define BODY_CLASS

#include <iostream>
#include "SFML/Graphics.hpp"

class PlanetaryBody{
    public:
    PlanetaryBody(sf::Vector2f p,sf::Vector2f vel,sf::Vector2f acc, float m,float s);
    
    //Getters
    sf::Vector2f getPos();
    sf::Vector2f getVel();
    sf::Vector2f getAcc();
    float getMass();
    float getSize();
    float getID();

    //setters
    void setPos(sf::Vector2f newPos);
    void setVel(sf::Vector2f newVel);
    void setAcc(sf::Vector2f newAcc);
    void setMass(float newMass);
    void setSize(float newSize);

    
    private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;
    float size;
    int id;
    static int num;


};

#endif