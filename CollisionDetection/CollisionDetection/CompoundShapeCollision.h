#ifndef COMPOUND_SHAPE_COLLISION_H
#define COMPOUND_SHAPE_COLLISION_H

#include <vector>

#include "Collision.hpp"

namespace cd
{
	enum PrimitiveType
	{
		TrianglesStrip,
		TrianglesFan,
	};

	class CompoundShapeCollision :
		public Collision
	{
	public:
		CompoundShapeCollision();
		CompoundShapeCollision(const std::vector<VECTOR<float>>& vertices, const PrimitiveType& type);

		virtual ~CompoundShapeCollision();

		virtual bool intersects(const CompoundShapeCollision& other) const;
		virtual bool intersects(const ConvexShapeCollision& convex) const;
		virtual bool intersects(const CircleShapeCollision& circle) const;

		virtual bool intersects(const Collision& other) const;

		virtual bool contains(const VECTOR<float>& point) const;

	private:
		std::vector<ConvexShapeCollision> convexShapes_;
	};

} // namespace cd

#endif // !COMPOUND_SHAPE_COLLISION_H
