#include "CompoundShapeCollision.h"
#include "ConvexShapeCollision.h"

namespace cd
{
	CompoundShapeCollision::CompoundShapeCollision()
	{
	}

	CompoundShapeCollision::CompoundShapeCollision(const std::vector<ConvexShapeCollision>& convexShapes) :
		convexShapes_(convexShapes)
	{
	}

	CompoundShapeCollision::CompoundShapeCollision(const std::vector<VECTOR<float>>& vertices, const PrimitiveType& type)
	{
		append(vertices, type);
	}

	CompoundShapeCollision::~CompoundShapeCollision()
	{
	}

	void CompoundShapeCollision::append(const ConvexShapeCollision & convex)
	{
		convexShapes_.push_back(convex);
	}

	void CompoundShapeCollision::append(const std::vector<VECTOR<float>>& vertices, const PrimitiveType & type)
	{
		switch (type)
		{
		case TriangleStrip:
			for (int i = 2; i < vertices.size(); i++)
			{
				ConvexShapeCollision triangle(3);

				for (int j = 0, k = i - 2;
					k <= i;
					j++, k++)
				{
					triangle[j] = vertices[k];
				}

				convexShapes_.push_back(triangle);
			}
			break;

		case TriangleFan:
			for (int i = 2; i < vertices.size(); i++)
			{
				ConvexShapeCollision triangle(3);

				for (int j = 0, k = 0;
					k <= i;
					j++, k = i - 1 + j - 1)
				{
					triangle[j] = vertices[k];
				}

				convexShapes_.push_back(triangle);
			}
			break;
		default:
			break;
		}
	}

	void CompoundShapeCollision::clear()
	{
		convexShapes_.clear();
	}

	bool CompoundShapeCollision::intersects(const CompoundShapeCollision & other) const
	{
		for (auto i = convexShapes_.begin(); i != convexShapes_.end(); i++)
		{
			for (auto j = other.convexShapes_.begin(); j != other.convexShapes_.end(); j++)
			{
				if (i->intersects(*j))
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
			if (i->intersects(convex))
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
			if (i->intersects(circle))
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
			if (i->contains(point))
			{
				return true;
			}
		}
		return false;
	}
}