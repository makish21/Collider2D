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
	rectCollision_.left = getTransform().transformRect(shape_.getGlobalBounds()).left;
	rectCollision_.top = getTransform().transformRect(shape_.getGlobalBounds()).top;
	rectCollision_.width = getTransform().transformRect(shape_.getGlobalBounds()).width;
	rectCollision_.height = getTransform().transformRect(shape_.getGlobalBounds()).height;

	wireframe_.setPosition(rectCollision_.left, rectCollision_.top);
	wireframe_.setSize(sf::Vector2f(rectCollision_.width, rectCollision_.height));

	text.setPosition(rectCollision_.left + rectCollision_.width / 2,
					 rectCollision_.top + rectCollision_.height / 2);
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
