#ifndef VECTOR_2_HPP
#define VECTOR_2_HPP

#include <complex>

namespace cd
{
	template <typename T>
	class Vector2
	{
	public:
		Vector2();
		Vector2(T x, T y);
		template <typename U>
		explicit Vector2(const Vector2<U>& vector);

		T x;
		T y;

		float length() const;
		T dotProduct(const Vector2<T>& vector) const;
		Vector2<float> normalize() const;
		Vector2<T> getProjection(const Vector2<T>& onto) const;
		Vector2<T> normal() const;

	};

	template <typename T>
	Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right);
	
	template <typename T>
	Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T> operator-(const Vector2<T>& vector);

	template <typename T>
	Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	Vector2<T> operator*(const Vector2<T>& left, T right);

	template <typename T>
	Vector2<T> operator*(T left, const Vector2<T>& right);

	template <typename T>
	Vector2<T>& operator*=(Vector2<T>& left, T right);

	template <typename T>
	Vector2<T> operator/(const Vector2<T>& left, T right);

	template <typename T>
	Vector2<T>& operator/=(Vector2<T>& left, T right);

	template <typename T>
	bool operator==(const Vector2<T>& left, const Vector2<T>& right);

	template <typename T>
	bool operator!=(const Vector2<T>& left, const Vector2<T>& right);

#include "Vector2.inl"

} // namespace cd

#endif // !VECTOR_2_HPP