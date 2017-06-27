
template<typename T>
inline cd::Projection<T>::Projection(const Vector2<T> triangle[3], const Vector2<T>& axis) :
axis_(axis)
{
	vertices_.insert(vertices_.begin(), triangle, triangle + 3);

	update();
}

template<typename T>
inline cd::Projection<T>::Projection(const Vector2<T> triangle[3])
{
	vertices_.insert(vertices_.begin(), triangle, triangle + 3);
}

template<typename T>
inline cd::Projection<T>::Projection(const std::vector<Vector2<T>>& vertices, const Vector2<T>& axis) :
	vertices_(vertices),
	axis_(axis)
{
	update();
}

template<typename T>
inline cd::Projection<T>::Projection(const std::vector<Vector2<T>>& vertices) :
	vertices_(vertices)
{
}

template<typename T>
inline cd::Projection<T>::Projection(Triangle<T> triangle, const Vector2<T>& axis) :
	axis_(axis)
{
	vertices_.insert(vertices_.begin(), triangle.vertices, triangle.vertices + 3);

	update();
}

template<typename T>
inline cd::Projection<T>::Projection(const Triangle<T> triangle)
{
	vertices_.insert(vertices_.begin(), triangle.vertices, triangle.vertices + 3);
}

template<typename T>
inline cd::Projection<T>::~Projection()
{
}

template<typename T>
inline void cd::Projection<T>::setAxis(const Vector2<T>& axis)
{
	axis_ = axis;

	update();
}

template<typename T>
inline bool cd::Projection<T>::overlaps(Projection<T>& other)
{
	return (contains(other.min_) || contains(other.max_));
}

template<typename T>
inline bool cd::Projection<T>::contains(const Vector2<T>& point)
{
	T dp = dotProduct(axis_, point);
	return contains(dp);
}

template<typename T>
inline bool cd::Projection<T>::contains(const T & end)
{
	return (end >= min_ && end <= max_);
}

template<typename T>
inline void cd::Projection<T>::update()
{
	min_ = dotProduct(axis_, vertices_[0]);
	max_ = min_;

	for (auto i = vertices_.begin(); i != vertices_.end(); i++)
	{
		float p = dotProduct(axis_, *i);
		p < min_ ? min_ = p : p > max_ ? max_ = p : p;
	}
}