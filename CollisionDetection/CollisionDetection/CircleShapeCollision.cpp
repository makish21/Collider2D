#include "CollisionDetection.hpp"

#include "CircleShapeCollision.h"
#include "ConvexShapeCollision.h"
#include "CompoundShapeCollision.h"
#include "AABBCollision.h"

namespace cd
{
	CircleShapeCollision::CircleShapeCollision()
	{
	}

	CircleShapeCollision::CircleShapeCollision(const VECTOR<float>& position, float radius) :
		position_(position),
		radius_(radius)
	{
	}

	CircleShapeCollision::~CircleShapeCollision()
	{
	}

	void CircleShapeCollision::setPosition(const VECTOR<float>& position)
	{
		position_ = position;
	}

	void CircleShapeCollision::setRadius(const float & radius)
	{
		radius_ = radius;
	}

	const VECTOR<float>& CircleShapeCollision::getPosition() const
	{
		return position_;
	}

	const float & CircleShapeCollision::getRadius() const
	{
		return radius_;
	}

	Projection<float> CircleShapeCollision::getProjection(const VECTOR<float>& axis) const
	{
		float dp = dotProduct(axis, position_);

		return Projection<float>(dp - radius_, dp + radius_);
	}

	bool CircleShapeCollision::intersects(const CompoundShapeCollision & compound) const
	{
		return compound.intersects(*this);
	}

	bool CircleShapeCollision::intersects(const ConvexShapeCollision & convex) const
	{
		return convex.intersects(*this);
	}

	bool CircleShapeCollision::intersects(const CircleShapeCollision & other) const
	{
		return vectorLength(position_ - other.position_) < radius_ + other.radius_;
	}

	bool CircleShapeCollision::intersects(const AABBCollision & aabb) const
	{
		VECTOR<float> aabbHalfExtents(aabb.width / 2, aabb.height / 2);
		VECTOR<float> aabbCenter(aabb.left + aabbHalfExtents.x, aabb.top + aabbHalfExtents.y);

		VECTOR<float> difference = position_ - aabbCenter;

		VECTOR<float> clamped;
		clamped.x = std::max(-aabbHalfExtents.x, std::min(aabbHalfExtents.x, difference.x));
		clamped.y = std::max(-aabbHalfExtents.y, std::min(aabbHalfExtents.y, difference.y));

		VECTOR<float> closest = aabbCenter + clamped;

		difference = closest - position_;

		return vectorLength(difference) < radius_;
	}

	bool CircleShapeCollision::intersects(const Collision& other) const
	{
		return other.intersects(*this);
	}

	bool CircleShapeCollision::contains(const VECTOR<float>& point) const
	{
		return vectorLength(point - position_) < radius_;
	}
}