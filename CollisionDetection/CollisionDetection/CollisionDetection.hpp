#ifndef COLLISION_DETECTION
#define COLLISION_DETECTION

#include <math.h>
#include <vector>

#include <complex>
#include "Projection.hpp"
#include "Collision.hpp"

////////////////////////////////////
#include <SFML\System\Vector2.hpp>//
#define VECTOR sf::Vector2<T>     //
////////////////////////////////////

namespace cd
{
	template<typename T>
	bool intersects(const Collision<T>& collision1, const Collision<T>& collision2);

	template<typename T>
	bool contains(const Collision<T>& collision, const VECTOR& point);

	template<typename T>
	T vectorLength(const VECTOR& v);

	template<typename T>
	T dotProduct(const VECTOR& vec1, const VECTOR& vec2);

	template<typename T>
	VECTOR normalize(const VECTOR& v);
	
	template<typename T>
	VECTOR projection(const VECTOR& from, const VECTOR& onto);

	template<typename T>
	VECTOR normal(const VECTOR& vec);

	#include "CollisionDetection.inl"
}

#endif // COLLISION_DETECTION