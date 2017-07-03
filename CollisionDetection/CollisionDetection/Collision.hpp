#ifndef COLLISION
#define COLLISION

#include <vector>

////////////////////////////////////
#include <SFML\System\Vector2.hpp>//
#define VECTOR sf::Vector2<T>     //
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
		VECTOR vertices[3];

		bool collides(const Triangle<T>& other) const;
		bool contains(const VECTOR& point) const;
	};

	template <typename T>
	class Collision
	{
	public:
		explicit Collision();
		explicit Collision(const std::vector<VECTOR>& vertices, const PrimitiveType& type = TrianglesStrip);
		~Collision();

		const std::vector<Triangle<T>>& getTriangles() const;

	private:
		std::vector<Triangle<T>> triangles_;
	};

#include "Collision.inl"

	// Define the most common types
	typedef Collision<float>      Collision2f;
	typedef Collision<double>	  Collision2d;
}

#endif // COLLISION