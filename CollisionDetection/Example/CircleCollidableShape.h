#pragma once
#include "CollidableShape.h"
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
	cd::CircleShapeCollision circleCollision_;
	sf::CircleShape shape_;
};

