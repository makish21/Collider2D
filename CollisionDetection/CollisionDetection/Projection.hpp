#pragma once
#include <vector>

#include "Collision.hpp"

////////////////////////////////////
#include <SFML\System\Vector2.hpp>//
using namespace sf;               //
////////////////////////////////////

namespace cd
{
	template<typename T>
	class Projection
	{
	public:
		explicit Projection<T>(const Vector2<T> triangle[3], const Vector2<T>& axis);
		explicit Projection<T>(const Vector2<T> triangle[3]);
		explicit Projection<T>(const std::vector<Vector2<T>>& vertices, const Vector2<T>& axis);
		explicit Projection<T>(const std::vector<Vector2<T>>& vertices);
		explicit Projection<T>(Triangle<T> triangle, const Vector2<T>& axis);
		explicit Projection<T>(Triangle<T> triangle);

		~Projection();

		void setAxis(const Vector2<T>& axis);

		bool overlaps(Projection<T>& other);
		bool contains(const Vector2<T>& point);

	private:
		std::vector<Vector2<T>> vertices_;
		Vector2<T> axis_;
		T min_;
		T max_;

		bool contains(const T& end);

		void update();
	};

#include "Projection.inl"
}