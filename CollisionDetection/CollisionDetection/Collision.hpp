#pragma once
#include <vector>

////////////////////////////////////
#include <SFML\System\Vector2.hpp>//
using namespace sf;               //
////////////////////////////////////

namespace cd
{
	enum PrimitiveType
	{
		TrianglesStrip,
		TrianglesFan,
	};

	template<typename T>
	struct Triangle
	{
		Vector2<T> vertices[3];

		bool collides(const Triangle<T>& other) const;
		bool contains(const Vector2<T>& point) const;
	};

	template <typename T>
	class Collision
	{
	public:
		explicit Collision();
		explicit Collision(const std::vector<Vector2<T>>& vertices, const PrimitiveType& type = TrianglesStrip);
		~Collision();

		const std::vector<Triangle<T>>& getTriangles() const;

	private:
		std::vector<Triangle<T>> triangles_;
	};

#include "Collision.inl"	
}
