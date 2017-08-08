#include "Projection.hpp"

template<typename T>
inline cd::Projection<T>::Projection(const CircleShapeCollision & circle, const VECTOR<float>& axis) :
	axis_(axis)
{
	float p = dotProduct(axis, circle.getPosition());
	min_ = p - circle.getRadius();
	max_ = p + circle.getRadius();
}

//template<typename T>
//inline cd::Projection<T>::Projection(const VECTOR<T>& position, const T & radius, const VECTOR<T>& axis) :
//	axis_(axis)
//{
//	T p = dotProduct(axis, position);
//	min_ = p - radius;
//	max_ = p + radius;
//}

template<typename T>
inline cd::Projection<T>::Projection(const ConvexShapeCollision & convex, const VECTOR<float>& axis) :
	axis_(axis)
{
	min_ = dotProduct(axis, convex[0]);
	max_ = min_;

	for (size_t i = 0; i < convex.getVertexCount(); i++)
	{
		float p = dotProduct(axis, convex[i]);

		min_ = std::min(min_, p);
		max_ = std::max(max_, p);
		//p < min_ ? min_ = p : p > max_ ? max_ = p : p;
	}
}

template<typename T>
inline cd::Projection<T>::Projection(const AABBCollision & aabb, const VECTOR<float>& axis)
{
	VECTOR<float> rectVertices[4];

	rectVertices[0] = VECTOR<float>(aabb.left, aabb.top);
	rectVertices[1] = VECTOR<float>(aabb.left + aabb.width, aabb.top);
	rectVertices[2] = VECTOR<float>(aabb.left + aabb.width, aabb.top + aabb.height);
	rectVertices[3] = VECTOR<float>(aabb.left, aabb.top + aabb.height);

	min_ = dotProduct(axis, rectVertices[0]);
	max_ = min_;

	for (int i = 0; i < 4; i++)
	{
		float p = dotProduct(axis, rectVertices[i]);

		min_ = std::min(min_, p);
		max_ = std::max(max_, p);
	}
}

template<typename T>
inline cd::Projection<T>::~Projection()
{
}

template<typename T>
inline bool cd::Projection<T>::overlaps(Projection<T>& other)
{
	return (contains(other.min_) || contains(other.max_)) ||
		(other.contains(this->min_) || other.contains(this->max_));
}

template<typename T>
inline bool cd::Projection<T>::contains(const VECTOR<T>& point)
{
	T dp = dotProduct(axis_, point);
	return contains(dp);
}

template<typename T>
inline bool cd::Projection<T>::contains(const T & end)
{
	return (end >= min_ && end <= max_);
}