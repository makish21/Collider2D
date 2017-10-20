#ifndef CONVEX_SHAPE_COLLISION_H
#define CONVEX_SHAPE_COLLISION_H

#include <vector>

#include "Collision.hpp"

namespace cd
{
	// Specialized collision representing a convex shape.
	class ConvexCollision :
		public Collision
	{
	public:
		// Default constructor.
		//
		// parameter vertexCount - initial number of vertices in the shape.
		ConvexCollision(size_t vertexCount = 0);

		// Construct the static collision from array of its vertices.
		//
		// Static vertices are created inside an instance and can be changed
		// only through operator []. All static vertices are deallocated
		// when instance is destroyed.
		//
		// parameter vertices[] - pointer to array of the vertices,
		// parameter vertexCount - array size.
		ConvexCollision(const Vector2<float> vertices[], size_t vertexCount);

		// Construct the dynamic collision from array of its vertices.
		//
		// Dynamic vertices are created outside an instance and can be changed
		// directly. Dynamic vertices are not deallocated when instance is
		// destroyed and must be deleted manually.
		//
		// parameter vertices[] - pointer to array of the vertices pointers,
		// parameter vertexCount - array size.
		ConvexCollision(Vector2<float>* vertices[], size_t vertexCount);

		// Destructor.
		~ConvexCollision();
		
		// Resize the number of the collision's vertices.
		//
		// If new size is greater than the current size, the previous
		// vertices are kept and new default-constructed vertices are
		// added.
		// If new size is less than the current size, existing vertices
		// are removed from the array.
		//
		// parameter newSize - new number of vertices.
		void resize(std::size_t newSize);

		// Return the vertex count.
		//
		// return number of vertices.
		std::size_t getVertexCount() const;

		// Add a static vertex to the collision.
		//
		// Static vertices are created inside an instance and can be changed
		// only through operator []. All static vertices are deallocated
		// when instance is destroyed.
		//
		// parameter vertex - vertex to add.
		void append(const Vector2<float>& vertex);

		// Add a dynamic vertex to the collision.
		//
		// Dynamic vertices are created outside an instance and can be changed
		// directly. Dynamic vertices are not deallocated when instance is
		// destroyed and must be deleted manually.
		//
		// parameter vertex - vertex to add.
		void append(Vector2<float>* vertex);

		// Clear the vertices array.
		//
		// This function removes all the vertices from collision and deallocates
		// all static vertices from memory.
		void clear();

		// Get the projection of the collision on the axis.
		//
		// parameter axis - axis for projection.
		//
		// return projection of the collision.
		Projection<float> getProjection(const Vector2<float>& axis) const;

		// Check the intersection with abstract base collision.
		//
		// parameter collision - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const Collision& collision) const;

		// Check the intersection with compound collision.
		//
		// parameter compound - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const CompoundCollision& compound) const;

		// Check the intersection with other convex collision.
		//
		// parameter other - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const ConvexCollision& other) const;

		// Check the intersection with circle collision.
		//
		// parameter circle - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const CircleCollision& circle) const;

		// Check the intersection with AABB collision.
		//
		// parameter aabb - collision to test.
		//
		// return true if collisions overlap, false otherwise.
		virtual bool intersects(const AABBCollision& aabb) const;

		// Check if a point is inside the collision's area.
		//
		// parameter point - point to test.
		//
		// return true if the point inside, false otherwise.
		virtual bool contains(const Vector2<float>& point) const;

		// Get a read-write access to a vertex by its index.
		//
		// This function checks an index. If is it out of range,
		// function returns vertex by [index % getVertexCount()].
		//
		// parameter index - index of the vertex to get.
		//
		// return reference to the index-th vertex.
		Vector2<float>& operator[](std::size_t index);

		// Get a read-only access to a vertex by its index.
		//
		// This function checks an index. If is it out of range,
		// function returns vertex by [index % getVertexCount()].
		//
		// parameter index - index of the vertex to get.
		//
		// return reference to the index-th vertex.
		const Vector2<float>& operator[](std::size_t index) const;

	private:
		std::vector<Vector2<float>*> m_vertices;           // Vector of pointers to vertices.
		std::vector<Vector2<float>**> m_allocatedVertices; // Vector of pointers to allocated vertices that must be deleted.
	};

} // namespace cd

#endif // CONVEX_SHAPE_COLLISION_H

// Class cd::ConvexCollision
//
// ConvexCollision is a collision representing a convex shape.
//
// A shape can be created from vertex points and must be convex.
// Otherwise the intersection of collisions will not be calculated
// correctly.
//
// Usage example:
//
// std::vector<cd::Vector2<float>> vertices;
//
// ...
//
// // ConvexCollision can be created from vector of points:
// cd::ConvexCollision collision(vertices[0], vertices.size());
//
// // Add a static vertex to the collision:
// collision.append(cd::Vector2<float>(100.f, 100.f));
//
// cd::Vector2<float> dynamicPoint(150.f, 200.f);
//
// // Add a dynamic vertex to the collision:
// collision.append(&dynamicPoint);
//
// if (collision.intersects(otherCollision))
// {
//		...
// }
// 
// Then the dynamic vertex can be changed:
// dynamicPoint.x = 120.f;
// dynamicPoint.y = 130.f;
//
// And new collision can be checked for intersection again:
// if (collision.intersects(otherCollision))
// {
//		...
// }
//
// if (collision.contains(mousePos))
// {
//		...
// }
//