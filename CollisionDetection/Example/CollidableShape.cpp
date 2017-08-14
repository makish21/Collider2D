#include "CollidableShape.h"


CollidableShape::CollidableShape(const sf::Color & color, sf::Font& font) :
	color(color),
	text("", font, 20)
{
}

CollidableShape::~CollidableShape()
{
}

void CollidableShape::resetColor()
{
	setColor(color);
}
