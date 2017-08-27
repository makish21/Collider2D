#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "Vector2.hpp"
#include "Projection.hpp"

namespace cd
{
	class CompoundCollision;
	class ConvexCollision;
	class CircleCollision;
	class AABBCollision;

	class Collision
	{
	public:
		virtual ~Collision() {};

		virtual Projection<float> getProjection(const Vector2<float>& axis) const = 0;

		virtual bool intersects(const Collision&) const = 0;
		virtual bool intersects(const CompoundCollision&) const = 0;
		virtual bool intersects(const CircleCollision&) const = 0;
		virtual bool intersects(const ConvexCollision&) const = 0;
		virtual bool intersects(const AABBCollision&) const = 0;

		virtual bool contains(const Vector2<float>& point) const = 0;
	};
}

#endif // COLLISION