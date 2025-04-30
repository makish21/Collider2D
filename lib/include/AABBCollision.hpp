#ifndef AABB_COLLISION_H
#define AABB_COLLISION_H

#include <algorithm>

#include "Collision.hpp"

namespace cd
{
	// Specialized collision representing an axis-aligned rectangle.
	class AABBCollision :
		public Collision
	{
	public:
		// Default constructor.
		//
		// parameter left   - left coordinate of the collision,
		// parameter top    - top coordinate of the collision,
		// parameter width  - width of the collision,
		// parameter height - height of the collision.
		AABBCollision(float left = 0.f,
					  float top = 0.f,
					  float width = 0.f,
					  float height = 0.f);

		// Construct the rectangle from its center position and size.
		//
		// parameter position - center position of the rectangle,
		// parameter size     - size of the rectangle.
		AABBCollision(const Vector2<float>& position,
					  const Vector2<float>& size);

		// Destructor.
		~AABBCollision();

		// Set the position of the rectangle's center.
		//
		// parameter position - new center position of the rectangle.
		void setPosition(const Vector2<float>& position);

		// Set the size of the rectangle.
		//
		// parameter size - new size of the rectangle.
		void setSize(const Vector2<float>& size);

		// Get the position of the rectangle's center.
		//
		// return center position of the rectangle.
		const Vector2<float>& getPosition() const;

		// Get the size of the rectangle.
		//
		// return size of the rectangle.
		const Vector2<float>& getSize() const;

		// Get the corner's position of the rectangle.
		//
		// Returns corner's position by the index [0...3], 
		// where 0 is the top left corner and then clockwise.
		// If index is out of range, function returns corner
		// by [index % 4].
		//
		// parameter index - index of the corner to get.
		//
		// return index-th point of the rectangle.
		Vector2<float> getCorner(unsigned int index) const;

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

		// Check the intersection with circle collision.
		//
		// parameter circle - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const CircleCollision& circle) const;

		// Check the intersection with convex collision.
		//
		// parameter convex - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const ConvexCollision& convex) const;

		// Check the intersection with other AABB collision.
		//
		// parameter other - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const AABBCollision& other) const;

		// Check the intersection with other AABB collision.
		//
		// This overload returns overlapped rectangle in the
		// intersection parameter.
		//
		// parameter other		  - collision to test
		// parameter intersection - overlapped rectangle.
		//
		// return true if collisions overlap, false otherwise.
		bool intersects(const AABBCollision& other, AABBCollision& intersection) const;

		// Check if a point is inside the collision's area.
		//
		// parameter point - point to test.
		//
		// return true if the point inside, false otherwise.
		virtual bool contains(const Vector2<float>& point) const;

	private:
		Vector2<float> m_position; // Position of the rectangle's center.
		Vector2<float> m_size;     // Size of the rectangle.
	};
}

#endif // AABB_COLLISION_H

// Class cd::AABBCollision
//
// AABBCollision is a collision representing an axis-aligned
// rectangle. This means that this rectangle depends on X and Y
// coordinates and cannot be rotated.
// To create a rotatable rectangle, use cd::ConvexCollision.
//
// Usage example:
//
// cd::AABBCollision collision;
// collision.setPosition(cd::Vector2<float>(250, 200));
// collision.setSize(cd::Vector2<float>(100, 50));
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