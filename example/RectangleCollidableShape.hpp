#ifndef RECTANGLE_COLLIDABLE_SHAPE_HPP
#define RECTANGLE_COLLIDABLE_SHAPE_HPP

#include <AABBCollision.hpp>

#include "CollidableShape.hpp"

class RectangleCollidableShape :
	public CollidableShape
{
public:
	RectangleCollidableShape(const sf::Rect<float> rect,
							 const sf::Color& color,
							 sf::Font& font);
	~RectangleCollidableShape();

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	virtual void updateCollision();
	virtual void showWireframe(bool wireframe);
	virtual void setColor(const sf::Color& color);
	virtual const cd::Collision& getCollision() const;

private:
	sf::RectangleShape wireframe_;
	cd::AABBCollision rectCollision_;
	sf::RectangleShape shape_;
};

#endif // RECTANGLE_COLLIDABLE_SHAPE_HPP
