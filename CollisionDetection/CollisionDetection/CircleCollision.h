#ifndef CIRCLE_SHAPE_COLLISION_H
#define CIRCLE_SHAPE_COLLISION_H

#include <algorithm>

#include "Collision.hpp"
#include "CollisionDetection.hpp"

namespace cd
{
	// Specialized collision representing a circle shape.
	class CircleCollision :
		public Collision
	{
	public:
		// Default constructor.
		//
		// parameter position - position of the circle's center,
		// patameter radius - radius of the circle.
		CircleCollision(const Vector2<float>& position = Vector2<float>(0.f, 0.f),
						float radius = 0.f);

		// Destructor.
		~CircleCollision();

		// Set the position of the circle's center.
		//
		// parameter position - new center position of the circle.
		void setPosition(const Vector2<float>& position);

		// Set the radius of the circle.
		//
		// parameter radius - new radius of the circle.
		void setRadius(const float& radius);

		// Get the position of the circle's center.
		//
		// return center position of the circle.
		const Vector2<float>& getPosition() const;

		// Get the radius of the circle.
		//
		// return radius of the circle.
		const float& getRadius() const;

		// Get the projection of the collision on the axis.
		//
		// parameter axis - axis for projection.
		//
		// return projection of the collision.
		Projection<float> getProjection(const Vector2<float>& axis) const;

		// Check the intersection with abstract base collision.
		//
		// parameter collision - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const Collision& collision) const;

		// Check the intersection with compound collision.
		//
		// parameter compound - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const CompoundCollision& compound) const;

		// Check the intersection with convex collision.
		//
		// parameter convex - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const ConvexCollision& convex) const;

		// Check the intersection with other circle collision.
		//
		// parameter other - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const CircleCollision& other) const;

		// Check the intersection with other AABB collision.
		//
		// parameter aabb - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const AABBCollision& aabb) const;

		// Check if a point is inside the collision's area.
		//
		// parameter point - point to test.
		//
		// return true if the point inside, false otherwise.
		virtual bool contains(const Vector2<float>& point) const;

	private:
		Vector2<float> m_position; // Position of the circle's center.
		float m_radius;            // Radius of the circle.
	};
}
#endif // !CIRCLE_SHAPE_COLLISION

// Class cd::CircleCollision
//
// It is a simple and fastest collision, representing a perfect circle.
//
// Usage example:
//
// cd::CircleCollision collision;
// collision.setPosition(cd::Vector2<float>(100.f, 100.f));
// collision.setRadius(50.f);
//
// if (collision.intersects(otherCollision))
// {
//		...
// }
//
// if (collision.contains(mousePos))
// {
//		...
// }
//