#include "ConcaveCollidableShape.h"


ConcaveCollidableShape::ConcaveCollidableShape(const sf::VertexArray& shape, const cd::PrimitiveType & type, const sf::Color & color) :
	shape_(shape),
	wireframe_(sf::Lines),
	isWireframeVisible_(false),
	CollidableShape(color),
	primitiveType_(type)
{
	setColor(color);
	updateCollision();
}

ConcaveCollidableShape::~ConcaveCollidableShape()
{
}

void ConcaveCollidableShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape_, states);

	if (isWireframeVisible_)
	{
		target.draw(wireframe_, states);
	}
}

void ConcaveCollidableShape::updateCollision()
{
	std::vector<VECTOR<float>> vertices;

	wireframe_.clear();

	for (size_t i = 0; i < shape_.getVertexCount(); i++)
	{
		vertices.push_back(getTransform().transformPoint(shape_[i].position));

		wireframe_.append(sf::Vertex(shape_[i].position, sf::Color::Yellow));

		if (i >= 2)
		{
			switch (primitiveType_)
			{
			case cd::TriangleStrip:
				wireframe_.append(sf::Vertex(shape_[i - 1].position, sf::Color::Yellow));
				wireframe_.append(sf::Vertex(shape_[i].position, sf::Color::Yellow));
				wireframe_.append(sf::Vertex(shape_[i - 2].position, sf::Color::Yellow));
				break;

			case cd::TriangleFan:
				wireframe_.append(sf::Vertex(shape_[0].position, sf::Color::Yellow));
				wireframe_.append(sf::Vertex(shape_[i].position, sf::Color::Yellow));
				wireframe_.append(sf::Vertex(shape_[i - 1].position, sf::Color::Yellow));
				break;

			default:
				break;
			}
		}
	}

	compoundCollision_.clear();
	compoundCollision_.append(vertices, primitiveType_);
}

void ConcaveCollidableShape::showWireframe(bool wireframe)
{
	isWireframeVisible_ = wireframe;
}

void ConcaveCollidableShape::setColor(const sf::Color & color)
{
	for (int i = 0; i < shape_.getVertexCount(); i++)
	{
		shape_[i].color = color;
	}
}

const cd::Collision & ConcaveCollidableShape::getCollision() const
{
	return compoundCollision_;
}