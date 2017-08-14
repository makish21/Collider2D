#include "ConvexShapeCollision.h"
#include "CircleShapeCollision.h"
#include "CompoundShapeCollision.h"
#include "AABBCollision.h"

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

	Projection<float> ConvexShapeCollision::getProjection(const VECTOR<float>& axis) const
	{
		float min = dotProduct(axis, vertices_[0]);
		float max = min;

		for (size_t i = 0; i < vertices_.size(); i++)
		{
			float dp = dotProduct(axis, vertices_[i]);

			min = std::min(min, dp);
			max = std::max(max, dp);
		}

		return Projection<float>(min, max);
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
	
			if (!getProjection(axis).overlaps(other.getProjection(axis)))
			{
				return false;
			}
	
			axis = normalize(normal(VECTOR<float>(other.vertices_[i] - other.vertices_[j])));
	
			if (!getProjection(axis).overlaps(other.getProjection(axis)))
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

			if (!getProjection(axis).overlaps(circle.getProjection(axis)))
			{
				return false;
			}
		}

		axis = normalize(VECTOR<float>(nearestPoint - circle.getPosition()));
		
		return getProjection(axis).overlaps(circle.getProjection(axis));
	}

	bool ConvexShapeCollision::intersects(const AABBCollision & aabb) const
	{
		VECTOR<float> axis;

		// i: [0], [1], [2], [3]...[n];
		// j: [n], [0], [1], [2]...[n-1];
		for (size_t i = 0, j = vertices_.size() - 1; i < vertices_.size(); i++, j = i - 1)
		{
			axis = normalize(normal(VECTOR<float>(vertices_[i] - vertices_[j])));

			if (!getProjection(axis).overlaps(aabb.getProjection(axis)))
			{
				return false;
			}
		}

		axis = VECTOR<float>(1.f, 0.f);

		if (!getProjection(axis).overlaps(aabb.getProjection(axis)))
		{
			return false;
		}

		axis = VECTOR<float>(0.f, 1.f);

		return getProjection(axis).overlaps(aabb.getProjection(axis));
	}

	bool ConvexShapeCollision::intersects(const Collision& other) const
	{
		return other.intersects(*this);
	}

	bool ConvexShapeCollision::contains(const VECTOR<float>& point) const
	{
		// i: [0], [1], [2], [3]...[n];
		// j: [n], [0], [1], [2]...[n-1];
		for (size_t i = 0, j = vertices_.size() - 1; i < vertices_.size(); i++, j = i - 1)
		{
			VECTOR<float> axis = normalize(normal(VECTOR<float>(vertices_[i] - vertices_[j])));

			float dp = dotProduct(axis, point);

			if (!getProjection(axis).contains(dp))
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