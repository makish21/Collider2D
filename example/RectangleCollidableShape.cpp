#include "RectangleCollidableShape.hpp"



RectangleCollidableShape::RectangleCollidableShape(const sf::Rect<float> rect,
												   const sf::Color & color,
												   sf::Font& font) :
	CollidableShape(color, font),
	shape_(rect.size)
{
	wireframe_.setFillColor(sf::Color::Transparent);
	wireframe_.setOutlineColor(sf::Color::Yellow);
	wireframe_.setOutlineThickness(1.f);

	shape_.setPosition(rect.position);
	setColor(color);
	updateCollision();

	text.setFillColor(sf::Color::White);
	text.setString("AABB");
	text.setOrigin(text.getGlobalBounds().size / 2.f);
}

RectangleCollidableShape::~RectangleCollidableShape()
{
}

void RectangleCollidableShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape_, states);
	target.draw(wireframe_);
	target.draw(text);
}

void RectangleCollidableShape::updateCollision()
{
	sf::FloatRect rect = getTransform().transformRect(shape_.getGlobalBounds());
	sf::Vector2f center = rect.getCenter();

	rectCollision_.setPosition({center.x, center.y});
	rectCollision_.setSize({rect.size.x, rect.size.y});

	wireframe_.setPosition(rect.position);
	wireframe_.setSize(rect.size);

	text.setPosition(rect.getCenter());
}

void RectangleCollidableShape::showWireframe(bool wireframe)
{
	if (wireframe)
	{
		wireframe_.setOutlineColor(sf::Color::Yellow);
	}
	else
	{
		wireframe_.setOutlineColor(sf::Color::Transparent);
	}
}

void RectangleCollidableShape::setColor(const sf::Color & color)
{
	shape_.setFillColor(color);
}

const cd::Collision & RectangleCollidableShape::getCollision() const
{
	return rectCollision_;
}
