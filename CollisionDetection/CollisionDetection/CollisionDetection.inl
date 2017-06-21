

template<typename T>
inline bool cd::intersects(const std::vector<Vector2<T>>& shape1, const std::vector<Vector2<T>>& shape2)
{
	std::vector<Triangle<T>> triangles1;
	std::vector<Triangle<T>> triangles2;

	for (int i = 2; i < shape1.size(); i++)
	{
		Triangle<T> triangle;

		for (int j = 0, k = i - 2;
			k <= i;
			j++, k++)
		{
			triangle.vertices[j] = shape1[k];
		}

		triangles1.push_back(triangle);
	}

	for (int i = 2; i < shape2.size(); i++)
	{
		Triangle<T> triangle;

		for (int j = 0, k = i - 2;
			k <= i;
			j++, k++)
		{
			triangle.vertices[j] = shape2[k];
		}

		triangles2.push_back(triangle);
	}

	for (auto i = triangles1.begin(); i != triangles1.end(); i++)
	{
		for (auto j = triangles2.begin(); j != triangles2.end(); j++)
		{
			if (j->collides(*i))
			{
				return true;
			}
		}
	}
	return false;
}

template<typename T>
inline double cd::vectorLength(const Vector2<T>& v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

template<typename T>
inline T cd::dotProduct(const Vector2<T>& vec1, const Vector2<T>& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

template<typename T>
inline Vector2<T> cd::normalize(const Vector2<T>& v)
{
	return vectorLength(v) == 0 ? Vector2<T>(0, 0) : Vector2<T>(v / float(vectorLength(v)));
}

template<typename T>
inline Vector2<T> cd::projection(const Vector2<T>& from, const Vector2<T>& onto)
{
	return Vector2<T>((cd::dotProduct(from, onto) / (onto.x * onto.x + onto.y * onto.y) * onto.x),
		(cd::dotProduct(from, onto) / (onto.x * onto.x + onto.y * onto.y) * onto.y));
}

template<typename T>
inline Vector2<T> cd::normal(const Vector2<T>& vec)
{
	return Vector2<T>(vec.y, -vec.x);
}

template<typename T>
inline bool cd::Triangle<T>::collides(const Triangle<T>& other)
{
	Vector2<T> axis;

	Projection<T> p1(vertices);
	Projection<T> p2(other.vertices);

	for (int i = 0, j = 2; i < 3; i++, j = i - 1)
	{
		axis = Vector2<T>(normalize(normal(Vector2<T>(vertices[i] - vertices[j]))));

		p1.setAxis(axis);
		p2.setAxis(axis);

		if (!p1.overlaps(p2) && !p2.overlaps(p1))
		{
			return false;
		}

		axis = Vector2<T>(normalize(normal(Vector2<T>(other.vertices[i] - other.vertices[j]))));

		p1.setAxis(axis);
		p2.setAxis(axis);

		if (!p1.overlaps(p2) && !p2.overlaps(p1))
		{
			return false;
		}
	}

	return true;
}


