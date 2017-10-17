#include "ConvexCollidableShape.h"


ConvexCollidableShape::ConvexCollidableShape(const sf::VertexArray & shape, 
											 const cd::PrimitiveType & type, 
											 const sf::Color & color, 
											 sf::Font & font) :
	m_shape(shape),
	m_vertices(shape.getVertexCount()),
	m_wireframe(sf::LineStrip),
	m_isWireframeVisible(false),
	CollidableShape(color, font)
{
	for (size_t i = 0; i < m_shape.getVertexCount(); i++)
	{
		sf::Vector2f vertexPosition = getTransform().transformPoint(m_shape[i].position);
		m_vertices[i] = new cd::Vector2<float>(vertexPosition.x, vertexPosition.y);
		m_convexCollision.append(m_vertices[i]);
	}

	setColor(color);
	updateCollision();

	sf::Glyph glyph = font.getGlyph('a', 20, false);
	text.setFillColor(sf::Color::White);

	text.setString("Convex");
	text.setOrigin(text.getGlobalBounds().width / 2, glyph.bounds.height);

	float left = m_shape[0].position.x;
	float top = m_shape[0].position.y;
	float right = left;
	float down = top;

	for (size_t i = 0; i < m_shape.getVertexCount(); i++)
	{
		left = std::min(left, shape[i].position.x);
		top = std::min(top, shape[i].position.y);
		right = std::max(right, shape[i].position.x);
		down = std::max(down, shape[i].position.y);
	}

	text.setPosition(left + (right - left) / 2.f, top + (down - top) / 2.f);
}

ConvexCollidableShape::~ConvexCollidableShape()
{
	for (auto i = m_vertices.begin(); i != m_vertices.end(); i++)
	{
		if (*i)
		{
			delete *i;
			*i = nullptr;
		}
	}
}

void ConvexCollidableShape::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_shape, states);

	if (m_isWireframeVisible)
	{
		target.draw(m_wireframe, states);
	}

	target.draw(text, states);
}

void ConvexCollidableShape::updateCollision()
{
	m_wireframe.clear();

	text.setRotation(-getRotation());

	for (size_t i = 0; i < m_shape.getVertexCount(); i++)
	{
		sf::Vector2f vertexPosition = getTransform().transformPoint(m_shape[i].position);
		*m_vertices[i] = cd::Vector2<float>(vertexPosition.x, vertexPosition.y);

		m_wireframe.append(sf::Vertex(m_shape[i].position, sf::Color::Yellow));
	}

	m_wireframe.append(sf::Vertex(m_shape[0].position, sf::Color::Yellow));
}

void ConvexCollidableShape::showWireframe(bool wireframe)
{
	m_isWireframeVisible = wireframe;
}

void ConvexCollidableShape::setColor(const sf::Color & color)
{
	for (int i = 0; i < m_shape.getVertexCount(); i++)
	{
		m_shape[i].color = color;
	}
}

const cd::Collision & ConvexCollidableShape::getCollision() const
{
	return m_convexCollision;
}
