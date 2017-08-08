#include "CompoundShapeCollision.h"
#include "ConvexShapeCollision.h"
#include "CircleShapeCollision.h"
#include "AABBCollision.h"

namespace cd
{
	CompoundShapeCollision::CompoundShapeCollision()
	{
	}

	CompoundShapeCollision::CompoundShapeCollision(const std::vector<Collision*>& collisions) :
		collisionShapes_(collisions)
	{
	}

	CompoundShapeCollision::CompoundShapeCollision(const std::vector<VECTOR<float>>& vertices, const PrimitiveType& type)
	{
		append(vertices, type);
	}

	CompoundShapeCollision::~CompoundShapeCollision()
	{
		clear();
	}

	void CompoundShapeCollision::append(Collision * collision)
	{
		if (collision)
		{
			collisionShapes_.push_back(collision);
		}
	}

	void CompoundShapeCollision::append(const ConvexShapeCollision & convex)
	{
		collisionShapes_.push_back(new ConvexShapeCollision(convex));
	}

	void CompoundShapeCollision::append(const CircleShapeCollision & circle)
	{
		collisionShapes_.push_back(new CircleShapeCollision(circle));
	}

	void CompoundShapeCollision::append(const std::vector<VECTOR<float>>& vertices, const PrimitiveType & type)
	{
		switch (type)
		{
		case Triangles:
			//i: [2], [2], [2], [5], [5], [5]...[N]
			//j: [0], [1], [2], [0], [1], [2]...[2]
			//k: [0], [1], [2], [3], [4], [5]...[N]
			for (size_t i = 2; i < vertices.size(); i+=3)
			{
				ConvexShapeCollision triangle(3);

				for (size_t j = 0, k = i - 2; 
					 k <= i; j++, k++)
				{
					triangle[j] = vertices[k];
				}

				collisionShapes_.push_back(new ConvexShapeCollision(triangle));
			}
			break;

		case TriangleStrip:
			//i: [2], [2], [2], [3], [3], [3]...[N]
			//j: [0], [1], [2], [0], [1], [2]...[2]
			//k: [0], [1], [2], [1], [2], [3]...[N]
			for (size_t i = 2; i < vertices.size(); i++)
			{
				ConvexShapeCollision triangle(3);

				for (size_t j = 0, k = i - 2;
					k <= i;
					j++, k++)
				{
					triangle[j] = vertices[k];
				}

				collisionShapes_.push_back(new ConvexShapeCollision(triangle));
			}
			break;

		case TriangleFan:
			//i: [2], [2], [2], [3], [3], [3]...[N]
			//j: [0], [1], [2], [0], [1], [2]...[2]
			//k: [0], [1], [2], [0], [2], [3]...[N]
			for (size_t i = 2; i < vertices.size(); i++)
			{
				ConvexShapeCollision triangle(3);

				for (size_t j = 0, k = 0;
					k <= i;
					j++, k = i - 1 + j - 1)
				{
					triangle[j] = vertices[k];
				}

				collisionShapes_.push_back(new ConvexShapeCollision(triangle));
			}
			break;
		default:
			break;
		}
	}

	void CompoundShapeCollision::clear()
	{
		for (auto i = collisionShapes_.begin(); i != collisionShapes_.end(); i++)
		{
			if (*i)
			{
				delete *i;
				*i = nullptr;
			}
		}

		collisionShapes_.clear();
	}

	bool CompoundShapeCollision::intersects(const CompoundShapeCollision & other) const
	{
		for (auto i = collisionShapes_.begin(); i != collisionShapes_.end(); i++)
		{
			for (auto j = other.collisionShapes_.begin(); j != other.collisionShapes_.end(); j++)
			{
				if ((*i)->intersects(**j))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool CompoundShapeCollision::intersects(const ConvexShapeCollision & convex) const
	{
		for (auto i = collisionShapes_.begin(); i != collisionShapes_.end(); i++)
		{
			if ((*i)->intersects(convex))
			{
				return true;
			}
		}
		return false;
	}

	bool CompoundShapeCollision::intersects(const CircleShapeCollision & circle) const
	{
		for (auto i = collisionShapes_.begin(); i != collisionShapes_.end(); i++)
		{
			if ((*i)->intersects(circle))
			{
				return true;
			}
		}
		return false;
	}

	bool CompoundShapeCollision::intersects(const AABBCollision & aabb) const
	{
		for (auto i = collisionShapes_.begin(); i != collisionShapes_.end(); i++)
		{
			if ((*i)->intersects(aabb))
			{
				return true;
			}
		}
		return false;
	}

	bool CompoundShapeCollision::intersects(const Collision& other) const
	{
		return other.intersects(*this);
	}

	bool CompoundShapeCollision::contains(const VECTOR<float>& point) const
	{
		for (auto i = collisionShapes_.begin(); i != collisionShapes_.end(); i++)
		{
			if ((*i)->contains(point))
			{
				return true;
			}
		}
		return false;
	}
}