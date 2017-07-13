#pragma once
#include <CollisionDetection.hpp>
#include <SFML\Graphics.hpp>

class CollidableShape : 
	public sf::Transformable, public sf::Drawable
{
public:
	CollidableShape(const sf::VertexArray& shape, const cd::PrimitiveType& type, const sf::Color& color);
	~CollidableShape();

	void updateCollision();

	void setColor(const sf::Color& color);
	const sf::Color& getDefaultColor() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	cd::Collision* collision;

private:
	sf::VertexArray shape_;
	sf::Color color_;
	std::vector<sf::Vector2f> collisionVertices_;
	cd::PrimitiveType primitiveType_;
};