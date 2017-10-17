#pragma once
#include <ConvexCollision.h>
#include "CollidableShape.h"
class ConvexCollidableShape :
	public CollidableShape
{
public:
	ConvexCollidableShape(const sf::VertexArray& shape,
						   const cd::PrimitiveType& type,
						   const sf::Color& color,
						   sf::Font& font);
	~ConvexCollidableShape();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	virtual void updateCollision();
	virtual void showWireframe(bool wireframe);
	virtual void setColor(const sf::Color& color);
	virtual const cd::Collision& getCollision() const;

private:
	cd::ConvexCollision m_convexCollision;
	std::vector<cd::Vector2<float>*> m_vertices;
	sf::VertexArray m_shape;
	sf::VertexArray m_wireframe;
	bool m_isWireframeVisible;
};

