#include <SFML\Graphics.hpp>
#include <vector>
#include <CollisionDetection.hpp>

struct CollidableShape : public sf::Transformable, public sf::Drawable
{
	sf::Color color;
	sf::VertexArray shape;
	cd::Collision<float> collision;

	void updateCollision()
	{
		std::vector<sf::Vector2f> vertices;
		for (int i = 0; i < shape.getVertexCount(); i++)
		{
			vertices.push_back(getTransform().transformPoint(shape[i].position));
		}

		collision = cd::Collision<float>(vertices);
	}
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(shape, states);
	}
};

void main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Collision Example", sf::Style::Close, settings);
	
	sf::VertexArray newShape(sf::TrianglesStrip);
	CollidableShape* selectedShape = nullptr;


	std::vector<sf::RectangleShape> points;
	sf::VertexArray lines(sf::LinesStrip);

	sf::Vector2f mousePosition;

	std::vector<CollidableShape> collidableShapes;

	sf::Event event;

	float angle = 0.f;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selectedShape)
				{
					selectedShape->setPosition(mousePosition);
					selectedShape->updateCollision();
				}
				break;

			case sf::Event::MouseButtonReleased:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					selectedShape = nullptr;
					break;

				case sf::Mouse::Right:
					angle = 0.f;
					break;

				default:
					break;
				}

				break;

			case sf::Event::MouseButtonPressed:

				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
				{
					for (auto i = collidableShapes.begin(); i != collidableShapes.end(); i++)
					{
						if (cd::contains(i->collision, mousePosition))
						{
							selectedShape = &(*i);
							selectedShape->setOrigin(selectedShape->getOrigin() - selectedShape->getPosition() + mousePosition);
							selectedShape->setPosition(mousePosition);
						}
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
					{
						sf::RectangleShape point(sf::Vector2f(4.f, 4.f));
						point.setOrigin(2.f, 2.f);
						point.setFillColor(sf::Color::White);
						point.setPosition(mousePosition);

						points.push_back(point);

						newShape.setPrimitiveType(sf::TrianglesStrip);
						newShape.append(sf::Vertex(mousePosition, sf::Color::Transparent));

						lines.append(sf::Vertex(mousePosition, sf::Color::White));

						if (newShape.getVertexCount() >= 2)
						{
							lines.append(sf::Vertex(newShape[newShape.getVertexCount() - 2].position, sf::Color::White));
						}
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					{
						sf::RectangleShape point(sf::Vector2f(4.f, 4.f));
						point.setOrigin(2.f, 2.f);
						point.setFillColor(sf::Color::White);
						point.setPosition(mousePosition);

						points.push_back(point);

						newShape.setPrimitiveType(sf::TrianglesFan);
						newShape.append(sf::Vertex(mousePosition, sf::Color::Transparent));

						lines.append(sf::Vertex(mousePosition, sf::Color::White));

						if (newShape.getVertexCount() >= 2)
						{
							lines.append(sf::Vertex(newShape[0].position, sf::Color::White));
							lines.append(sf::Vertex(newShape[newShape.getVertexCount() - 1].position, sf::Color::White));
						}
					}

					break;
				}

				case sf::Mouse::Right:
				{
					for (auto i = collidableShapes.begin(); i != collidableShapes.end(); i++)
					{
						if (cd::contains(i->collision, mousePosition))
						{
							selectedShape = &(*i);
							//selectedShape->setOrigin(selectedShape->getOrigin() - selectedShape->getPosition() + mousePosition);
							selectedShape->setOrigin(selectedShape->getTransform().transformPoint(mousePosition));
							//selectedShape->getTransform().combine(sf::Transform::transformPoint(mousePosition));
							selectedShape->setPosition(mousePosition);
							angle = 0.1f;
						}
					}
				}

				default:
					break;
				}

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::LControl:
				{
					CollidableShape collidableShape;
					std::vector<sf::Vector2f> collision;

					collidableShape.color = sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255);

					for (int i = 0; i < newShape.getVertexCount(); i++)
					{
						newShape[i].color = collidableShape.color;
						collision.push_back(newShape[i].position);
					}

					collidableShape.shape = newShape;
					collidableShape.collision = cd::Collision<float>(collision);

					collidableShapes.push_back(collidableShape);

					newShape.clear();
					points.clear();
					lines.clear();

					break;
				}

				case sf::Keyboard::LShift:
				{
					CollidableShape collidableShape;
					std::vector<sf::Vector2f> collision;

					collidableShape.color = sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255);

					for (int i = 0; i < newShape.getVertexCount(); i++)
					{
						newShape[i].color = collidableShape.color;
						collision.push_back(newShape[i].position);
					}

					collidableShape.shape = newShape;
					collidableShape.collision = cd::Collision<float>(collision, cd::TrianglesFan);

					collidableShapes.push_back(collidableShape);

					newShape.clear();
					points.clear();
					lines.clear();

					break;
				}

				default:
					break;
				}
			
			default:
				break;
			}
		}

		mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

		for (auto i = collidableShapes.begin(); i != collidableShapes.end(); i++)
		{
			if (cd::contains(i->collision, sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				for (int k = 0; k < i->shape.getVertexCount(); k++)
				{
					i->shape[k].color = i->color - sf::Color(0, 0, 0, 64);
				}
			}
			else
			{
				for (int k = 0; k < i->shape.getVertexCount(); k++)
				{
					i->shape[k].color = i->color;
				}
			}

			if (selectedShape)
			{
				if (&(*i) != selectedShape && cd::intersects(i->collision, selectedShape->collision))
				{
					for (int k = 0; k < i->shape.getVertexCount(); k++)
					{
						i->shape[k].color = sf::Color::Red;
					}
					for (int k = 0; k < selectedShape->shape.getVertexCount(); k++)
					{
						selectedShape->shape[k].color = sf::Color::Red;
					}
				}
			}

			
		}
		
		if (selectedShape)
		{
			selectedShape->rotate(angle);
			selectedShape->updateCollision();
		}

		window.clear();

		for (auto i = collidableShapes.begin(); i != collidableShapes.end(); i++)
		{
			window.draw(*i);
		}

		window.draw(newShape);
		window.draw(lines);

		for (auto i = points.begin(); i != points.end(); i++)
		{
			window.draw(*i);
		}

		window.display();
	}
}