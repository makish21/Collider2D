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

	// Abstract base class for collision types that can be 
	// checked for intersection with other collisions.
	class Collision
	{
	public:
		// Virtual destructor.
		virtual ~Collision() {};

		// Check the intersection between two abstract base collisions.
		//
		// This is a pure virtual function that has to be implemented
		// by the derived class to define how the collision should be
		// checked for intersection with abstract base collision.
		//
		// parameter other - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const Collision& other) const = 0;

		// Check the intersection between abstract base 
		// collision and CompoundCollision.
		//
		// This is a pure virtual function that has to be implemented
		// by the derived class to define how the collision should be
		// checked for intersection with CompoundCollision.
		//
		// parameter compound - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const CompoundCollision& compound) const = 0;

		// Check the intersection between abstract base 
		// collision and CircleCollision.
		//
		// This is a pure virtual function that has to be implemented
		// by the derived class to define how the collision should be
		// checked for intersection with CircleCollision.
		//
		// parameter circle - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const CircleCollision& circle) const = 0;

		// Check the intersection between abstract base 
		// collision and ConvexCollision.
		//
		// This is a pure virtual function that has to be implemented
		// by the derived class to define how the collision should be
		// checked for intersection with ConvexCollision.
		//
		// parameter convex - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const ConvexCollision& convex) const = 0;

		// Check the intersection between abstract base 
		// collision and AABBCollision.
		//
		// This is a pure virtual function that has to be implemented
		// by the derived class to define how the collision should be
		// checked for intersection with AABBCollision.
		//
		// parameter aabb - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const AABBCollision& aabb) const = 0;

		// Check if a point is inside the collision's area.
		//
		// This is a pure virtual function that has to be implemented
		// by the derived class to define how the collision should be
		// checked for the point containment.
		//
		// parameter point - point to test.
		//
		// return true if the point inside, false otherwise.
		virtual bool contains(const Vector2<float>& point) const = 0;
	};
}

#endif // COLLISION_HPP

// Class cd::Collision
//
// cd::Collision is a base class for collision types that can be 
// checked for intersection with each other.
//
// Note that if you override only default base methods in your class, 
// you can not check the intersection with it from an instance of base
// or other derived classes. To do this, you need to determine method of 
// intersection with your specific collision in all required classes.
//
// Example:
//
// class MyCollision : public cd::Collision
// {
// public:
//
//	...
//
//		virtual bool intersects(const cd::Collision& other) const
//		{
//			...
//
//			// By default, this method should contain this line
//			return other.intersects(*this);
//		}
//
//		virtual bool intersects(const cd::CompoundCollision& compound) const
//		{
//			...
//		}
//
//		virtual bool intersects(const cd::ConvexCollision& convex) const
//		{
//			...
//		}
//
//		virtual bool intersects(const cd::CircleCollision& circle) const
//		{
//			...
//		}
//
//		virtual bool intersects(const cd::AABBCollision& aabb) const
//		{
//			...
//		}
//		
//		// Optional. Method that checks this collision type with itself.
//		bool intersects(const MyCollision& my) const
//		{
//			...
//		}
//
//		virtual bool contains(const cd::Vector2<float>& point) const
//		{
//			...
//		}
//
// private:
//		...
// };
