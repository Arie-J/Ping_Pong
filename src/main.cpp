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
	int windowWidth {static_cast<int>(window.getSize().x)};
	int windowHeight {static_cast<int>(window.getSize().y)};
	std::cout << windowWidth << "\n";

	//GameStates Control(Initializing a enum for managing Game states)
	GameStates gameState {GameStates::MainMenu};

	//Create Objects other game Variables here for initialisation and set their initial values.
	PlayerBar P1{};
	auto playerSpeed = 500; //500 pixels per second

	PlayerBar O1{10.f,150.f,true,800.f}; //height of Opponent(O1) is 10 pixels and width is 150 pixels.
	O1.moveToPositon(windowWidth - 100,windowHeight/2); //Center of the paddle is given.
	auto opponentSpeed = 300.f; //300 pixels per second

	PlayerBar M1{600.f,10.f,false};//size of unmoving map obstacle is 600 width and 10 height
	M1.moveToPositon(windowWidth/2,0.f);//center of obstacle

	PlayerBar M2{600.f,10.f,false};//size of unmoving map obstacle is 600 width and 10 height
	M2.moveToPositon(windowWidth/2,windowHeight);//center of obstacle

	Ball b1{10.f,{windowWidth,windowHeight}}; //radius of ball is 10 pixels and is present at center of screen, the second argument takes window size.
	b1.giveVelocity({400.f,300.f}); //Velocity is set with magnitude 500 as constant.

	//loading some fonts.
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

	//Various Menus have been made using texts. 
	MenuText pauseScreen{font1,"PAUSED",150,{400.f,220.f}};
	pauseScreen.createText();

	MenuText pauseScreenDirection1{font1,"Press Enter To Go Back To Main Menu",50,{400.f,310.f}};
	pauseScreenDirection1.createText();

	MenuText pauseScreenDirection2{font1,"Press Escape To Continue Playing",50,{400.f,370.f}};
	pauseScreenDirection2.createText();

	MenuText scoreCounter(font1,"0",100,{400.f,60.f});
	scoreCounter.createText();
	scoreCounter.setAlpha(100);
	int score {0}; // This is a score that can be negative. The ball object carries the real score value in m_score member.

	MenuText gameOverTxt1{font1,"GAME OVER!",150,{400.f,240.f}};
	gameOverTxt1.createText();

	MenuText gameOverTxt2{font1,"SCORE:",80,{365.f,350.f}};
	gameOverTxt2.createText();

	MenuText gameOverTxt3Counter{font1,"0",80,{498.f,350.f}};
	gameOverTxt3Counter.createText();

	MenuText gameOverTxt4{font1,"Press Enter To Continue...",30,{400.f,450.f}};
	gameOverTxt4.createText();

	MenuText mainMenuTxt1{font1,"Ping Pong",150,{400.f,240.f}};
	mainMenuTxt1.createText();

	MenuText mainMenuTxt2{font1,"Press Enter to Play",80,{400.f,370.f}};
	mainMenuTxt2.createText();

	//clocks for deltaTime. (Decoupling the physics from the processor speed using deltaTime)
	sf::Clock clock;
	sf::Clock unpauseTimer; // Cooldown timer after unpausing to smoothen the transition
	bool hasUnpaused{false}; //state variable for the cooldown

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
						//reset the ball to initial condition.
						score = 0;
						b1.resetScore();
						b1.giveVelocity({400.f,300.f});
						b1.setPosition(windowWidth/2,windowHeight/2);
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
				case GameStates::Scored:
				{
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
			gameOverTxt3Counter.setTextint(score);
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
			window.draw(mainMenuTxt1.getText());
			window.draw(mainMenuTxt2.getText());
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
			window.draw(gameOverTxt1.getText());
			window.draw(gameOverTxt2.getText());
			window.draw(gameOverTxt3Counter.getText());
			window.draw(gameOverTxt4.getText());
			break;
		}
		case GameStates::Scored:
		{
			break;
		}
		}

		//Mandatory display for displaying Graphics
		window.display();
		
	}
	
}
