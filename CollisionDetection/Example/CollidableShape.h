#pragma once
#include <CollisionDetection.hpp>
#include <SFML\Graphics.hpp>

class CollidableShape : 
	public sf::Transformable, public sf::Drawable
{
public:
	CollidableShape(const sf::Color& color);
	virtual ~CollidableShape();

	void setDefaultColor(const sf::Color& color);
	const sf::Color& getDefaultColor() const;

	virtual void updateCollision() = 0;
	virtual void setColor(const sf::Color& color) = 0;
	virtual const cd::Collision& getCollision() const = 0;

protected:
	sf::Color color;
};