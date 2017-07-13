#ifndef COLLISION_HPP
#define COLLISION_HPP

////////////////////////////////////
#include <SFML\System\Vector2.hpp>//
#define VECTOR sf::Vector2        //
////////////////////////////////////

namespace cd
{
	class CompoundShapeCollision;
	class ConvexShapeCollision;
	class CircleShapeCollision;

	class Collision
	{
	public:
		virtual ~Collision() {};

		virtual bool intersects(const Collision&) const = 0;
		virtual bool intersects(const CompoundShapeCollision&) const = 0;
		virtual bool intersects(const CircleShapeCollision&) const = 0;
		virtual bool intersects(const ConvexShapeCollision&) const = 0;

		virtual bool contains(const VECTOR<float>& point) const = 0;
	};
}

#endif // COLLISION