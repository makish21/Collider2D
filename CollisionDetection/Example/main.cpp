#include <SFML\Graphics.hpp>
#include <vector>
#include <CollisionDetection.hpp>

#include <iostream>

struct CollidableShape : public sf::Transformable, public sf::Drawable
{
	sf::Color color;
	sf::VertexArray shape;
	cd::Collision<float> collision;

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
	std::vector<sf::RectangleShape> points;
	sf::VertexArray lines(sf::LinesStrip);

	std::vector<CollidableShape> collidableShapes;

	sf::Event event;

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
				break;

			case sf::Event::MouseButtonReleased:
				break;

			case sf::Event::MouseButtonPressed:

				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
					{
						sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

						sf::RectangleShape point(sf::Vector2f(4.f, 4.f));
						point.setOrigin(2.f, 2.f);
						point.setFillColor(sf::Color::White);
						point.setPosition(mousePosition);

						points.push_back(point);

						newShape.append(sf::Vertex(mousePosition, sf::Color::Transparent));

						lines.append(sf::Vertex(mousePosition, sf::Color::White));

						if (newShape.getVertexCount() >= 2)
						{
							lines.append(sf::Vertex(newShape[newShape.getVertexCount() - 2].position, sf::Color::White));
						}
					}

					break;
				}

				case sf::Mouse::Right:
				{

				}
					break;

				default:
					break;
				}
				

			case sf::Event::KeyPressed:

				switch (event.key.code)
				{
				case sf::Keyboard::Return:
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
				
				default:
					break;
				}

			default:

				std::cout << event.key.control << " " << event.key.alt << " " << event.key.shift << std::endl;

				break;
			}
		}

		for (auto i = collidableShapes.begin(); i != collidableShapes.end(); i++)
		{
			for (auto j = collidableShapes.begin(); j != collidableShapes.end(); j++)
			{
				if (i != j && cd::intersects(i->collision, j->collision))
				{
					for (int k = 0; k < i->shape.getVertexCount(); k++)
					{
						i->shape[k].color = sf::Color::Red;
					}
					for (int k = 0; k < j->shape.getVertexCount(); k++)
					{
						j->shape[k].color = sf::Color::Red;
					}
				}
			}

			if (cd::contains(i->collision, sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				for (int k = 0; k < i->shape.getVertexCount(); k++)
				{
					i->shape[k].color = sf::Color::Yellow;
				}
			}
			else
			{
				for (int k = 0; k < i->shape.getVertexCount(); k++)
				{
					i->shape[k].color = i->color;
				}
			}
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