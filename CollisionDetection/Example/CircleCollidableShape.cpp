#include "CircleCollidableShape.h"


CircleCollidableShape::CircleCollidableShape(const sf::Vector2f & position, const float & radius, const sf::Color & color) :
	circleCollision_(position, radius),
	radius_(radius),
	shape_(radius, 30),
	CollidableShape(color)
{
	shape_.setOrigin(radius, radius);
	shape_.setPosition(position);
	setColor(color);
}

CircleCollidableShape::~CircleCollidableShape()
{
}

void CircleCollidableShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape_, states);
}

void CircleCollidableShape::updateCollision()
{
	circleCollision_.setPosition(getTransform().transformPoint(shape_.getPosition()));
}

void CircleCollidableShape::showWireframe(bool wireframe)
{
	if (wireframe)
	{
		shape_.setOutlineThickness(1.f);
		shape_.setOutlineColor(sf::Color::Yellow);
	}
	else
	{
		shape_.setOutlineThickness(0.f);
	}
}

void CircleCollidableShape::setColor(const sf::Color & color)
{
	shape_.setFillColor(color);
}

const cd::Collision & CircleCollidableShape::getCollision() const
{
	return circleCollision_;
}
