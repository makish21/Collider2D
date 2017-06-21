#include <SFML\Graphics.hpp>
#include <vector>
#include <CollisionDetection.hpp>


void main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "asdasd");

	sf::CircleShape shape1(50, 3);

	sf::VertexArray shape2(sf::PrimitiveType::TrianglesStrip, 10);

	shape2[0].position = sf::Vector2f(400.f, 300.f);
	shape2[1].position = sf::Vector2f(400.f, 350.f);
	shape2[2].position = sf::Vector2f(450.f, 300.f);
	shape2[3].position = sf::Vector2f(450.f, 350.f);
	shape2[4].position = sf::Vector2f(475.f, 325.f);
	shape2[5].position = sf::Vector2f(475.f, 375.f);
	shape2[6].position = sf::Vector2f(500.f, 325.f);
	shape2[7].position = sf::Vector2f(500.f, 375.f);
	shape2[8].position = sf::Vector2f(550.f, 350.f);
	shape2[9].position = sf::Vector2f(550.f, 400.f);

	std::vector<sf::Vector2f> points1, points2;

	float angle1 = 0.f;

	shape1.setOrigin(50, 50);

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
				shape1.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
				break;

			case sf::Event::MouseButtonReleased:
				angle1 = 0.f;
				break;

			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					angle1 = 0.05f;
					break;

				case sf::Mouse::Right:
					//angle2 = 0.05f;
					break;

				default:
					break;
				}


			case sf::Event::KeyPressed:

				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					shape1.setPointCount(shape1.getPointCount() + 1);
					break;

				case sf::Keyboard::Down:
					shape1.setPointCount(shape1.getPointCount() - 1);
					break;

				case sf::Keyboard::Right:
					break;

				case sf::Keyboard::Left:
					break;

				default:
					break;
				}

			default:
				break;
			}
		}

		points1.clear();
		points2.clear();
		for (int i = 0; i < shape1.getPointCount(); i++)
		{
			points1.push_back(shape1.getTransform().transformPoint(shape1.getPoint(i)));
		}
		for (int i = 0; i < shape2.getVertexCount(); i++)
		{
			points2.push_back(shape2[i].position);
		}

		shape1.setFillColor(sf::Color::Green);

		for (int i = 0; i < shape2.getVertexCount(); i++)
		{
			shape2[i].color = sf::Color::Magenta;
		}

		shape1.rotate(angle1);

		if (cd::intersects(points1, points2))
		{
			shape1.setFillColor(sf::Color::Red);
			for (int i = 0; i < shape2.getVertexCount(); i++)
			{
				shape2[i].color = sf::Color::Red;
			}
		}

		window.clear();

		window.draw(shape1);
		window.draw(shape2);

		window.display();
	}
}