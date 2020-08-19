#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	sf::Sprite shape;
	int hp;
	int max_hp;

	Enemy(sf::Texture& texture);
	~Enemy();
};

