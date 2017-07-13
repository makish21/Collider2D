#include "CollidableShape.h"


CollidableShape::CollidableShape(const sf::VertexArray & shape, const cd::PrimitiveType & type, const sf::Color & color) :
	shape_(shape),
	primitiveType_(type),
	color_(color)
{
	collisionVertices_.resize(shape.getVertexCount());
	updateCollision();
	setColor(color);
}

CollidableShape::~CollidableShape()
{
	if (collision)
	{
		delete collision;
	}
}

void CollidableShape::updateCollision()
{
	for (int i = 0; i < shape_.getVertexCount(); i++)
	{
		collisionVertices_[i] = getTransform().transformPoint(shape_[i].position);
	}

	collision = new cd::CompoundShapeCollision(collisionVertices_, primitiveType_);
}

void CollidableShape::setColor(const sf::Color & color)
{
	for (int i = 0; i < shape_.getVertexCount(); i++)
	{
		shape_[i].color = color;
	}
}

const sf::Color & CollidableShape::getDefaultColor() const
{
	return color_;
}

void CollidableShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	{
		states.transform *= getTransform();
		target.draw(shape_, states);
	}
}
