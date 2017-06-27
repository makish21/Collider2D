#include "Projection.hpp"


template<typename T>
inline cd::Collision<T>::Collision()
{
}

template<typename T>
inline cd::Collision<T>::Collision(const std::vector<Vector2<T>>& vertices, const PrimitiveType & type)
{
	switch (type)
	{
	case cd::TrianglesStrip:
		for (int i = 2; i < vertices.size(); i++)
		{
			Triangle<T> triangle;

			for (int j = 0, k = i - 2;
				k <= i;
				j++, k++)
			{
				triangle.vertices[j] = vertices[k];
			}

			triangles_.push_back(triangle);
		}
		break;

	case cd::TrianglesFan:
		for (int i = 2; i < vertices.size(); i++)
		{
			Triangle<T> triangle;

			for (int j = 0, k = 0;
				k <= i;
				j++, k = i - 1 + j - 1)
			{
				triangle.vertices[j] = vertices[k];
			}

			triangles_.push_back(triangle);
		}
		break;
	default:
		break;
	}
}

template<typename T>
inline cd::Collision<T>::~Collision()
{
}

template<typename T>
inline const std::vector<Triangle<T>>& cd::Collision<T>::getTriangles() const
{
	return triangles_;
}

template<typename T> 
inline bool cd::Triangle<T>::collides(const Triangle<T>& other) const
{
	Vector2<T> axis;

	Projection<T> projectionThis(vertices);
	Projection<T> projectionOther(other.vertices);

	for (int i = 0, j = 2; i < 3; i++, j = i - 1)
	{
		axis = Vector2<T>(normalize(normal(Vector2<T>(vertices[i] - vertices[j]))));

		projectionThis.setAxis(axis);
		projectionOther.setAxis(axis);

		if (!projectionThis.overlaps(projectionOther) && !projectionOther.overlaps(projectionThis))
		{
			return false;
		}

		axis = Vector2<T>(normalize(normal(Vector2<T>(other.vertices[i] - other.vertices[j]))));

		projectionThis.setAxis(axis);
		projectionOther.setAxis(axis);

		if (!projectionThis.overlaps(projectionOther) && !projectionOther.overlaps(projectionThis))
		{
			return false;
		}
	}

	return true;
}

template<typename T>
inline bool cd::Triangle<T>::contains(const Vector2<T>& point) const
{
	Vector2<T> axis;

	Projection<T> projection(vertices);

	for (int i = 0, j = 2; i < 3; i++, j = i - 1)
	{
		axis = Vector2<T>(normalize(normal(Vector2<T>(vertices[i] - vertices[j]))));

		projection.setAxis(axis);

		if (!projection.contains(point))
		{
			return false;
		}
	}
	return true;
}
