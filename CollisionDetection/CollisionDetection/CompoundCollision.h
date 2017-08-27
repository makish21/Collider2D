#ifndef COMPOUND_SHAPE_COLLISION_H
#define COMPOUND_SHAPE_COLLISION_H

#include <vector>

#include "Collision.hpp"

namespace cd
{
	enum PrimitiveType
	{
		Triangles,
		TriangleStrip,
		TriangleFan
	};

	class CompoundCollision :
		public Collision
	{
	public:
		CompoundCollision();
		CompoundCollision(const std::vector<Collision*>& collisions);
		CompoundCollision(const std::vector<Vector2<float>>& vertices, const PrimitiveType& type);

		~CompoundCollision();

		void append(Collision* collision);
		void append(const ConvexCollision& convex);
		void append(const CircleCollision& circle);
		void append(const std::vector<Vector2<float>>& vertices, const PrimitiveType& type);
		void clear();

		virtual Projection<float> getProjection(const Vector2<float>& axis) const;

		virtual bool intersects(const Collision& other) const;
		virtual bool intersects(const CompoundCollision& other) const;
		virtual bool intersects(const ConvexCollision& convex) const;
		virtual bool intersects(const CircleCollision& circle) const;
		virtual bool intersects(const AABBCollision& aabb) const;

		virtual bool contains(const Vector2<float>& point) const;

	private:
		std::vector<Collision*> m_collisions;
	};

} // namespace cd

#endif // !COMPOUND_SHAPE_COLLISION_H
