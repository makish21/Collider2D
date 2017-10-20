#include "ConvexCollision.h"
#include "CircleCollision.h"
#include "CompoundCollision.h"
#include "AABBCollision.h"

#include "Projection.hpp"

namespace cd
{
	ConvexCollision::ConvexCollision(size_t vertexCount) :
		m_vertices(vertexCount)
	{
	}

	ConvexCollision::ConvexCollision(const Vector2<float> vertices[], size_t vertexCount) :
		m_vertices(vertexCount),
		m_allocatedVertices(vertexCount)
	{
		for (size_t i = 0; i < vertexCount; i++)
		{
			m_vertices[i] = new Vector2<float>(vertices[i]);
			m_allocatedVertices[i] = &m_vertices[i];
		}
	}

	ConvexCollision::ConvexCollision(Vector2<float>* vertices[], size_t vertexCount) :
		m_vertices(vertices, vertices + vertexCount)
	{
	}

	ConvexCollision::~ConvexCollision()
	{
		clear();
	}

	void ConvexCollision::resize(std::size_t newSize)
	{
		m_vertices.resize(newSize);
	}

	size_t ConvexCollision::getVertexCount() const
	{
		return m_vertices.size();
	}

	void ConvexCollision::append(const Vector2<float> & vertex)
	{
		m_vertices.push_back(new Vector2<float>(vertex));
		m_allocatedVertices.push_back(&m_vertices.back());
	}

	void ConvexCollision::append(Vector2<float>* vertex)
	{
		if (vertex)
		{
			m_vertices.push_back(vertex);
		}
	}

	void ConvexCollision::clear()
	{
		for (auto i = m_allocatedVertices.begin(); i != m_allocatedVertices.end(); i++)
		{
			if (**i)
			{
				delete (**i);
				(**i) = nullptr;
			}
		}

		m_vertices.clear();
		m_allocatedVertices.clear();
	}

	Projection<float> ConvexCollision::getProjection(const Vector2<float>& axis) const
	{
		float min = axis.dotProduct(*m_vertices[0]);
		float max = min;

		for (size_t i = 0; i < m_vertices.size(); i++)
		{
			float dp = axis.dotProduct(*m_vertices[i]);

			min = std::min(min, dp);
			max = std::max(max, dp);
		}

		return Projection<float>(min, max);
	}

	bool ConvexCollision::intersects(const CompoundCollision & compound) const
	{
		return compound.intersects(*this);
	}

	bool ConvexCollision::intersects(const ConvexCollision & other) const
	{
		Vector2<float> axis;
	
		// i: [0], [1], [2], [3]...[n];
		// j: [n], [0], [1], [2]...[n-1];
		for (size_t i = 0, j = m_vertices.size() - 1; i < m_vertices.size(); i++, j = i - 1)
		{
			axis = Vector2<float>(*m_vertices[i] - *m_vertices[j]).normal().normalize();

			if (!getProjection(axis).overlaps(other.getProjection(axis)))
			{
				return false;
			}
		}

		for (size_t i = 0, j = other.m_vertices.size() - 1; i < other.m_vertices.size(); i++, j = i - 1)
		{
			axis = Vector2<float>(*other.m_vertices[i] - *other.m_vertices[j]).normal().normalize();
	
			if (!getProjection(axis).overlaps(other.getProjection(axis)))
			{
				return false;
			}
		}
	
		return true;
	}

	bool ConvexCollision::intersects(const CircleCollision & circle) const
	{
		Vector2<float> axis;
		Vector2<float> nearestPoint = *m_vertices[0];
		float nearestPointDistance = Vector2<float>(circle.getPosition() - *m_vertices[0]).length();

		// i: [0], [1], [2], [3]...[n];
		// j: [n], [0], [1], [2]...[n-1];
		for (size_t i = 0, j = m_vertices.size() - 1; i < m_vertices.size(); i++, j = i - 1)
		{
			float distance = Vector2<float>(circle.getPosition() - *m_vertices[i]).length();

			if (distance < nearestPointDistance)
			{
				nearestPoint = *m_vertices[i];
				nearestPointDistance = distance;
			}

			axis = Vector2<float>(*m_vertices[i] - *m_vertices[j]).normal().normalize();

			if (!getProjection(axis).overlaps(circle.getProjection(axis)))
			{
				return false;
			}
		}

		axis = Vector2<float>(nearestPoint - circle.getPosition()).normalize();
		
		return getProjection(axis).overlaps(circle.getProjection(axis));
	}

	bool ConvexCollision::intersects(const AABBCollision & aabb) const
	{
		Vector2<float> axis;

		// i: [0], [1], [2], [3]...[n];
		// j: [n], [0], [1], [2]...[n-1];
		for (size_t i = 0, j = m_vertices.size() - 1; i < m_vertices.size(); i++, j = i - 1)
		{
			axis = Vector2<float>(*m_vertices[i] - *m_vertices[j]).normal().normalize();

			if (!getProjection(axis).overlaps(aabb.getProjection(axis)))
			{
				return false;
			}
		}

		axis = Vector2<float>(1.f, 0.f);

		if (!getProjection(axis).overlaps(aabb.getProjection(axis)))
		{
			return false;
		}

		axis = Vector2<float>(0.f, 1.f);

		return getProjection(axis).overlaps(aabb.getProjection(axis));
	}

	bool ConvexCollision::intersects(const Collision& other) const
	{
		return other.intersects(*this);
	}

	bool ConvexCollision::contains(const Vector2<float>& point) const
	{
		// i: [0], [1], [2], [3]...[n];
		// j: [n], [0], [1], [2]...[n-1];
		for (size_t i = 0, j = m_vertices.size() - 1; i < m_vertices.size(); i++, j = i - 1)
		{
			Vector2<float> axis = Vector2<float>(*m_vertices[i] - *m_vertices[j]).normal().normalize();

			float dp = axis.dotProduct(point);

			if (!getProjection(axis).contains(dp))
			{
				return false;
			}
		}

		return true;
	}

	Vector2<float>& ConvexCollision::operator[](std::size_t index)
	{
		return index < getVertexCount() ? *m_vertices[index] : *m_vertices[index % getVertexCount()];
	}

	const Vector2<float>& ConvexCollision::operator[](std::size_t index) const
	{
		return index < getVertexCount() ? *m_vertices[index] : *m_vertices[index % getVertexCount()];;
	}
}