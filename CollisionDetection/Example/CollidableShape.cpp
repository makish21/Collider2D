#include "CollidableShape.h"


CollidableShape::CollidableShape(const sf::Color & color) :
	color(color)
{
}

CollidableShape::~CollidableShape()
{
}

void CollidableShape::setDefaultColor(const sf::Color & color)
{
	this->color = color;
}

const sf::Color & CollidableShape::getDefaultColor() const
{
	return color;
}
