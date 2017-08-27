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
		ConvexCollision(const size_t& vertexCount);
		ConvexCollision(const std::vector<Vector2<float>>& vertices);

		~ConvexCollision();

		void resize(const std::size_t& newSize);
		size_t getVertexCount() const;
		void append(const Vector2<float>& vertex);
		void clear();

		virtual Projection<float> getProjection(const Vector2<float>& axis) const;

		virtual bool intersects(const Collision& other) const;
		virtual bool intersects(const CompoundCollision& compound) const;
		virtual bool intersects(const ConvexCollision& other) const;
		virtual bool intersects(const CircleCollision& circle) const;
		virtual bool intersects(const AABBCollision& aabb) const;

		virtual bool contains(const Vector2<float>& point) const;

		Vector2<float>& operator[](const std::size_t& index);
		const Vector2<float>& operator[](const std::size_t& index) const;

	private:
		std::vector<Vector2<float>> m_vertices;
	};

} // namespace cd

#endif // CONVEX_SHAPE_COLLISION_H