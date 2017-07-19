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

	ConvexShapeCollision::ConvexShapeCollision(const size_t & vertexCount)
	{
		vertices_.resize(vertexCount);
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

	size_t ConvexShapeCollision::getVertexCount() const
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
	
		// i: [0], [1], [2], [3]...[n];
		// j: [n], [0], [1], [2]...[n-1];
		for (size_t i = 0, j = vertices_.size() - 1; i < vertices_.size(); i++, j = i - 1)
		{
			axis = normalize(normal(VECTOR<float>(vertices_[i] - vertices_[j])));

			cd::Projection<float> projectionThis(*this, axis);
			cd::Projection<float> projectionOther(other, axis);
	
			if (!projectionThis.overlaps(projectionOther))
			{
				return false;
			}
	
			axis = normalize(normal(VECTOR<float>(other.vertices_[i] - other.vertices_[j])));
	
			projectionThis = cd::Projection<float>(*this, axis);
			projectionOther = cd::Projection<float>(other, axis);
	
			if (!projectionThis.overlaps(projectionOther))
			{
				return false;
			}
		}
	
		return true;
	}

	bool ConvexShapeCollision::intersects(const CircleShapeCollision & circle) const
	{
		VECTOR<float> axis;
		VECTOR<float> nearestPoint = vertices_[0];
		float nearestPointDistance = vectorLength(circle.getPosition() - vertices_[0]);

		// i: [0], [1], [2], [3]...[n];
		// j: [n], [0], [1], [2]...[n-1];
		for (size_t i = 0, j = vertices_.size() - 1; i < vertices_.size(); i++, j = i - 1)
		{
			float distance = vectorLength(circle.getPosition() - vertices_[i]);
			if (distance < nearestPointDistance)
			{
				nearestPoint = vertices_[i];
				nearestPointDistance = distance;
			}

			axis = normalize(normal(VECTOR<float>(vertices_[i] - vertices_[j])));

			cd::Projection<float> projectionConvex(*this, axis);
			cd::Projection<float> projectionCircle(circle, axis);

			if (!projectionConvex.overlaps(projectionCircle))
			{
				return false;
			}
		}

		axis = normalize(VECTOR<float>(nearestPoint - circle.getPosition()));

		cd::Projection<float> projectionConvex(*this, axis);
		cd::Projection<float> projectionCircle(circle, axis);
		
		return projectionCircle.overlaps(projectionConvex);
	}

	bool ConvexShapeCollision::intersects(const Collision& other) const
	{
		return other.intersects(*this);
	}

	bool ConvexShapeCollision::contains(const VECTOR<float>& point) const
	{
		VECTOR<float> axis;

		// i: [0], [1], [2], [3]...[n];
		// j: [n], [0], [1], [2]...[n-1];
		for (size_t i = 0, j = vertices_.size() - 1; i < vertices_.size(); i++, j = i - 1)
		{
			axis = normalize(normal(VECTOR<float>(vertices_[i] - vertices_[j])));

			Projection<float> projection(*this, axis);

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