#include "CompoundShapeCollision.h"
#include "ConvexShapeCollision.h"
#include "CircleShapeCollision.h"

namespace cd
{
	CompoundShapeCollision::CompoundShapeCollision()
	{
	}

	CompoundShapeCollision::CompoundShapeCollision(const std::vector<Collision*>& collisions) :
		convexShapes_(collisions)
	{
	}

	CompoundShapeCollision::CompoundShapeCollision(const std::vector<VECTOR<float>>& vertices, const PrimitiveType& type)
	{
		append(vertices, type);
	}

	CompoundShapeCollision::~CompoundShapeCollision()
	{
		//clear();
	}

	void CompoundShapeCollision::append(Collision * collision)
	{
		if (collision)
		{
			convexShapes_.push_back(collision);
		}
	}

	void CompoundShapeCollision::append(const ConvexShapeCollision & convex)
	{
		convexShapes_.push_back(new ConvexShapeCollision(convex));
	}

	void CompoundShapeCollision::append(const CircleShapeCollision & circle)
	{
		convexShapes_.push_back(new CircleShapeCollision(circle));
	}

	void CompoundShapeCollision::append(const std::vector<VECTOR<float>>& vertices, const PrimitiveType & type)
	{
		switch (type)
		{
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

				convexShapes_.push_back(new ConvexShapeCollision(triangle));
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

				convexShapes_.push_back(new ConvexShapeCollision(triangle));
			}
			break;
		default:
			break;
		}
	}

	void CompoundShapeCollision::clear()
	{
		for (auto i = convexShapes_.begin(); i != convexShapes_.end(); i++)
		{
			delete *i;
		}

		convexShapes_.clear();
	}

	bool CompoundShapeCollision::intersects(const CompoundShapeCollision & other) const
	{
		for (auto i = convexShapes_.begin(); i != convexShapes_.end(); i++)
		{
			for (auto j = other.convexShapes_.begin(); j != other.convexShapes_.end(); j++)
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
		for (auto i = convexShapes_.begin(); i != convexShapes_.end(); i++)
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
		for (auto i = convexShapes_.begin(); i != convexShapes_.end(); i++)
		{
			if ((*i)->intersects(circle))
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
		for (auto i = convexShapes_.begin(); i != convexShapes_.end(); i++)
		{
			if ((*i)->contains(point))
			{
				return true;
			}
		}
		return false;
	}
}