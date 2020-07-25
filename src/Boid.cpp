#include "Boid.h"

constexpr float PI = 3.141592635f;

Boid::Boid() {}

Boid::Boid(float x, float y) {
    acceleration = sf::Vector2f(0, 0);
    velocity = sf::Vector2f(rand() % 6 - 3, rand() % 6 - 3);
    position = sf::Vector2f(x, y);
}

// Adds force sf::Vector2f to current force sf::Vector2f
void Boid::applyForce(sf::Vector2f force) {
    acceleration += force;
}

// Separation: steer to avoid crowding local flockmates
sf::Vector2f Boid::separate(std::vector<Boid>* boidVec) {
    sf::Vector2f steer(0, 0);
    int boidCount = 0;
    for (int i = 0; i < boidVec->size(); i++) {
        float d = distanceBetween(position, (*boidVec)[i].position);
        if ((&(*boidVec)[i] != this) && (d < desiredSeparation)) {
            sf::Vector2f diff(0, 0);
            diff = (position - (*boidVec)[i].position);
            diff /= (d*d);
            steer += diff;
            boidCount++;
        }
    }
    if (boidCount > 0) {
        steer /= (float)boidCount;
        steer = (maxSpeed * normalise(steer));
        steer -= velocity;
        steer = limit(steer, maxForce);
    }
    return steer;
}

// Alignment: steer towards the average heading of local flockmates
sf::Vector2f Boid::align(std::vector<Boid>* boidVec) {
    float perceptionRadius = 50;
    sf::Vector2f steer(0, 0);
    int boidCount = 0;
    for (int i = 0; i < boidVec->size(); i++) {
        float d = distanceBetween(position, (*boidVec)[i].position);
        if ((&(*boidVec)[i] != this) && (d < perceptionRadius)) {
            steer += (*boidVec)[i].velocity;
            boidCount++;
        }
    }
    if (boidCount > 0) {
        steer /= (float)boidCount;
        steer = (maxSpeed * normalise(steer));
        steer -= velocity;
        steer = limit(steer, maxForce);
    }
    return steer;
}

// Cohesion: steer to move towards the average position of local flockmates
sf::Vector2f Boid::cohere(std::vector<Boid>* boidVec) {
    float perceptionRadius = 55;
    sf::Vector2f steer(0, 0);
    int boidCount = 0; 
    for (int i = 0; i < boidVec->size(); i++) {
        float d = distanceBetween(position, (*boidVec)[i].position);
        if ((&(*boidVec)[i] != this) && (d < perceptionRadius)) {
            steer += (*boidVec)[i].position;
            boidCount++;
        }
    }
    if (boidCount > 0) {
        steer /= (float)boidCount;
        steer -= position;
        steer = (maxSpeed * normalise(steer));
        steer -= velocity;
        steer = limit(steer, maxForce);
    }
    return steer;
}

// Euclidean distance between two vectors
float Boid::distanceBetween(sf::Vector2f pos1, sf::Vector2f pos2) {
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    return std::sqrt(dx * dx + dy * dy);
}

sf::Vector2f Boid::normalise(sf::Vector2f pos) {
    float x = pos.x;
    float y = pos.y;
    float magnitude = sqrt(x * x + y * y);
    if (magnitude != 0) {
        return sf::Vector2f(x / magnitude, y / magnitude);
    }
    else return pos;
}

// limits the magnitude of a vector to some given limit
sf::Vector2f Boid::limit(sf::Vector2f pos, float limitAmount) {
    float x = pos.x;
    float y = pos.y;
    float magnitude = sqrt(x * x + y * y);

    if (magnitude > limitAmount) {
        return sf::Vector2f(x * (limitAmount / magnitude), y * (limitAmount / magnitude));
    }
    else return pos;
}

void Boid::update() {
    acceleration *= 0.7f;
    velocity += acceleration;
    velocity = limit(velocity, maxSpeed);
    position += velocity;
    acceleration *= 0.0f;
}

void Boid::run(std::vector<Boid>* boidVec) {
    flock(boidVec);
    update();
    windowWrap();
}

void Boid::render(sf::RenderWindow* window) {
    sf::Vector2f offset = boidSize * normalise(velocity);
    float boidAngle = angle(offset) + (PI / 2);
    sf::Vector2f triangleBase((boidSize / 2) * std::cos(boidAngle), (boidSize / 2) * std::sin(boidAngle));
    sf::Color triangleBaseColour = colours.chooseColour(boidAngle - (PI / 2));

    boid[0] = sf::Vertex(position + offset, triangleBaseColour);
    boid[1] = sf::Vertex(position + triangleBase, triangleBaseColour);
    boid[2] = sf::Vertex(position - triangleBase, triangleBaseColour);

    window->draw(boid);
}

// Apply the three forces to the boid
void Boid::flock(std::vector<Boid>* boidVec) {
    sf::Vector2f separatingForce = separate(boidVec);
    sf::Vector2f aligningForce = align(boidVec);
    sf::Vector2f coherenceForce = cohere(boidVec);

    // The separating force for this configuration was not enough from keeping them getting stuck inside each other. So it is multiplied by 1.1f to fix this problem.
    applyForce(separatingForce * 1.1f); 
    applyForce(aligningForce);
    applyForce(coherenceForce);
}

// Wrap boid around to other side of screen
void Boid::windowWrap() {
    if (position.x < 0) {
        position.x = screenWidth;
    }
    else if (position.x > screenWidth) {
        position.x = 0;
    }
    if (position.y < 0) {
        position.y = screenHeight;
    }
    else if (position.y > screenHeight) {
        position.y = 0;
    }
}

float Boid::angle(sf::Vector2f position) {
    return std::atan2(position.y, position.x);
}
