#include "CircleShapeCollision.h"
#include "ConvexShapeCollision.h"
#include "CompoundShapeCollision.h"
#include "AABBCollision.h"

namespace cd
{
	AABBCollision::AABBCollision() :
		left(0.f),
		top(0.f),
		width(0.f),
		height(0.f)
	{
	}

	AABBCollision::AABBCollision(float rectLeft, float rectTop, float rectWidth, float rectHeight) :
		left(rectLeft),
		top(rectTop),
		width(rectWidth),
		height(rectHeight)
	{
	}


	AABBCollision::~AABBCollision()
	{
	}

	bool AABBCollision::intersects(const Collision & collision) const
	{
		return collision.intersects(*this);
	}
	bool AABBCollision::intersects(const CompoundShapeCollision & compound) const
	{
		return compound.intersects(*this);
	}

	bool AABBCollision::intersects(const CircleShapeCollision & circle) const
	{
		return circle.intersects(*this);
	}

	bool AABBCollision::intersects(const ConvexShapeCollision & convex) const
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
		float thisMinX = std::min(left, left + width);
		float thisMaxX = std::max(left, left + width);
		float thisMinY = std::min(top, top + height);
		float thisMaxY = std::max(top, top + height);

		float otherMinX = std::min(other.left, other.left + other.width);
		float otherMaxX = std::max(other.left, other.left + other.width);
		float otherMinY = std::min(other.top, other.top + other.height);
		float otherMaxY = std::max(other.top, other.top + other.height);
		
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

	bool AABBCollision::contains(const VECTOR<float>& point) const
	{
		float minX = std::min(left, left + width);
		float maxX = std::max(left, left + width);
		float minY = std::min(top, top + height);
		float maxY = std::max(top, top + height);

		return (point.x >= minX) && (point.x < maxX) && (point.y >= minY) && (point.y < maxY);
	}
}