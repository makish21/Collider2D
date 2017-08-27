#ifndef AABB_COLLISION_H
#define AABB_COLLISION_H

#include <algorithm>

#include "Collision.hpp"

namespace cd
{
	class AABBCollision :
		public Collision
	{
	public:
		AABBCollision();
		AABBCollision(float left, float top, float width, float height);
		~AABBCollision();

		float left, top, width, height;

		virtual Projection<float> getProjection(const Vector2<float>& axis) const;

		virtual bool intersects(const Collision&) const;
		virtual bool intersects(const CompoundCollision& compound) const;
		virtual bool intersects(const CircleCollision& circle) const;
		virtual bool intersects(const ConvexCollision& convex) const;
		virtual bool intersects(const AABBCollision& other) const;
		bool intersects(const AABBCollision& other, AABBCollision& intersection) const;
		
		virtual bool contains(const Vector2<float>& point) const;
	};
}

#endif