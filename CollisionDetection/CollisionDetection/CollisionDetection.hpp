#include <math.h>
#include <vector>
#include <SFML\System\Vector2.hpp>
#include "Projection.hpp"

using namespace sf;

namespace cd
{
	template<typename T>
	bool intersects(const std::vector<Vector2<T>>& shape1, const std::vector<Vector2<T>>& shape2);

	template<typename T>
	double vectorLength(const Vector2<T>& v);

	template<typename T>
	T dotProduct(const Vector2<T>& vec1, const Vector2<T>& vec2);

	template<typename T>
	Vector2<T> normalize(const Vector2<T>& v);
	
	template<typename T>
	Vector2<T> projection(const Vector2<T>& from, const Vector2<T>& onto);

	template<typename T>
	Vector2<T> normal(const Vector2<T>& vec);

	template<typename T>
	struct Triangle
	{
		Vector2<T> vertices[3];

		bool collides(const Triangle<T>& other);
	};

	#include "CollisionDetection.inl"
}