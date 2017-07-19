#pragma once
#include "CollidableShape.h"

#include <CompoundShapeCollision.h>

class CompoundCollidableShape :
	public CollidableShape
{
public:
	CompoundCollidableShape(const sf::VertexArray& shape, const cd::PrimitiveType& type, const sf::Color& color);
	~CompoundCollidableShape();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	virtual void updateCollision();
	virtual void setColor(const sf::Color& color);
	virtual const cd::Collision& getCollision() const;
	//virtual bool intersects(const CollidableShape& other) const;
	//virtual bool contains(const sf::Vector2f& point) const;

private:
	cd::CompoundShapeCollision compoundCollision_;
	sf::VertexArray shape_;
	cd::PrimitiveType primitiveType_;
};

