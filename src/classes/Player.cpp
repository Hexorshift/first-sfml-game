#include "Player.h"
#include "Bullet.h"

Player::Player(sf::Texture& texture)
{
	this->hp_max = 500;
	this->hp = hp_max;
	this->shape.setTexture(texture);
}

void Player::movements(sf::RenderWindow& window, float normal_fps)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->shape.getPosition().y > 0)
	{
		this->shape.move(sf::Vector2f(0.0f, -5.0f * normal_fps));
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->shape.getPosition().y < window.getSize().y - this->shape.getLocalBounds().height)
	{
		this->shape.move(sf::Vector2f(0.0f, 5.0f * normal_fps));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->shape.getPosition().x > 0)
	{
		this->shape.move(sf::Vector2f(-5.0f * normal_fps, 0.0f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->shape.getPosition().x < window.getSize().x - this->shape.getLocalBounds().width - 5)
	{
		this->shape.move(sf::Vector2f(5.0f * normal_fps, 0.0f));
	}
}

void Player::move_bullets(sf::RenderWindow& window)
{
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		bullets[i].shape.move(sf::Vector2f(0.0f, -8.0f));
		if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x || bullets[i].shape.getPosition().y < 0 
			|| bullets[i].shape.getPosition().y > window.getSize().y)
		{
			bullets.erase(bullets.begin() + i);
		}
	}
}

Player::~Player()
{

}