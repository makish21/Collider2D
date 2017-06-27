

template<typename T>
bool cd::intersects(Collision<T> collision1, Collision<T> collision2)
{
	for (auto i = collision1.getTriangles().begin(); i != collision1.getTriangles().end(); i++)
	{
		for (auto j = collision2.getTriangles().begin(); j != collision2.getTriangles().end(); j++)
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
bool cd::contains(Collision<T> collision, const Vector2<T>& point)
{
	for (auto i = collision.getTriangles().begin(); i != collision.getTriangles().end(); i++)
	{
		if (i->contains(point))
		{
			return true;
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





