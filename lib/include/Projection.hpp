#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include <vector>
#include <algorithm>

#include "Collision.hpp"

namespace cd
{
	template<typename T>
	class Projection
	{
	public:
		Projection<T>();
		Projection<T>(T min, T max);
		template<typename U>
		explicit Projection<T>(const Projection<U>& projection);

		~Projection();

		bool overlaps(const Projection<T>& other) const;
		bool contains(T dot) const;

		T min;
		T max;
	};

#include "Projection.inl"
}

#endif // PROJECTION