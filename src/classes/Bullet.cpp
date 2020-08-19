#include "Bullet.h"

Bullet::Bullet(sf::Texture& texture)
{
	this->shape.setTexture(texture);
}

Bullet::~Bullet()
{

}