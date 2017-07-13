#ifndef CIRCLE_SHAPE_COLLISION_H
#define CIRCLE_SHAPE_COLLISION_H

#include "Collision.hpp"
#include "CollisionDetection.hpp"

namespace cd
{
	class CircleShapeCollision :
		public Collision
	{
	public:
		explicit CircleShapeCollision();
		explicit CircleShapeCollision(const VECTOR<float>& position, float radius);

		virtual ~CircleShapeCollision();

		void setPosition(const VECTOR<float>& position);
		void setRadius(const float& radius);

		const VECTOR<float>& getPosition() const;
		const float& getRadius() const;

		// TODO 
		virtual bool intersects(const CompoundShapeCollision& compound) const;
		virtual bool intersects(const ConvexShapeCollision& convex) const;
		virtual bool intersects(const CircleShapeCollision& other) const;

		virtual bool intersects(const Collision& other) const;

		virtual bool contains(const VECTOR<float>& point) const;

	private:
		VECTOR<float> position_;
		float radius_;
	};
}
#endif // !CIRCLE_SHAPE_COLLISION