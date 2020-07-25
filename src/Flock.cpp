#include "Flock.h"

Flock::Flock() {}

Flock::Flock(std::vector<Boid>* startFlock) : flock(*startFlock) {
}

inline int Flock::getSize() {
    return flock.size();
}

Boid Flock::getBoid(int index) {
    return flock[index];
}

void Flock::addBoid(Boid boid) {
    flock.push_back(boid);
}

void Flock::update() {
    for (int i = 0; i < flock.size(); i++) {
        flock[i].run(&flock);
    }
}

void Flock::render(sf::RenderWindow* window) {
    for (int i = 0; i < flock.size(); i++) {
        flock[i].render(window);
    }
}
