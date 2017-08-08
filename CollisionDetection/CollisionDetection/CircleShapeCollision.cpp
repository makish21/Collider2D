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
		/*float minX = std::min(aabb.left, aabb.left + aabb.width);
		float maxX = std::max(aabb.left, aabb.left + aabb.width);
		float minY = std::min(aabb.top, aabb.top + aabb.height);
		float maxY = std::max(aabb.top, aabb.top + aabb.height);

		VECTOR<float> point = position_;

		point.x = std::max(point.x, maxX);
		point.x = std::min(point.x, minX);
		point.y = std::max(point.y, maxY);
		point.y = std::min(point.y, minY);*/

		// TODO check this:

		// Calculate AABB info (center, half-extents)
		VECTOR<float> aabb_half_extents(aabb.width / 2, aabb.height / 2);
		VECTOR<float> aabb_center(aabb.left + aabb_half_extents.x, aabb.top + aabb_half_extents.y);
		// Get difference vector between both centers
		VECTOR<float> difference = position_ - aabb_center;

		VECTOR<float> clamped;
		clamped.x = std::max(-aabb_half_extents.x, std::min(aabb_half_extents.x, difference.x));
		clamped.y = std::max(-aabb_half_extents.y, std::min(aabb_half_extents.y, difference.y));
		// Add clamped value to AABB_center and we get the value of box closest to circle
		VECTOR<float> closest = aabb_center + clamped;
		// Retrieve vector between center circle and closest point AABB and check if length <= radius
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