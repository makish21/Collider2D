#include <SFML\Graphics.hpp>
#include <vector>

#include "ConcaveCollidableShape.h"
#include "CircleCollidableShape.h"
#include "RectangleCollidableShape.h"
#include "ConvexCollidableShape.h"

sf::Color generateRandomColor()
{
	return sf::Color(std::rand() % 255,
					 std::rand() % 255,
					 std::rand() % 255);
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16U;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Collision Example", sf::Style::Close, settings);
	window.setFramerateLimit(60U);
	window.setKeyRepeatEnabled(false);

	sf::VertexArray newConcaveShape;
	CollidableShape* selectedShape = nullptr;

	sf::VertexArray lines(sf::Lines);

	sf::Vector2f mousePosition;

	sf::Font helvetica;
	helvetica.loadFromFile("HelveticaRegular.ttf");

	std::vector<CollidableShape*> collidableShapes;

	collidableShapes.push_back(new CircleCollidableShape(sf::Vector2f(400.f, 300.f), 50.f,
														 generateRandomColor(),
														 helvetica));

	collidableShapes.push_back(new CircleCollidableShape(sf::Vector2f(600.f, 400.f), 70.f,
														 generateRandomColor(),
														 helvetica));

	collidableShapes.push_back(new RectangleCollidableShape(sf::Rect<float>(100.f, 100.f, 100.f, 250.f),
															generateRandomColor(),
															helvetica));

	sf::Event event;

	sf::Clock clock;
	int updates = 0;

	while (window.isOpen())
	{
		std::srand(static_cast<unsigned int>(std::time(0)));

		if (window.hasFocus())
		{
			if (clock.getElapsedTime().asSeconds() > 1)
			{
				std::string title = "Collision Example | Updates: ";
				title.append(std::to_string(updates));
				window.setTitle(title);
				clock.restart();
				updates = 0;
			}
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
						if ((*i)->getCollision().contains(cd::Vector2<float>(mousePosition.x, 
																			 mousePosition.y)))
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
							newConcaveShape.setPrimitiveType(sf::TrianglesStrip);
							newConcaveShape.append(sf::Vertex(mousePosition,
															  sf::Color::Transparent));

							lines.append(sf::Vertex(mousePosition,
													sf::Color::White));

							if (newConcaveShape.getVertexCount() >= 2)
							{
								lines.append(sf::Vertex(newConcaveShape[newConcaveShape.getVertexCount() - 2].position,
														sf::Color::White));
								lines.append(sf::Vertex(newConcaveShape[newConcaveShape.getVertexCount() - 1].position,
														sf::Color::White));
								lines.append(sf::Vertex(newConcaveShape[newConcaveShape.getVertexCount() - 2].position,
														sf::Color::White));
							}
						}

						if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
						{
							newConcaveShape.setPrimitiveType(sf::TrianglesFan);
							newConcaveShape.append(sf::Vertex(mousePosition,
															  sf::Color::Transparent));

							lines.append(sf::Vertex(mousePosition,
													sf::Color::White));

							if (newConcaveShape.getVertexCount() >= 2)
							{
								lines.append(sf::Vertex(newConcaveShape[0].position,
														sf::Color::White));
								lines.append(sf::Vertex(newConcaveShape[newConcaveShape.getVertexCount() - 1].position,
														sf::Color::White));
								lines.append(sf::Vertex(newConcaveShape[newConcaveShape.getVertexCount() - 1].position,
														sf::Color::White));
							}
						}

						if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
						{
							newConcaveShape.setPrimitiveType(sf::TrianglesFan);
							newConcaveShape.append(sf::Vertex(mousePosition,
															  sf::Color::Transparent));

							lines.append(sf::Vertex(mousePosition,
													sf::Color::White));

							if (newConcaveShape.getVertexCount() >= 2)
							{
								lines.append(sf::Vertex(newConcaveShape[newConcaveShape.getVertexCount() - 1].position,
														sf::Color::White));
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
						collidableShapes.push_back(new ConcaveCollidableShape(newConcaveShape,
																			  cd::TriangleStrip,
																			  generateRandomColor(),
																			  helvetica));

						newConcaveShape.clear();
						lines.clear();

						break;
					}

					case sf::Keyboard::LShift:
					{
						collidableShapes.push_back(new ConcaveCollidableShape(newConcaveShape,
																			  cd::TriangleFan,
																			  generateRandomColor(),
																			  helvetica));

						newConcaveShape.clear();
						lines.clear();

						break;
					}

					/*case sf::Keyboard::LAlt:
					{
						collidableShapes.push_back(new ConcaveCollidableShape(newConcaveShape,
																			  cd::Triangles,
																			  generateRandomColor(),
																			  helvetica));

						newConcaveShape.clear();
						lines.clear();

						break;
					}*/

					case sf::Keyboard::LAlt:
					{
						collidableShapes.push_back(new ConvexCollidableShape(newConcaveShape,
																			  cd::Triangles,
																			  generateRandomColor(),
																			  helvetica));

						newConcaveShape.clear();
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

			updates++;
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