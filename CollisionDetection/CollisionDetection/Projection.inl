#include "Projection.hpp"

template<typename T>
inline cd::Projection<T>::Projection() :
	min(0),
	max(0)
{
}

template<typename T>
inline cd::Projection<T>::Projection(T Min, T Max) :
	min(std::min(Min, Max)),
	max(std::max(Min, Max))
{
}

template<typename T>
template<typename U>
inline cd::Projection<T>::Projection(const Projection<U>& projection) :
	min(static_cast<T>(projection.min)),
	max(static_cast<T>(projection.max))
{
}

template<typename T>
inline cd::Projection<T>::~Projection()
{
}

template<typename T>
inline bool cd::Projection<T>::overlaps(const Projection<T>& other) const
{
	return (contains(other.min) || contains(other.max)) ||
		(other.contains(this->min) || other.contains(this->max));
}

template<typename T>
inline bool cd::Projection<T>::contains(T dot) const
{
	return dot >= min && dot <= max;
}