//include all classes and headers related to those classes. Add other Pre-Processing Directives.
#include "Headers.hpp"

int main()
{
	
	//Setting up SFML
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	//Generating a Render Window
	sf::RenderWindow window(sf::VideoMode({800,600}),"Hello World!",sf::Style::Default);
	window.setVerticalSyncEnabled(true);  

	//GameStates Control(Initializing a enum for managing Game states)
	GameStates gameState {GameStates::Playing};

	//Create Objects other game Variables here for initialisation and set their initial values.
	PlayerBar P1{};

	PlayerBar O1{10.f,600.f};
	O1.moveToPositon(790.f,300.f);

	Ball b1{};
	b1.giveVelocity({100.f,20.f});


	sf::Clock clock;

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		
		//Checking events with a state Machine using scoped enum defined in GameStates.hpp
		while (const std::optional event = window.pollEvent())
		{
			if(event -> is <sf::Event::Closed>())
			{
				window.close();
			}
			if(const auto keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				switch(gameState)
				{
				case GameStates::MainMenu:
				{
					//check for Enter key to switch over to Playing
					if(keyPressed->scancode == sf::Keyboard::Scancode::Enter)
					{
						gameState = GameStates::Playing;
					}
					
					break;
				}
				case GameStates::Playing:
				{
					//check for Escape key to switch to Paused
					//The Pause Button will be a toggle
					if(keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					{
						gameState = GameStates::Paused;
					}
					break;
				}
				case GameStates::Paused:
				{
					//check for Escape key to switch over to Playing 
					if(keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					{
						gameState = GameStates::Playing;
					}
					//check for Enter to switch Over to GameOver
					if(keyPressed->scancode == sf::Keyboard::Scancode::Enter)
					{
						gameState = GameStates::GameOver;
					}
					break;
				}

				case GameStates::GameOver:
				{
					//check for Enter key to switch over to MainMenu
					if(keyPressed->scancode == sf::Keyboard::Scancode::Enter)
					{
						gameState = GameStates::MainMenu;
					}
					break;
				}

			}
			}
		}		

		//calculating delta time 
		sf::Time deltaTime = clock.restart();

		//Updating the logic (Calculating Physics, deltaTime, etc.) based on state
		switch (gameState)
		{
		case GameStates::Playing:
		{
			b1.calcPhysics(deltaTime);
			b1.calcCollisions(P1);
			b1.calcCollisions(O1);

			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			P1.moveToPositon(100.f,static_cast<float>(mousePos.y));
			break;
		}
		case GameStates::MainMenu:
		{
			break;
		}
		case GameStates::Paused:
		{
			break;
		}
		case GameStates::GameOver:
		{
			break;
		}
		}

		//Rendering Graphics as per Gamestate 
		switch(gameState)
		{
		case GameStates::Playing:
		{
			window.draw(P1.createShape());
			window.draw(b1.createShape());
			window.draw(O1.createShape());
			break;
		}
		case GameStates::MainMenu:
		{
			break;
		}
		case GameStates::Paused:
		{
			break;
		}
		case GameStates::GameOver:
		{
			break;
		}
		}

		//Mandatory display for displaying Graphics
		
		window.display();
		
	}
	
}
