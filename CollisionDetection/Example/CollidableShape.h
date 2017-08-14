#pragma once
#include <CollisionDetection.hpp>
#include <SFML\Graphics.hpp>

class CollidableShape : 
	public sf::Transformable, public sf::Drawable
{
public:
	CollidableShape(const sf::Color& color, sf::Font& font);
	virtual ~CollidableShape();

	void resetColor();

	virtual void updateCollision() = 0;
	virtual void showWireframe(bool wireframe) = 0;
	virtual void setColor(const sf::Color& color) = 0;
	virtual const cd::Collision& getCollision() const = 0;

protected:
	sf::Color color;
	sf::Text text;
};