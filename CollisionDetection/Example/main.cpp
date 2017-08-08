#include <SFML\Graphics.hpp>
#include <vector>

#include "ConcaveCollidableShape.h"
#include "CircleCollidableShape.h"
#include "RectangleCollidableShape.h"

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16U;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Collision Example", sf::Style::Close, settings);
	window.setFramerateLimit(60U);
	window.setKeyRepeatEnabled(false);

	sf::VertexArray newShape;
	CollidableShape* selectedShape = nullptr;

	sf::VertexArray lines(sf::LineStrip);

	sf::Vector2f mousePosition;

	std::vector<CollidableShape*> collidableShapes;

	collidableShapes.push_back(new CircleCollidableShape(sf::Vector2f(400.f, 300.f), 50.f, sf::Color::Cyan));
	collidableShapes.push_back(new RectangleCollidableShape(sf::Rect<float>(100.f, 100.f, 100.f, 250.f), sf::Color::Magenta));

	sf::Event event;

	while (window.isOpen())
	{
		if (window.hasFocus())
		{
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseMoved:

					mousePosition = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selectedShape)
					{
						selectedShape->setPosition(mousePosition);
						selectedShape->updateCollision();
					}
					break;

				case sf::Event::MouseButtonPressed:

					if (selectedShape)
					{
						selectedShape->showWireframe(false);
						selectedShape = nullptr;
					}

					for (auto i = collidableShapes.begin(); i != collidableShapes.end(); i++)
					{
						if ((*i)->getCollision().contains(mousePosition))
						{
							selectedShape = (*i);
							selectedShape->showWireframe(true);
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
						collidableShapes.push_back(new ConcaveCollidableShape(newShape, cd::TriangleStrip, sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255)));

						newShape.clear();
						lines.clear();

						break;
					}

					case sf::Keyboard::LShift:
					{
						ConcaveCollidableShape collidableShape(newShape, cd::TriangleFan, sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255));

						collidableShapes.push_back(new ConcaveCollidableShape(collidableShape));

						newShape.clear();
						lines.clear();

						break;
					}

					default:
						break;
					}

				default:
					break;
				}
			} // window.pollEvent()

			if (selectedShape)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					selectedShape->rotate(1.f);
					selectedShape->updateCollision();
				}

				selectedShape->resetColor();

				for (auto i = collidableShapes.begin(); i != collidableShapes.end(); i++)
				{
					if ((*i) == selectedShape)
					{
						continue;
					}

					if ((*i)->getCollision().intersects(selectedShape->getCollision()))
					{
						(*i)->setColor(sf::Color::Red);
						(*i)->showWireframe(true);
						selectedShape->setColor(sf::Color::Red);
					}
					else
					{
						(*i)->showWireframe(false);
						(*i)->resetColor();
					}
				}
			}

			window.clear();

			for (auto i = collidableShapes.begin(); i != collidableShapes.end(); i++)
			{
				window.draw(**i);
			}

			window.draw(lines);

			window.display();
		}
		else // window.hasFocus()
		{
			window.waitEvent(event);
		}
	} // window.isOpen()

	for (auto i = collidableShapes.begin(); i != collidableShapes.end(); i++)
	{
		if (*i)
		{
			delete *i;
			*i = nullptr;
		}
	}

	return 0;
}