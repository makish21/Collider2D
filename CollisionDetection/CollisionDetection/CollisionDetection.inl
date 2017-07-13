
template<typename T>
inline T cd::vectorLength(const VECTOR<T>& v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

template<typename T>
inline T cd::dotProduct(const VECTOR<T>& vec1, const VECTOR<T>& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

template<typename T>
inline VECTOR<T> cd::normalize(const VECTOR<T>& v)
{
	return vectorLength(v) == 0 ? VECTOR<T>(0, 0) : VECTOR<T>(v / T(vectorLength(v)));
}

template<typename T>
inline VECTOR<T> cd::projection(const VECTOR<T>& from, const VECTOR<T>& onto)
{
	return VECTOR((cd::dotProduct(from, onto) / (onto.x * onto.x + onto.y * onto.y) * onto.x),
		(cd::dotProduct(from, onto) / (onto.x * onto.x + onto.y * onto.y) * onto.y));
}

template<typename T>
inline VECTOR<T> cd::normal(const VECTOR<T>& vec)
{
	return VECTOR<T>(vec.y, -vec.x);
}





