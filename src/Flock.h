#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Boid.h"

class Flock {
private:
    std::vector<Boid> flock = std::vector<Boid>();

public:
    Flock();
    Flock(std::vector<Boid>* startFlock);
    
    void update();
    void render(sf::RenderWindow* window);

    void addBoid(Boid boid);
    int getSize();
    Boid getBoid(int index);
};