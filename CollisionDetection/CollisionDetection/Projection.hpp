#ifndef PROJECTION
#define PROJECTION

#include <vector>

#include "Collision.hpp"

////////////////////////////////////
#include <SFML\System\Vector2.hpp>//
#define VECTOR sf::Vector2<T>     //
////////////////////////////////////

namespace cd
{
	template<typename T>
	class Projection
	{
	public:
		explicit Projection<T>(const VECTOR triangle[3], const VECTOR& axis);
		explicit Projection<T>(const VECTOR triangle[3]);
		explicit Projection<T>(const std::vector<VECTOR>& vertices, const VECTOR& axis);
		explicit Projection<T>(const std::vector<VECTOR>& vertices);
		explicit Projection<T>(const Triangle<T>& triangle, const VECTOR& axis);
		explicit Projection<T>(const Triangle<T>& triangle);

		~Projection();

		void setAxis(const VECTOR& axis);

		bool overlaps(Projection<T>& other);
		bool contains(const VECTOR& point);

	private:
		std::vector<VECTOR> vertices_;
		VECTOR axis_;
		T min_;
		T max_;

		bool contains(const T& end);

		void update();
	};

#include "Projection.inl"

	// Define the most common types
	typedef Projection<float>      Projection2f;
	typedef Projection<double>	   Projection2d;
}

#endif // PROJECTION