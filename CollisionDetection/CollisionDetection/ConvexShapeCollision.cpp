#include "ConvexShapeCollision.h"
#include "CircleShapeCollision.h"
#include "CompoundShapeCollision.h"

#include "Projection.hpp"
#include "CollisionDetection.hpp"

namespace cd
{
	ConvexShapeCollision::ConvexShapeCollision()
	{
	}

	ConvexShapeCollision::ConvexShapeCollision(const std::vector<VECTOR<float>>& vertices) :
		vertices_(vertices)
	{
	}

	ConvexShapeCollision::~ConvexShapeCollision()
	{
	}

	void ConvexShapeCollision::resize(const std::size_t & newSize)
	{
		vertices_.resize(newSize);
	}

	std::size_t ConvexShapeCollision::getVertexCount() const
	{
		return vertices_.size();
	}

	void ConvexShapeCollision::append(const VECTOR<float> & vertex)
	{
		vertices_.push_back(vertex);
	}

	void ConvexShapeCollision::clear()
	{
		vertices_.clear();
	}

	bool ConvexShapeCollision::intersects(const CompoundShapeCollision & compound) const
	{
		return compound.intersects(*this);
	}

	bool ConvexShapeCollision::intersects(const ConvexShapeCollision & other) const
	{
		VECTOR<float> axis;
	
		for (size_t i = 0, j = vertices_.size() - 1; i < vertices_.size(); i++, j = i - 1)
		{
			axis = normalize(normal(VECTOR<float>(vertices_[i] - vertices_[j])));

			cd::Projection<float> projectionThis(vertices_, axis);
			cd::Projection<float> projectionOther(other.vertices_, axis);
	
			if (!projectionThis.overlaps(projectionOther) && !projectionOther.overlaps(projectionThis))
			{
				return false;
			}
	
			axis = normalize(normal(VECTOR<float>(other.vertices_[i] - other.vertices_[j])));
	
			projectionThis = cd::Projection<float>(vertices_, axis);
			projectionOther = cd::Projection<float>(other.vertices_, axis);
	
			if (!projectionThis.overlaps(projectionOther) && !projectionOther.overlaps(projectionThis))
			{
				return false;
			}
		}
	
		return true;
	}

	bool ConvexShapeCollision::intersects(const CircleShapeCollision & circle) const
	{
		VECTOR<float> axis;
		float nearestPointDistance = vectorLength(circle.getPosition() - vertices_[0]);

		for (size_t i = 0, j = vertices_.size() - 1; i < vertices_.size(); i++, j = i - 1)
		{
			float distance = vectorLength(circle.getPosition() - vertices_[i]);
			if (distance < nearestPointDistance)
			{
				nearestPointDistance = distance;
			}
			axis = normalize(normal(VECTOR<float>(vertices_[i] - vertices_[j])));

			cd::Projection<float> projectionConvex(vertices_, axis);
			cd::Projection<float> projectionCircle(circle.getPosition(), circle.getRadius(), axis);

			if (!projectionConvex.overlaps(projectionCircle) && !projectionCircle.overlaps(projectionConvex))
			{
				return false;
			}
		}

		return nearestPointDistance < circle.getRadius();
	}

	bool ConvexShapeCollision::intersects(const Collision& other) const
	{
		return other.intersects(*this);
	}

	bool ConvexShapeCollision::contains(const VECTOR<float>& point) const
	{
		VECTOR<float> axis;

		for (size_t i = 0, j = vertices_.size() - 1; i < vertices_.size(); i++, j = i - 1)
		{
			axis = normalize(normal(VECTOR<float>(vertices_[i] - vertices_[j])));

			Projection<float> projection(vertices_, axis);

			if (!projection.contains(point))
			{
				return false;
			}
		}
		return true;
	}
	VECTOR<float>& ConvexShapeCollision::operator[](const std::size_t& index)
	{
		return vertices_[index];
	}

	const VECTOR<float>& ConvexShapeCollision::operator[](const std::size_t& index) const
	{
		return vertices_[index];
	}
}