#include "CompoundCollision.h"
#include "ConvexCollision.h"
#include "CircleCollision.h"
#include "AABBCollision.h"

namespace cd
{
	CompoundCollision::CompoundCollision()
	{
	}

	CompoundCollision::CompoundCollision(Collision* collisions[], size_t colliisionsCount) :
		m_collisions(collisions, collisions + colliisionsCount)
	{
	}

	cd::CompoundCollision::CompoundCollision(const Vector2<float> vertices[], size_t vertexCount, const PrimitiveType & type)
	{
		append(vertices, vertexCount, type);
	}

	CompoundCollision::CompoundCollision(Vector2<float>* vertices[], size_t vertexCount, const PrimitiveType & type)
	{
		append(vertices, vertexCount, type);
	}

	CompoundCollision::~CompoundCollision()
	{
		clear();
	}

	void CompoundCollision::append(Collision * collision)
	{
		if (collision)
		{
			m_collisions.push_front(collision);
		}
	}

	void CompoundCollision::append(const ConvexCollision & convex)
	{
		m_collisions.push_front(new ConvexCollision(convex));
	}

	void CompoundCollision::append(const CircleCollision & circle)
	{
		m_collisions.push_front(new CircleCollision(circle));
	}

	void CompoundCollision::append(const AABBCollision & aabb)
	{
		m_collisions.push_front(new AABBCollision(aabb));
	}

	void CompoundCollision::append(const Vector2<float> vertices[], size_t vertexCount, const PrimitiveType& type)
	{
		switch (type)
		{
		case Triangles:
			//i: [2], [2], [2], [5], [5], [5]...[N]
			//j: [0], [1], [2], [0], [1], [2]...[2]
			//k: [0], [1], [2], [3], [4], [5]...[N]
			for (size_t i = 2; i < vertexCount; i += 3)
			{
				Vector2<float> triangle[3];

				for (size_t j = 0, k = i - 2;
					 k <= i; j++, k++)
				{
					triangle[j] = vertices[k];
				}

				m_collisions.push_front(new ConvexCollision(&triangle[0], 3));
			}
			break;

		case TriangleStrip:
			//i: [2], [2], [2], [3], [3], [3]...[N]
			//j: [0], [1], [2], [0], [1], [2]...[2]
			//k: [0], [1], [2], [1], [2], [3]...[N]
			for (size_t i = 2; i < vertexCount; i++)
			{
				Vector2<float> triangle[3];

				for (size_t j = 0, k = i - 2;
					 k <= i;
					 j++, k++)
				{
					triangle[j] = vertices[k];
				}

				m_collisions.push_front(new ConvexCollision(&triangle[0], 3));
			}
			break;

		case TriangleFan:
			//i: [2], [2], [2], [3], [3], [3]...[N]
			//j: [0], [1], [2], [0], [1], [2]...[2]
			//k: [0], [1], [2], [0], [2], [3]...[N]
			for (size_t i = 2; i < vertexCount; i++)
			{
				Vector2<float> triangle[3];
				
				for (size_t j = 0, k = 0;
					 k <= i;
					 j++, k = i - 1 + j - 1)
				{
					triangle[j] = vertices[k];
				}

				m_collisions.push_front(new ConvexCollision(&triangle[0], 3));
			}
			break;
		default:
			break;
		}
	}

	void CompoundCollision::append(Vector2<float>* vertices[], size_t vertexCount, const PrimitiveType & type)
	{
		switch (type)
		{
		case Triangles:
			//i: [2], [2], [2], [5], [5], [5]...[N]
			//j: [0], [1], [2], [0], [1], [2]...[2]
			//k: [0], [1], [2], [3], [4], [5]...[N]
			for (size_t i = 2; i < vertexCount; i += 3)
			{
				Vector2<float>* triangle[3];

				for (size_t j = 0, k = i - 2;
					 k <= i; j++, k++)
				{
					triangle[j] = vertices[k];
				}

				m_collisions.push_front(new ConvexCollision(&triangle[0], 3));
			}
			break;

		case TriangleStrip:
			//i: [2], [2], [2], [3], [3], [3]...[N]
			//j: [0], [1], [2], [0], [1], [2]...[2]
			//k: [0], [1], [2], [1], [2], [3]...[N]
			for (size_t i = 2; i < vertexCount; i++)
			{
				Vector2<float>* triangle[3];

				for (size_t j = 0, k = i - 2;
					 k <= i;
					 j++, k++)
				{
					triangle[j] = vertices[k];
				}

				m_collisions.push_front(new ConvexCollision(&triangle[0], 3));
			}
			break;

		case TriangleFan:
			//i: [2], [2], [2], [3], [3], [3]...[N]
			//j: [0], [1], [2], [0], [1], [2]...[2]
			//k: [0], [1], [2], [0], [2], [3]...[N]
			for (size_t i = 2; i < vertexCount; i++)
			{
				Vector2<float>* triangle[3];

				for (size_t j = 0, k = 0;
					 k <= i;
					 j++, k = i - 1 + j - 1)
				{
					triangle[j] = vertices[k];
				}

				m_collisions.push_front(new ConvexCollision(&triangle[0], 3));
			}
			break;

		default:
			break;
		}
	}

	void CompoundCollision::splice(CompoundCollision & other)
	{
		m_collisions.splice_after(m_collisions.end(), other.m_collisions);
	}

	void CompoundCollision::clear()
	{
		for (auto i = m_collisions.begin(); i != m_collisions.end(); i++)
		{
			if (*i)
			{
				delete *i;
				*i = nullptr;
			}
		}

		m_collisions.clear();
	}

	bool CompoundCollision::intersects(const CompoundCollision & other) const
	{
		for (auto i = m_collisions.begin(); i != m_collisions.end(); i++)
		{
			for (auto j = other.m_collisions.begin(); j != other.m_collisions.end(); j++)
			{
				if ((*i)->intersects(**j))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool CompoundCollision::intersects(const ConvexCollision & convex) const
	{
		for (auto i = m_collisions.begin(); i != m_collisions.end(); i++)
		{
			if ((*i)->intersects(convex))
			{
				return true;
			}
		}
		return false;
	}

	bool CompoundCollision::intersects(const CircleCollision & circle) const
	{
		for (auto i = m_collisions.begin(); i != m_collisions.end(); i++)
		{
			if ((*i)->intersects(circle))
			{
				return true;
			}
		}
		return false;
	}

	bool CompoundCollision::intersects(const AABBCollision & aabb) const
	{
		for (auto i = m_collisions.begin(); i != m_collisions.end(); i++)
		{
			if ((*i)->intersects(aabb))
			{
				return true;
			}
		}
		return false;
	}

	bool CompoundCollision::intersects(const Collision& other) const
	{
		return other.intersects(*this);
	}

	bool CompoundCollision::contains(const Vector2<float>& point) const
	{
		for (auto i = m_collisions.begin(); i != m_collisions.end(); i++)
		{
			if ((*i)->contains(point))
			{
				return true;
			}
		}
		return false;
	}
}