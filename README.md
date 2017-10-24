# Collider2D

Collider2D is a simple, object-oriented library for 2D collision detection.

## Download

Visual C++ ( [32-bit](https://drive.google.com/uc?export=download&id=0B5uXbOSPUOk3dUVYbGhldWJUNTQ) | [64-bit](https://drive.google.com/uc?export=download&id=0B5uXbOSPUOk3NkNId1ZaZlY5bmM) )

## Installing

In the project's properties, add:
 * The path to the Collider2D headers (*collider2d-install-path/include*) to *C/C++ > General > Additional Include Directories*
 * The path to the Collider2D libraries (*collider2d-install-path/lib*) to *Linker > General > Additional Library Directories*

These paths are the same in both **Debug** and **Release** configuration. 

Library must be added in the project's properties, in *Linker > Input > Additional Dependencies*.

 * For **Debug** - `Collider2D-d.lib`
 * For **Release** - `Collider2D.lib`

## Usage example

The library uses the `cd::` namespace.

``` Cpp
#include <vector>
#include <CollisionDetection.hpp>

int main()
{
	// create array of vertices
	std::vector<cd::Vector2<float>> vertices(5);

	// initialize it
	vertices[0] = cd::Vector2<float>(100.f, 80.f);
	// ...

	// create a convex shape from array of vertices
	cd::ConvexCollision convex(&vertices[0], vertices.size());

	// create another circle collision from its position and radius
	cd::CircleCollision circle(cd::Vector2<float>(100.f, 100.f), 50.f);

	// check if collisions overlap
	if (convex.intersects(circle))
	{
		// do something
	}

	// you can change the collisions
	convex[2].x = 20.f;
	convex[4] = cd::Vector2<float>(50.f, 50.f);

	circle.setRadius(150.f);

	// create a point
	cd::Vector2<float> point(80.f, 80.f);

	// check if collisions contain the point;
	if (convex.contains(point))
	{
		// do something
	}

	if (circle.contains(point))
	{
		// do something
	}

	return 0;
}
```

### Supported collision types:

 * AABB
 * Circle
 * Convex
 * Compound

For **CompoundCollision** there are the following *PrimitiveTypes*:

 * Triangles
 * TriangleFan
 * TriangleStrip

## License

The **Collider2D** libraries and source code are under [MIT license](https://github.com/makish21/Collider2D/blob/master/LICENSE).  
The example uses [SFML](https://www.sfml-dev.org/) which is under [zlib/png license](https://www.sfml-dev.org/license.php).
