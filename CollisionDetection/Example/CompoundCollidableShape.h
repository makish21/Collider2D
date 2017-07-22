#pragma once
#include "CollidableShape.h"

#include <CompoundShapeCollision.h>

#include <CircleShapeCollision.h>

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

private:
	cd::CompoundShapeCollision compoundCollision_;
	sf::VertexArray shape_;
	cd::PrimitiveType primitiveType_;
};

