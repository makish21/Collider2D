#include "Projection.hpp"



template<typename T>
inline cd::Projection<T>::Projection(const VECTOR<T>& position, const T & radius, const VECTOR<T>& axis) :
	axis_(axis)
{
	T p = dotProduct(axis, position);
	min_ = p - radius;
	max_ = p + radius;
}

template<typename T>
inline cd::Projection<T>::Projection(const std::vector<VECTOR<T>>& vertices, const VECTOR<T>& axis) :
	axis_(axis)
{
	min_ = dotProduct(axis, vertices[0]);
	max_ = min_;

	for (auto i = vertices.begin(); i != vertices.end(); i++)
	{
		float p = dotProduct(axis, *i);
		p < min_ ? min_ = p : p > max_ ? max_ = p : p;
	}
}

template<typename T>
inline cd::Projection<T>::~Projection()
{
}

template<typename T>
inline bool cd::Projection<T>::overlaps(Projection<T>& other)
{
	return (contains(other.min_) || contains(other.max_));
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