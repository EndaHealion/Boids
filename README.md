# Boids (flocking simulation)
C++ implementation of boids using SFML.

Controls:
 * Left mouse: Adds a boid to the screen at the cursor location.
 * Escape: Closes the window.

What you are looking at:
 * This is a simulation developed by Craig Reynolds which simulates the flocking behaviour of birds.
 * Since every boid in a flock tends to have a similar direction, I gave each boid a colour depending on its direction to try and show the flocks more clearly. Some flocks may flash between two colours. This is because their direction is close between the cut-off point of one colour and the start of the next.
 * The boids can wrap around to the other side of the screen, however the distances used in the calculations do not take this wrapping into account. This means that flocks that partially wrap around to the other side of the screen are essentially broken up into a new flock.
