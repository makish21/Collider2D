#pragma once
#include "CollidableShape.h"

#include <CompoundShapeCollision.h>
#include <CircleShapeCollision.h>

class ConcaveCollidableShape :
	public CollidableShape
{
public:
	ConcaveCollidableShape(const sf::VertexArray& shape, const cd::PrimitiveType& type, const sf::Color& color);
	~ConcaveCollidableShape();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	virtual void updateCollision();
	virtual void showWireframe(bool wireframe);
	virtual void setColor(const sf::Color& color);
	virtual const cd::Collision& getCollision() const;

private:
	cd::CompoundShapeCollision compoundCollision_;
	sf::VertexArray shape_;
	sf::VertexArray wireframe_;
	bool isWireframeVisible_;
	cd::PrimitiveType primitiveType_;
};

