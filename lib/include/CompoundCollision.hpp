#ifndef COMPOUND_SHAPE_COLLISION_H
#define COMPOUND_SHAPE_COLLISION_H

#include <forward_list>

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
		CompoundCollision(Collision* collisions[], size_t collisionsCount);
		CompoundCollision(const Vector2<float> vertices[], size_t vertexCount, const PrimitiveType& type);
		CompoundCollision(Vector2<float>* vertices[], size_t vertexCount, const PrimitiveType& type);

		~CompoundCollision();

		void append(Collision* collision);
		void append(const ConvexCollision& convex);
		void append(const CircleCollision& circle);
		void append(const AABBCollision& aabb);
		void append(const Vector2<float> vertices[], size_t vertexCount, const PrimitiveType& type);
		void append(Vector2<float>* vertices[], size_t vertexCount, const PrimitiveType& type);

		void splice(CompoundCollision& other);

		void clear();

		virtual bool intersects(const Collision& other) const;
		virtual bool intersects(const CompoundCollision& other) const;
		virtual bool intersects(const ConvexCollision& convex) const;
		virtual bool intersects(const CircleCollision& circle) const;
		virtual bool intersects(const AABBCollision& aabb) const;

		virtual bool contains(const Vector2<float>& point) const;

	private:
		std::forward_list<Collision*> m_collisions;
	};

} // namespace cd

#endif // !COMPOUND_SHAPE_COLLISION_H
