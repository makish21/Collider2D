#ifndef CIRCLE_COLLIDABLE_SHAPE_HPP
#define CIRCLE_COLLIDABLE_SHAPE_HPP

#include "CollidableShape.hpp"
class CircleCollidableShape :
	public CollidableShape
{
public:
	CircleCollidableShape(const sf::Vector2f& position,
						  const float& radius,
						  const sf::Color& color,
						  sf::Font& font);
	~CircleCollidableShape();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	virtual void updateCollision();
	virtual void showWireframe(bool wireframe);
	virtual void setColor(const sf::Color& color);
	virtual const cd::Collision& getCollision() const;

private:
	float radius_;
	cd::CircleCollision circleCollision_;
	sf::CircleShape shape_;
};

#endif // CIRCLE_COLLIDABLE_SHAPE_HPP
