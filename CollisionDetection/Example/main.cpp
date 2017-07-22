#include <SFML\Graphics.hpp>
#include <vector>

#include "CompoundCollidableShape.h"
#include "CircleCollidableShape.h"

void main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Collision Example", sf::Style::Close, settings);
	
	sf::VertexArray newShape(sf::TrianglesStrip);
	CollidableShape* selectedShape = nullptr;

	sf::RectangleShape point(sf::Vector2f(4.f, 4.f));
	point.setOrigin(2.f, 2.f);
	point.setFillColor(sf::Color::White);
	std::vector<sf::RectangleShape> points;
	sf::VertexArray lines(sf::LinesStrip);

	sf::Vector2f mousePosition;

	std::vector<CollidableShape*> collidableShapes;

	collidableShapes.push_back(new CircleCollidableShape(sf::Vector2f(400.f, 300.f), 50.f, sf::Color::Magenta));

	sf::Event event;

	float angle = 0.0f;

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

				mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selectedShape)
				{
					selectedShape->setPosition(mousePosition);
					selectedShape->updateCollision();
				}
				break;

			case sf::Event::MouseButtonReleased:

				selectedShape = nullptr;

				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					break;

				case sf::Mouse::Right:
					angle = 0.0f;
					break;

				default:
					break;
				}

				break;

			case sf::Event::MouseButtonPressed:
				for (auto i = collidableShapes.begin(); i != collidableShapes.end(); i++)
				{
					if ((*i)->getCollision().contains(mousePosition))
					{
						selectedShape = (*i);
					}
				}

				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
				{
					if (selectedShape)
					{
						selectedShape->setOrigin(selectedShape->getInverseTransform().transformPoint(mousePosition));
						selectedShape->setPosition(mousePosition);
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
					{
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
					if (selectedShape)
					{
						selectedShape->setOrigin(selectedShape->getInverseTransform().transformPoint(mousePosition));
						selectedShape->setPosition(mousePosition);
						angle = 0.3f;
					}
					break;

				default:
					break;
				}

			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::LControl:
				{
					CompoundCollidableShape collidableShape(newShape, cd::TriangleStrip, sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255));

					collidableShapes.push_back(new CompoundCollidableShape(collidableShape));

					newShape.clear();
					points.clear();
					lines.clear();

					break;
				}

				case sf::Keyboard::LShift:
				{
					CompoundCollidableShape collidableShape(newShape, cd::TriangleFan, sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255));

					collidableShapes.push_back(new CompoundCollidableShape(collidableShape));

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

		if (selectedShape)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				selectedShape->rotate(angle);
				selectedShape->updateCollision();
			}
			
			for (auto i = collidableShapes.begin(); i != collidableShapes.end(); i++)
			{
				if ((*i) != selectedShape)
				{
					if ((*i)->getCollision().intersects(selectedShape->getCollision()))
					{
						(*i)->setColor(sf::Color::Red);
						selectedShape->setColor(sf::Color::Red);
					}
					else
					{
						(*i)->setColor((*i)->getDefaultColor());
						selectedShape->setColor(selectedShape->getDefaultColor());
					}
				}
			}
		}

		window.clear();

		for (auto i = collidableShapes.begin(); i != collidableShapes.end(); i++)
		{
			window.draw(**i);
		}

		window.draw(lines);

		for (auto i = points.begin(); i != points.end(); i++)
		{
			window.draw(*i);
		}

		window.display();
	}
}