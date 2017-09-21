#include "RectangleCollidableShape.h"



RectangleCollidableShape::RectangleCollidableShape(const sf::Rect<float> rect,
												   const sf::Color & color,
												   sf::Font& font) :
	CollidableShape(color, font),
	shape_(sf::Vector2f(rect.width, rect.height))
{
	wireframe_.setFillColor(sf::Color::Transparent);
	wireframe_.setOutlineColor(sf::Color::Yellow);
	wireframe_.setOutlineThickness(1.f);

	shape_.setPosition(rect.left, rect.top);
	setColor(color);
	updateCollision();

	text.setFillColor(sf::Color::White);
	text.setString("AABB");
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
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

	rectCollision_.setPosition(cd::Vector2<float>(rect.left + rect.width / 2.f,
												  rect.top + rect.height / 2.f));
	rectCollision_.setSize(cd::Vector2<float>(rect.width, rect.height));

	wireframe_.setPosition(rect.left, rect.top);
	wireframe_.setSize(sf::Vector2f(rect.width, rect.height));

	text.setPosition(rect.left + rect.width / 2,
					 rect.top + rect.height / 2);
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
