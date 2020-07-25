#pragma once

#include <SFML/Graphics.hpp>
#include <array>

class Colours {
public:
	const std::array<sf::Color, 8> colourArray{
		sf::Color::Red,
		sf::Color::Yellow,
		sf::Color(125, 255, 0),
		sf::Color(0, 255, 165),
		sf::Color(0, 65, 255),
		sf::Color(30, 0, 255),
		sf::Color(125, 0, 255),
		sf::Color(255, 0, 95)
	};

	sf::Color chooseColour(float angle);
};