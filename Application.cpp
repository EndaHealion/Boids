#include "Application.h"

Application::Application() {
    initWindow();
    initFlock();
}

void Application::initWindow() {
    sf::VideoMode videoMode(1920, 1080, 1);
    window.create(videoMode, "Flock off", sf::Style::Fullscreen);
    // window.setFramerateLimit(60);
}

void Application::run() {
    while (window.isOpen()) {
        pollEvents();
        update();
        render();
    }
}

void Application::pollEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        // This is wrapped in a switch statement to stop boids from being placed every frame that left button is held down
        // It current places one per mouse click
        switch (event.type) {
            case sf::Event::MouseButtonPressed: {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    addBoidToFlock(mousePos.x, mousePos.y);
                }
            }
        }
    }
}

void Application::addBoidToFlock(float x, float y) {
    Boid b(x, y);
    flock.addBoid(b);
}

void Application::update() {
    flock.update();
}

void Application::initFlock() {
    for (int x = 0; x < 12; x++) {
        for (int y = 0; y < 12; y++) {
            addBoidToFlock(x * 150, y * 85);
        }
    }
}

void Application::render() {
    window.clear(sf::Color::Black);
    flock.render(&window);
    window.display();
}