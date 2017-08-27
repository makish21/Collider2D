#ifndef CIRCLE_SHAPE_COLLISION_H
#define CIRCLE_SHAPE_COLLISION_H

#include <algorithm>

#include "Collision.hpp"
#include "CollisionDetection.hpp"

namespace cd
{
	class CircleCollision :
		public Collision
	{
	public:
		explicit CircleCollision();
		explicit CircleCollision(const Vector2<float>& position, float radius);

		virtual ~CircleCollision();

		void setPosition(const Vector2<float>& position);
		void setRadius(const float& radius);

		const Vector2<float>& getPosition() const;
		const float& getRadius() const;

		virtual Projection<float> getProjection(const Vector2<float>& axis) const;

		virtual bool intersects(const Collision& other) const;
		virtual bool intersects(const CompoundCollision& compound) const;
		virtual bool intersects(const ConvexCollision& convex) const;
		virtual bool intersects(const CircleCollision& other) const;
		virtual bool intersects(const AABBCollision& aabb) const;

		virtual bool contains(const Vector2<float>& point) const;

	private:
		Vector2<float> m_position;
		float m_radius;
	};
}
#endif // !CIRCLE_SHAPE_COLLISION