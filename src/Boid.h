#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Colours.h"

class Boid {
public:
private:
    sf::VertexArray boid = sf::VertexArray(sf::PrimitiveType::Triangles, 3);

    const float boidSize = 20;
    const float desiredSeparation = 50;
    const float maxSpeed = 3.5f;
    const float maxForce = 0.5f;

    // Remember to change these when changing window resolution
    const int screenHeight = 1080;
    const int screenWidth = 1920;

    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    Colours colours;

public:
    Boid();
    Boid(float x, float y);

    void run(std::vector<Boid>* boidVec);
    void render(sf::RenderWindow* window);

private:
    void applyForce(sf::Vector2f force);
    float distanceBetween(sf::Vector2f pos1, sf::Vector2f pos2);
    float angle(sf::Vector2f position);
    sf::Vector2f normalise(sf::Vector2f pos);
    sf::Vector2f limit(sf::Vector2f pos, float limitAmount);

    sf::Vector2f separate(std::vector<Boid>* boidVec);
    sf::Vector2f align(std::vector<Boid>* boidVec);
    sf::Vector2f cohere(std::vector<Boid>* boidVec);
    
    void flock(std::vector<Boid>* boidVec);
    void update();
    void windowWrap();
};