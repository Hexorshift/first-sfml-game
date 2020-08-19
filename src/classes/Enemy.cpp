#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy(sf::Texture& texture)
{
	this->shape.setTexture(texture);
	this->max_hp = rand() % 100 + 25;
	this->hp = this->max_hp;
}

Enemy::~Enemy()
{

}