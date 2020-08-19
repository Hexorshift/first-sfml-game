#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	sf::Sprite shape;

	Bullet(sf::Texture& texture);
	~Bullet();
};

