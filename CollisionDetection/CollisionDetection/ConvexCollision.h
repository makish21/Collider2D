#ifndef CONVEX_SHAPE_COLLISION_H
#define CONVEX_SHAPE_COLLISION_H

#include <vector>

#include "Collision.hpp"

namespace cd
{
	class ConvexCollision :
		public Collision
	{
	public:
		ConvexCollision();
		ConvexCollision(size_t vertexCount);
		ConvexCollision(const Vector2<float> vertices[], size_t vertexCount);
		ConvexCollision(Vector2<float>* vertices[], size_t vertexCount);

		~ConvexCollision();

		void resize(std::size_t newSize);
		size_t getVertexCount() const;
		void append(const Vector2<float>& vertex);
		void append(Vector2<float>* vertex);
		void clear();

		virtual Projection<float> getProjection(const Vector2<float>& axis) const;

		virtual bool intersects(const Collision& other) const;
		virtual bool intersects(const CompoundCollision& compound) const;
		virtual bool intersects(const ConvexCollision& other) const;
		virtual bool intersects(const CircleCollision& circle) const;
		virtual bool intersects(const AABBCollision& aabb) const;

		virtual bool contains(const Vector2<float>& point) const;

		Vector2<float>& operator[](size_t index);
		const Vector2<float>& operator[](size_t index) const;

	private:
		std::vector<Vector2<float>*> m_vertices;
		std::vector<Vector2<float>**> m_allocatedVertices;
	};

} // namespace cd

#endif // CONVEX_SHAPE_COLLISION_H