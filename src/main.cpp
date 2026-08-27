#include <SFML/Graphics.hpp>
#include <algorithm>


class PlayerBar
{
public:

	PlayerBar(float width, float height)
	:	m_width{width}, m_height{height}
	{
	}

	PlayerBar() = default;

	sf::RectangleShape createShape() const
	{
		sf::RectangleShape bar({m_width,m_height});
		bar.setPosition({m_posX,m_posY});
		bar.setOrigin({m_width/2,m_height/2});
		return bar;
	}

	void moveToPositon(float x, float y)
	{
		m_posX = x;
		m_posY = y;
	}

	sf::Vector2f getPos()
	{
		return sf::Vector2f {m_posX,m_posY};
	}

	sf::Vector2f getSize()
	{
		return sf::Vector2f {m_width, m_height};
	}

private:
	float m_posX{100.f};
	float m_posY{100.f};
	float m_width{10.f};
	float m_height{150.f};
};

class Ball
{
public:

	Ball(float radius)
	:	m_radius{radius}
	{
	}
	Ball() = default;

	sf::CircleShape createShape()
	{
		sf::CircleShape temp{m_radius,45};
		temp.setPosition({m_posX,m_posY});
		return temp;
	}

	void giveVelocity(sf::Vector2f vel)
	{
		m_velocity = vel;
	}

	void calcPhysics(sf::Time timeObj)
	{
		float dt = timeObj.asSeconds();
		m_posX = m_posX + (m_velocity.x * dt );
		m_posY = m_posY + (m_velocity.y * dt );
		
	}
	void calcCollisions(PlayerBar& bar)
	{
		//get the position of bar
		sf::Vector2f barPos = bar.getPos();

		//get the limits of the bar
		sf::Vector2f barSize = bar.getSize();
		float barRight = barPos.x + (barSize.x/2.f);
		float barLeft = barPos.x - (barSize.x/2.f);
		float barTop = barPos.y + (barSize.y/2.f);
		float barBottom = barPos.y - (barSize.y/2.f);

		//find closest point on the bar to the ball by clamping 
		sf::Vector2f closestPoint{0.f,0.f};
		if (m_posX > barRight)
		{
			closestPoint.x = barRight;
			closestPoint.y = m_posY;
		}
		else if(m_posX < barLeft)
		{
			closestPoint.x = barLeft;
			closestPoint.y = m_posY;
		}
		else if(m_posX > barLeft && m_posX < barRight)
		{
			closestPoint.x = m_posX;
			if (m_posY > barTop)
				closestPoint.y = barTop;
			else if (m_posY < barBottom)
				closestPoint.y = barBottom;
		}

		//use that to calculate distance between two points 
		float distanceSq {};
		distanceSq = (m_posX - closestPoint.x)*(m_posX - closestPoint.x) + (m_posY - closestPoint.y)*(m_posY - closestPoint.y);

		//check if the distance between points is less than or equal to zero
		if (distanceSq < (m_radius * m_radius-10.f))
		{
			m_velocity.x = -1.f * m_velocity.x;
		}
	}

private:
	float m_posX{100.f};
	float m_posY{100.f};
	float m_radius{10.f};
	sf::Vector2f m_velocity{100.f,0.f};
	float m_acceleration{0.f};
	sf::Color m_color{0,0,0};
};

int main()
{

	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode({800,600}),"Hello World!",sf::Style::Default);
	window.setVerticalSyncEnabled(true);  

	PlayerBar P1{};

	PlayerBar O1{10.f,600.f};
	O1.moveToPositon(790.f,300.f);

	Ball b1{};

	sf::Clock clock;

	while (window.isOpen())
	{
		

		while (const std::optional event = window.pollEvent())
		{
			if(event -> is <sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		
		window.draw(P1.createShape());
		window.draw(b1.createShape());
		window.draw(O1.createShape());

		sf::Time deltaTime = clock.restart();

		b1.calcPhysics(deltaTime);
		b1.calcCollisions(P1);
		b1.calcCollisions(O1);

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		P1.moveToPositon(100.f,static_cast<float>(mousePos.y));

		window.display();
		
	}
	

}
