#pragma once
#include <SFML/Graphics.hpp>
#include <PlayerBar.hpp>

class Ball
{
public:

	Ball(float radius);

	Ball();

	sf::CircleShape createShape();

	void calcPhysics(sf::Time timeObj);

	void giveVelocity(sf::Vector2f vel)
	{
		m_velocity = vel;
	}

	void calcCollisions(PlayerBar& bar);
	

private:
	float m_posX{400.f};
	float m_posY{300.f};
	float m_radius{10.f};
	sf::Vector2f m_velocity{0.f,0.f};
	float m_acceleration{0.f};
	sf::Color m_color{0,0,0};
};
