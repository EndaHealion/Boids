#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Flock.h"

class Application {
private:
    sf::RenderWindow window;
    Flock flock;

public:
    Application();
    void run();

private:
    void initWindow();
    void initFlock();
    void render();
    void pollEvents();
    void addBoidToFlock(float x, float y);
    void update();
};