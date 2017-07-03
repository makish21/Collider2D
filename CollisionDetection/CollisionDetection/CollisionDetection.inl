

template<typename T>
bool cd::intersects(const Collision<T>& collision1, const Collision<T>& collision2)
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
bool cd::contains(const Collision<T>& collision, const VECTOR& point)
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
inline T cd::vectorLength(const VECTOR& v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

template<typename T>
inline T cd::dotProduct(const VECTOR& vec1, const VECTOR& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

template<typename T>
inline VECTOR cd::normalize(const VECTOR& v)
{
	return vectorLength(v) == 0 ? VECTOR(0, 0) : VECTOR(v / float(vectorLength(v)));
}

template<typename T>
inline VECTOR cd::projection(const VECTOR& from, const VECTOR& onto)
{
	return VECTOR((cd::dotProduct(from, onto) / (onto.x * onto.x + onto.y * onto.y) * onto.x),
		(cd::dotProduct(from, onto) / (onto.x * onto.x + onto.y * onto.y) * onto.y));
}

template<typename T>
inline VECTOR cd::normal(const VECTOR& vec)
{
	return VECTOR(vec.y, -vec.x);
}





