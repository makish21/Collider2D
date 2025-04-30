#include <SFML\Graphics.hpp>
#include <vector>

#include "ConcaveCollidableShape.hpp"
#include "CircleCollidableShape.hpp"
#include "RectangleCollidableShape.hpp"
#include "ConvexCollidableShape.hpp"

sf::Color generateRandomColor()
{
	return sf::Color(std::rand() % 255,
					 std::rand() % 255,
					 std::rand() % 255);
}

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	sf::ContextSettings settings;
	settings.antiAliasingLevel = 16U;
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Collision Example", sf::State::Windowed, settings);
	window.setFramerateLimit(60U);
	window.setKeyRepeatEnabled(false);

	sf::VertexArray newConcaveShape;
	CollidableShape *selectedShape = nullptr;

	sf::VertexArray lines = sf::VertexArray(sf::PrimitiveType::Lines);

	sf::Vector2f mousePosition;

	sf::Font helvetica = sf::Font("assets/helvetica_regular.otf");

	std::vector<CollidableShape *> collidableShapes;

	collidableShapes.push_back(new CircleCollidableShape(sf::Vector2f(400.f, 300.f), 50.f,
														 generateRandomColor(),
														 helvetica));

	collidableShapes.push_back(new CircleCollidableShape(sf::Vector2f(600.f, 400.f), 70.f,
														 generateRandomColor(),
														 helvetica));

	collidableShapes.push_back(new RectangleCollidableShape(sf::Rect<float>({100.f, 100.f}, {100.f, 250.f}),
															generateRandomColor(),
															helvetica));

	while (window.isOpen())
	{
		while (const std::optional event = window.isOpen() ? window.pollEvent() : window.waitEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (event->is<sf::Event::MouseMoved>())
			{
				mousePosition = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selectedShape)
				{
					selectedShape->setPosition(mousePosition);
					selectedShape->updateCollision();
				}
			}
			else if (const auto *pressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
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

				switch (pressed->button)
				{
				case sf::Mouse::Button::Left:
				{
					if (selectedShape)
					{
						selectedShape->setOrigin(selectedShape->getInverseTransform().transformPoint(mousePosition));
						selectedShape->setPosition(mousePosition);
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
					{
						newConcaveShape.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
						newConcaveShape.append({mousePosition, sf::Color::Transparent});

						lines.append({mousePosition, sf::Color::White});

						if (newConcaveShape.getVertexCount() >= 2)
						{
							lines.append({newConcaveShape[newConcaveShape.getVertexCount() - 2].position, sf::Color::White});
							lines.append({newConcaveShape[newConcaveShape.getVertexCount() - 1].position, sf::Color::White});
							lines.append({newConcaveShape[newConcaveShape.getVertexCount() - 2].position, sf::Color::White});
						}
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
					{
						newConcaveShape.setPrimitiveType(sf::PrimitiveType::TriangleFan);
						newConcaveShape.append({mousePosition, sf::Color::Transparent});

						lines.append({mousePosition, sf::Color::White});

						if (newConcaveShape.getVertexCount() >= 2)
						{
							lines.append({newConcaveShape[0].position, sf::Color::White});
							lines.append({newConcaveShape[newConcaveShape.getVertexCount() - 1].position, sf::Color::White});
							lines.append({newConcaveShape[newConcaveShape.getVertexCount() - 1].position, sf::Color::White});
						}
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt))
					{
						newConcaveShape.setPrimitiveType(sf::PrimitiveType::TriangleFan);
						newConcaveShape.append({mousePosition, sf::Color::Transparent});

						lines.append({mousePosition, sf::Color::White});

						if (newConcaveShape.getVertexCount() >= 2)
						{
							lines.append({newConcaveShape[newConcaveShape.getVertexCount() - 1].position, sf::Color::White});
						}
					}

					break;
				}

				case sf::Mouse::Button::Right:
					if (selectedShape)
					{
						selectedShape->setOrigin(selectedShape->getInverseTransform().transformPoint(mousePosition));
						selectedShape->setPosition(mousePosition);
					}
					break;

				default:
					break;
				}
			}
			else if (const auto *released = event->getIf<sf::Event::KeyReleased>())
			{
				switch (released->code)
				{
				case sf::Keyboard::Key::LControl:
				{
					collidableShapes.push_back(new ConcaveCollidableShape(newConcaveShape,
																		  cd::TriangleStrip,
																		  generateRandomColor(),
																		  helvetica));

					newConcaveShape.clear();
					lines.clear();

					break;
				}

				case sf::Keyboard::Key::LShift:
				{
					collidableShapes.push_back(new ConcaveCollidableShape(newConcaveShape,
																		  cd::TriangleFan,
																		  generateRandomColor(),
																		  helvetica));

					newConcaveShape.clear();
					lines.clear();

					break;
				}

					/*case sf::Keyboard::Key::LAlt:
					{
						collidableShapes.push_back(new ConcaveCollidableShape(newConcaveShape,
																			  cd::Triangles,
																			  generateRandomColor(),
																			  helvetica));

						newConcaveShape.clear();
						lines.clear();

						break;
					}*/

				case sf::Keyboard::Key::LAlt:
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
			}
		} // window.pollEvent()

		if (selectedShape)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			{
				selectedShape->rotate(sf::degrees(1.f));
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