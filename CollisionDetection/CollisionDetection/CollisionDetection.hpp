#include <math.h>
#include <vector>

#include "Projection.hpp"
#include "Collision.hpp"

////////////////////////////////////
#include <SFML\System\Vector2.hpp>//
using namespace sf;               //
////////////////////////////////////

namespace cd
{

	template<typename T>
	bool intersects(Collision<T> collision1, Collision<T> collision2);

	template<typename T>
	bool contains(Collision<T> collision, const Vector2<T>& point);

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

	#include "CollisionDetection.inl"
}