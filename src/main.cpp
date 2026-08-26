#include <SFML/Graphics.hpp>

int main()
{

	sf::ContextSettings settings;
	settings.antiAliasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode({800,600}),"Hello World!",sf::Style::Default);
	window.setVerticalSyncEnabled(true);  

	sf::CircleShape triangle(180.f,3);
	triangle.setFillColor(sf::Color::White);
	triangle.setPosition({10.f,50.f});

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if(event -> is <sf::Event::Closed>())
			{
				window.close();
			}

			window.clear(sf::Color::Black);
			
			window.draw(triangle);

			window.display();
		}
		
	}
	

}
