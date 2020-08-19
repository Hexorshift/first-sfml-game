#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"

class Player
{
public:
	sf::RenderWindow window;
	sf::Sprite shape;
	sf::Texture texture;
	int hp;
	int hp_max;
	
	std::vector<Bullet> bullets;

	Player(sf::Texture& texture);
	~Player();

	void movements(sf::RenderWindow& window, float normal_fps);
	void move_bullets(sf::RenderWindow& window);
};