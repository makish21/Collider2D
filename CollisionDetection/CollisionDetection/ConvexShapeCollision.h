#ifndef CONVEX_SHAPE_COLLISION_H
#define CONVEX_SHAPE_COLLISION_H

#include <vector>

#include "Collision.hpp"

namespace cd
{
	class ConvexShapeCollision :
		public Collision
	{
		friend CompoundShapeCollision;

	public:
		ConvexShapeCollision();
		ConvexShapeCollision(const std::vector<VECTOR<float>>& vertices);

		~ConvexShapeCollision();

		void resize(const std::size_t& newSize);
		std::size_t getVertexCount() const;
		void append(const VECTOR<float>& vertex);
		void clear();

		virtual bool intersects(const Collision& other) const;
		virtual bool intersects(const CompoundShapeCollision& compound) const;
		virtual bool intersects(const ConvexShapeCollision& other) const;
		virtual bool intersects(const CircleShapeCollision& circle) const;

		virtual bool contains(const VECTOR<float>& point) const;

		VECTOR<float>& operator[](const std::size_t& index);
		const VECTOR<float>& operator[](const std::size_t& index) const;

	private:
		std::vector<VECTOR<float>> vertices_;
	};

} // namespace cd

#endif // CONVEX_SHAPE_COLLISION_H