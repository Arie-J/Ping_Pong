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
	auto playerSpeed = 500;

	PlayerBar O1{10.f,150.f,true};
	O1.moveToPositon(700.f,300.f);
	auto opponentSpeed = 5000000.f;

	PlayerBar M1{600.f,10.f,false};
	M1.moveToPositon(400.f,5.f);

	PlayerBar M2{600.f,10.f,false};
	M2.moveToPositon(400.f,595.f);

	Ball b1{10.f,{800,600}};
	b1.giveVelocity({400.f,300.f});

	sf::Font font1;
    if (!font1.openFromFile("../../resources/FastelarDemoRegular.ttf")) 
    {
        std::cout << "Error loading font!" << "\n";
        return -1;
    }
	sf::Font font2;
    if (!font2.openFromFile("../../resources/Playful_time_font.ttf")) 
    {
        std::cout << "Error loading font!" << "\n";
        return -1;
    }

	MenuText pauseScreen{font1,"PAUSED",150,{400.f,220.f}};
	pauseScreen.createText();

	MenuText pauseScreenDirection1{font1,"Press Enter To Go Back To Main Menu",50,{400.f,310.f}};
	pauseScreenDirection1.createText();

	MenuText pauseScreenDirection2{font1,"Press Escape To Continue Playing",50,{400.f,370.f}};
	pauseScreenDirection2.createText();

	MenuText scoreCounter(font1,"0",100,{400.f,60.f});
	scoreCounter.createText();
	scoreCounter.setAlpha(100);
	int score {0};

	sf::Clock clock;
	sf::Clock unpauseTimer;
	bool hasUnpaused{false};

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
						unpauseTimer.restart();
						hasUnpaused = true;
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
			b1.calcCollisions(M1);
			b1.calcCollisions(M2);
			O1.chase(b1,deltaTime,opponentSpeed);
			score = b1.score();
			scoreCounter.setTextint(score);

			if(hasUnpaused)
			{
				if(unpauseTimer.getElapsedTime().asMilliseconds() > 100)
				{
					hasUnpaused = false;
				}
			}

			if(!hasUnpaused)
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
				{
					P1.moveUp(playerSpeed*deltaTime.asSeconds());
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
				{
					P1.moveDown(playerSpeed*deltaTime.asSeconds());
				}
			}
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
		case GameStates::Scored:
		{
			break;
		}

		}

		//Rendering Graphics as per Gamestate 
		switch(gameState)
		{
		case GameStates::Playing:
		{	
			
			P1.setPausedAppearance(false);
			O1.setPausedAppearance(false);
			b1.setPausedAppearance(false);
			M1.setPausedAppearance(false);
			M2.setPausedAppearance(false);
			window.draw(P1.createShape());
			window.draw(b1.createShape());
			window.draw(O1.createShape());
			window.draw(M1.createShape());
			window.draw(M2.createShape());
			window.draw(scoreCounter.getText());
			break;
		}
		case GameStates::MainMenu:
		{
			break;
		}
		case GameStates::Paused:
		{
			P1.setPausedAppearance(true);
			O1.setPausedAppearance(true);
			b1.setPausedAppearance(true);
			M1.setPausedAppearance(true);
			M2.setPausedAppearance(true);
			window.draw(P1.createShape());
			window.draw(b1.createShape());
			window.draw(O1.createShape());
			window.draw(M1.createShape());
			window.draw(M2.createShape());
			window.draw(pauseScreen.getText());
			window.draw(pauseScreenDirection1.getText());
			window.draw(pauseScreenDirection2.getText());
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
