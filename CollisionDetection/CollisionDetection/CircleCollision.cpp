#include "CircleCollision.h"
#include "ConvexCollision.h"
#include "CompoundCollision.h"
#include "AABBCollision.h"

namespace cd
{
	CircleCollision::CircleCollision()
	{
	}

	CircleCollision::CircleCollision(const Vector2<float>& position, float radius) :
		m_position(position),
		m_radius(radius)
	{
	}

	CircleCollision::~CircleCollision()
	{
	}

	void CircleCollision::setPosition(const Vector2<float>& position)
	{
		m_position = position;
	}

	void CircleCollision::setRadius(const float & radius)
	{
		m_radius = radius;
	}

	const Vector2<float>& CircleCollision::getPosition() const
	{
		return m_position;
	}

	const float & CircleCollision::getRadius() const
	{
		return m_radius;
	}

	Projection<float> CircleCollision::getProjection(const Vector2<float>& axis) const
	{
		float dp = axis.dotProduct(m_position);

		return Projection<float>(dp - m_radius, dp + m_radius);
	}

	bool CircleCollision::intersects(const CompoundCollision & compound) const
	{
		return compound.intersects(*this);
	}

	bool CircleCollision::intersects(const ConvexCollision & convex) const
	{
		return convex.intersects(*this);
	}

	bool CircleCollision::intersects(const CircleCollision & other) const
	{
		return Vector2<float>(m_position - other.m_position).length() < m_radius + other.m_radius;
	}

	bool CircleCollision::intersects(const AABBCollision & aabb) const
	{
		Vector2<float> aabbHalfExtents(aabb.width / 2, aabb.height / 2);
		Vector2<float> aabbCenter(aabb.left + aabbHalfExtents.x, aabb.top + aabbHalfExtents.y);

		Vector2<float> difference = m_position - aabbCenter;

		Vector2<float> clamped;
		clamped.x = std::max(-aabbHalfExtents.x, std::min(aabbHalfExtents.x, difference.x));
		clamped.y = std::max(-aabbHalfExtents.y, std::min(aabbHalfExtents.y, difference.y));

		Vector2<float> closest = aabbCenter + clamped;

		difference = closest - m_position;

		return difference.length() < m_radius;
	}

	bool CircleCollision::intersects(const Collision& other) const
	{
		return other.intersects(*this);
	}

	bool CircleCollision::contains(const Vector2<float>& point) const
	{
		return Vector2<float>(point - m_position).length() < m_radius;
	}
}