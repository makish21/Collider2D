#include "ConcaveCollidableShape.h"


ConcaveCollidableShape::ConcaveCollidableShape(const sf::VertexArray& shape,
											   const cd::PrimitiveType & type,
											   const sf::Color & color,
											   sf::Font& font) :
	shape_(shape),
	vertices_(shape.getVertexCount()),
	wireframe_(sf::Lines),
	isWireframeVisible_(false),
	CollidableShape(color, font),
	primitiveType_(type)
{
	for (size_t i = 0; i < shape_.getVertexCount(); i++)
	{
		sf::Vector2f vertexPosition = getTransform().transformPoint(shape_[i].position);
		vertices_[i] = new cd::Vector2<float>(vertexPosition.x, vertexPosition.y);
	}

	compoundCollision_.append(&vertices_[0], vertices_.size(), type);

	setColor(color);
	updateCollision();

	sf::Glyph glyph = font.getGlyph('a', 20, false);
	text.setFillColor(sf::Color::White);

	if (shape.getVertexCount() <= 3)
	{
		text.setString("Convex");
	}
	else if (type == cd::Triangles)
	{
		text.setString("Compound");
	}
	else
	{
		text.setString("Concave");
	}

	text.setOrigin(text.getGlobalBounds().width / 2, glyph.bounds.height);

	float left = shape_[0].position.x;
	float top = shape_[0].position.y;
	float right = left;
	float down = top;

	for (size_t i = 0; i < shape_.getVertexCount(); i++)
	{
		left = std::min(left, shape[i].position.x);
		top = std::min(top, shape[i].position.y);
		right = std::max(right, shape[i].position.x);
		down = std::max(down, shape[i].position.y);
	}
	
	text.setPosition(left + (right - left) / 2.f, top + (down - top) / 2.f);
}

ConcaveCollidableShape::~ConcaveCollidableShape()
{
	for (auto i = vertices_.begin(); i != vertices_.end(); i++)
	{
		if (*i)
		{
			delete *i;
			*i = nullptr;
		}
	}
}

void ConcaveCollidableShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(shape_, states);

	if (isWireframeVisible_)
	{
		target.draw(wireframe_, states);
	}
	
	target.draw(text, states);
}

void ConcaveCollidableShape::updateCollision()
{
	wireframe_.clear();

	text.setRotation(-getRotation());

	for (size_t i = 0; i < shape_.getVertexCount(); i++)
	{
		sf::Vector2f vertexPosition = getTransform().transformPoint(shape_[i].position);
		*vertices_[i] = cd::Vector2<float>(vertexPosition.x, vertexPosition.y);

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

			case cd::Triangles:
				if ((i + 1) % 3 == 0)
				{
					wireframe_.append(sf::Vertex(shape_[i - 1].position, sf::Color::Yellow));
					wireframe_.append(sf::Vertex(shape_[i].position, sf::Color::Yellow));
					wireframe_.append(sf::Vertex(shape_[i - 2].position, sf::Color::Yellow));
				}

			default:
				break;
			}
		}
	}
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