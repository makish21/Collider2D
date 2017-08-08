#pragma once
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

		virtual bool intersects(const Collision&) const;
		virtual bool intersects(const CompoundShapeCollision& compound) const;
		virtual bool intersects(const CircleShapeCollision& circle) const;
		virtual bool intersects(const ConvexShapeCollision& convex) const;
		virtual bool intersects(const AABBCollision& other) const;
		bool intersects(const AABBCollision& other, AABBCollision& intersection) const;
		
		virtual bool contains(const VECTOR<float>& point) const;
	};
}
