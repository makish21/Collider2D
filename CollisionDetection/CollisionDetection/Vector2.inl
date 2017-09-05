
template<typename T>
inline Vector2<T>::Vector2() :
	x(0),
	y(0)
{
}

template<typename T>
inline Vector2<T>::Vector2(T X, T Y) :
	x(X),
	y(Y)
{
}

template <typename T>
template <typename U>
inline Vector2<T>::Vector2(const Vector2<U>& vector) :
	x(static_cast<T>(vector.x)),
	y(static_cast<T>(vector.y))
{
}

template<typename T>
inline float cd::Vector2<T>::length() const
{
	return static_cast<float>(std::sqrt(std::pow<T>(x, 2) + std::pow<T>(y, 2)));
}

template<typename T>
inline T cd::Vector2<T>::dotProduct(const Vector2<T>& vector) const
{
	return x * vector.x + y * vector.y;
}

template<typename T>
inline Vector2<float> cd::Vector2<T>::normalize() const
{
	float len = length();
	return len == 0 ? Vector2<float>(0.f, 0.f) : Vector2<float>(Vector2<float>(*this) / len);
}

template<typename T>
inline Vector2<T> cd::Vector2<T>::getProjection(const Vector2<T>& onto) const
{
	return Vector2<T>(static_cast<T>(dotProduct(onto) / (std::pow<T>(onto.x, 2) + std::pow<T>(onto.y, 2)) * onto.x),
					  static_cast<T>(dotProduct(onto) / (std::pow<T>(onto.x, 2) + std::pow<T>(onto.y, 2)) * onto.y));
}

template<typename T>
inline Vector2<T> cd::Vector2<T>::normal() const
{
	return Vector2<T>(y, -x);
}

template<typename T>
inline Vector2<T> cd::operator+(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x + right.x, left.y + right.y);
}

template<typename T>
inline Vector2<T>& cd::operator+=(Vector2<T>& left, const Vector2<T>& right)
{
	left.x += right.x;
	left.y += right.y;

	return left;
}

template<typename T>
inline Vector2<T> cd::operator-(const Vector2<T>& vector)
{
	return Vector2<T>(-vector.x, -vector.y);
}

template<typename T>
inline Vector2<T> cd::operator-(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x - right.x, left.y - right.y);
}

template<typename T>
inline Vector2<T>& cd::operator-=(Vector2<T>& left, const Vector2<T>& right)
{
	left.x -= right.x;
	left.y -= right.y;

	return left;
}

template<typename T>
inline Vector2<T> cd::operator*(const Vector2<T>& left, T right)
{
	return Vector2<T>(left.x * right, left.y * right);
}

template<typename T>
inline Vector2<T> cd::operator*(T left, const Vector2<T>& right)
{
	return Vector2<T>(left.x * right, left.y * right);
}

template<typename T>
inline Vector2<T>& cd::operator*=(Vector2<T>& left, T right)
{
	left.x *= right;
	left.y *= right;

	return left;
}

template<typename T>
inline Vector2<T> cd::operator/(const Vector2<T>& left, T right)
{
	return Vector2<T>(left.x / right, left.y / right);
}

template<typename T>
inline Vector2<T>& cd::operator/=(Vector2<T>& left, T right)
{
	left.x /= right;
	left.y /= right;

	return left;
}

template<typename T>
inline bool cd::operator==(const Vector2<T>& left, const Vector2<T>& right)
{
	return (left.x == right.x) && (left.y == right.y);
}

template<typename T>
inline bool cd::operator!=(const Vector2<T>& left, const Vector2<T>& right)
{
	return (left.x != right.x) || (left.y != right.y);
}

