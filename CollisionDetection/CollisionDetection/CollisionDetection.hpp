#ifndef COLLISION_DETECTION_HPP
#define COLLISION_DETECTION_HPP

#include <vector>
#include <complex>

#include "CircleShapeCollision.h"
#include "ConvexShapeCollision.h"
#include "CompoundShapeCollision.h"

////////////////////////////////////
#include <SFML\System\Vector2.hpp>//
#define VECTOR sf::Vector2        //
////////////////////////////////////

namespace cd
{
	template<typename T>
	T vectorLength(const VECTOR<T>& v);

	template<typename T>
	T dotProduct(const VECTOR<T>& vec1, const VECTOR<T>& vec2);

	template<typename T>
	VECTOR<T> normalize(const VECTOR<T>& v);
	
	template<typename T>
	VECTOR<T> projection(const VECTOR<T>& from, const VECTOR<T>& onto);

	template<typename T>
	VECTOR<T> normal(const VECTOR<T>& vec);

	#include "CollisionDetection.inl"
}

#endif // COLLISION_DETECTION_HPP