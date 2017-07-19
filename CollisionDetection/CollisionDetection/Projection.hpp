#ifndef PROJECTION_HPP
#define PROJECTION_HPP

#include <vector>

#include "Collision.hpp"


namespace cd
{
	template<typename T>
	class Projection
	{
	public:
		explicit Projection<T>(const CircleShapeCollision& circle, const VECTOR<float>& axis);
		explicit Projection<T>(const VECTOR<T>& position, const T& radius, const VECTOR<T>& axis);
		explicit Projection<T>(const ConvexShapeCollision& convex, const VECTOR<float>& axis);

		~Projection();

		bool overlaps(Projection<T>& other);
		bool contains(const VECTOR<T>& point);

	private:
		VECTOR<T> axis_;
		T min_;
		T max_;

		bool contains(const T& end);
	};

#include "Projection.inl"

	// Define the most common types
	typedef Projection<float>      Projection2f;
	typedef Projection<double>	   Projection2d;
}

#endif // PROJECTION