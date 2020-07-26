#include "Colours.h"

// takes in an angle and return an associated colour
sf::Color Colours::chooseColour(float angle) {
	const float twoPie = 2 * 3.141592635f;
	if (angle >= -twoPie && angle <= twoPie) {
		float normalisedAngle = (angle + 3.141592635f) / twoPie;
		return colourArray[(int)(normalisedAngle * (colourArray.size() - 1))];
	}
	else return sf::Color::White;
}

