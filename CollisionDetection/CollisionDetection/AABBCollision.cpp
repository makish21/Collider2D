#include "CircleCollision.h"
#include "ConvexCollision.h"
#include "CompoundCollision.h"
#include "AABBCollision.h"

namespace cd
{
	AABBCollision::AABBCollision(float left, float top, float width, float height) : 
		m_position(left + width / 2.f, top + height / 2.f),
		m_size(width, height)
	{
	}


	AABBCollision::AABBCollision(const Vector2<float>& position, const Vector2<float>& size) :
		m_position(position),
		m_size(size)
	{
	}

	AABBCollision::~AABBCollision()
	{
	}

	void AABBCollision::setPosition(const Vector2<float>& position)
	{
		m_position = position;
	}

	void AABBCollision::setSize(const Vector2<float>& size)
	{
		m_size = size;
	}

	const Vector2<float>& AABBCollision::getPosition() const
	{
		return m_position;
	}

	const Vector2<float>& AABBCollision::getSize() const
	{
		return m_size;
	}

	Vector2<float> AABBCollision::getCorner(unsigned int index) const
	{
		switch (index)
		{
		case 0:
			// Top left corner.
			return Vector2<float>(m_position - m_size / 2.f);

		case 1:
			// Top right corner.
			return Vector2<float>(m_position.x + m_size.x / 2.f,
								  m_position.y - m_size.y / 2.f);

		case 2:
			// Bottom right corner.
			return Vector2<float>(m_position + m_size / 2.f);

		case 3:
			// Bottom left corner.
			return Vector2<float>(m_position.x - m_size.x / 2.f,
								  m_position.y + m_size.y / 2.f);

		default:
			return getCorner(index % 4);
		}
	}

	Projection<float> AABBCollision::getProjection(const Vector2<float>& axis) const
	{
		float min = axis.dotProduct(getCorner(0));
		float max = min;

		for (int i = 0; i < 4; i++)
		{
			float dp = axis.dotProduct(getCorner(i));

			min = std::min(min, dp);
			max = std::max(max, dp);
		}

		return Projection<float>(min, max);
	}

	bool AABBCollision::intersects(const Collision & collision) const
	{
		return collision.intersects(*this);
	}
	bool AABBCollision::intersects(const CompoundCollision & compound) const
	{
		return compound.intersects(*this);
	}

	bool AABBCollision::intersects(const CircleCollision & circle) const
	{
		return circle.intersects(*this);
	}

	bool AABBCollision::intersects(const ConvexCollision & convex) const
	{
		return convex.intersects(*this);
	}

	bool AABBCollision::intersects(const AABBCollision & other) const
	{
		AABBCollision intersection;
		return intersects(other, intersection);
	}
	
	bool AABBCollision::intersects(const AABBCollision & other, 
								   AABBCollision & intersection) const
	{
		float thisMinX = std::min(m_position.x - m_size.x / 2.f,
								  m_position.x + m_size.x / 2.f);
		float thisMaxX = std::max(m_position.x - m_size.x / 2.f,
								  m_position.x + m_size.x / 2.f);
		float thisMinY = std::min(m_position.y - m_size.y / 2.f,
								  m_position.y + m_size.y / 2.f);
		float thisMaxY = std::max(m_position.y - m_size.y / 2.f,
								  m_position.y + m_size.y / 2.f);

		float otherMinX = std::min(other.m_position.x - m_size.x / 2.f,
								   other.m_position.x + m_size.x / 2.f);
		float otherMaxX = std::max(other.m_position.x - m_size.x / 2.f,
								   other.m_position.x + m_size.x / 2.f);
		float otherMinY = std::min(other.m_position.y - m_size.y / 2.f,
								   other.m_position.y + m_size.y / 2.f);
		float otherMaxY = std::max(other.m_position.y - m_size.y / 2.f,
								   other.m_position.y + m_size.y / 2.f);
		
		float intersectionLeft = std::max(thisMinX, otherMinX);
		float intersectionTop = std::max(thisMinY, otherMinY);
		float intersectionRight = std::min(thisMaxX, otherMaxX);
		float intersectionBottom = std::min(thisMaxY, otherMaxY);

		if ((intersectionLeft < intersectionRight) && (intersectionTop < intersectionBottom))
		{
			intersection = AABBCollision(intersectionLeft, 
										 intersectionTop, 
										 intersectionRight - intersectionLeft, 
										 intersectionBottom - intersectionTop);
			return true;
		}
		else
		{
			intersection = AABBCollision(0, 0, 0, 0);
			return false;
		}
	}

	bool AABBCollision::contains(const Vector2<float>& point) const
	{
		float minX = std::min(m_position.x - m_size.x / 2.f,
							  m_position.x + m_size.x / 2.f);
		float maxX = std::max(m_position.x - m_size.x / 2.f,
							  m_position.x + m_size.x / 2.f);
		float minY = std::min(m_position.y - m_size.y / 2.f,
							  m_position.y + m_size.y / 2.f);
		float maxY = std::max(m_position.y - m_size.y / 2.f,
							  m_position.y + m_size.y / 2.f);

		return (point.x >= minX) && (point.x < maxX) && (point.y >= minY) && (point.y < maxY);
	}
}