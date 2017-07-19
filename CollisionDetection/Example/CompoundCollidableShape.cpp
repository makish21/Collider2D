#include "CompoundCollidableShape.h"


CompoundCollidableShape::CompoundCollidableShape(const sf::VertexArray& shape, const cd::PrimitiveType & type, const sf::Color & color) :
	shape_(shape),
	CollidableShape(color),
	primitiveType_(type)
{
	setColor(color);
	updateCollision();
}

CompoundCollidableShape::~CompoundCollidableShape()
{
}

void CompoundCollidableShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape_, states);
}

void CompoundCollidableShape::updateCollision()
{
	std::vector<VECTOR<float>> vertices;

	for (size_t i = 0; i < shape_.getVertexCount(); i++)
	{
		vertices.push_back(getTransform().transformPoint(shape_[i].position));
	}

	compoundCollision_ = cd::CompoundShapeCollision(vertices, primitiveType_);
}

void CompoundCollidableShape::setColor(const sf::Color & color)
{
	for (int i = 0; i < shape_.getVertexCount(); i++)
	{
		shape_[i].color = color;
	}
}

const cd::Collision & CompoundCollidableShape::getCollision() const
{
	return compoundCollision_;
}