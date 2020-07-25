#include "Colours.h"

// takes in an angle and return an associated colour
sf::Color Colours::chooseColour(float angle) {
	// probably a faster was of doing this...
	float normalisedAngle = (angle + 3.141592635f) / (2 * 3.141592635f);
	return colourArray[(int)(normalisedAngle * (colourArray.size()-1))];
}
