#pragma once
#include <vector>
#include <SFML\System\Vector2.hpp>

using namespace sf;

namespace cd
{
	template<typename T>
	class Projection
	{
	public:
		explicit Projection<T>(const Vector2<T> triangle[3], const Vector2<T>& axis) :
			axis_(axis)
		{
			vertices_.insert(vertices_.begin(), triangle, triangle + 3);

			update();
		}

		explicit Projection<T>(const Vector2<T> triangle[3])
		{
			vertices_.insert(vertices_.begin(), triangle, triangle + 3);
		}

		~Projection() {}

		void setAxis(const Vector2<T>& axis)
		{
			axis_ = axis;

			update();
		}

		bool overlaps(Projection<T>& other)
		{
			return (contains(other.min_) || contains(other.max_));
		}

	private:
		std::vector<Vector2<T>> vertices_;
		Vector2<T> axis_;
		T min_;
		T max_;

		bool contains(const T& end)
		{
			return (end >= min_ && end <= max_);
		}

		void update()
		{
			min_ = dotProduct(axis_, vertices_[0]);
			max_ = min_;

			for (auto i = vertices_.begin(); i != vertices_.end(); i++)
			{
				float p = dotProduct(axis_, *i);
				p < min_ ? min_ = p : p > max_ ? max_ = p : p;
			}
		}
	};
}