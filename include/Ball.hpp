#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerBar.hpp"
#include "Random.h"

class PlayerBar;

class Ball
{
public:

	Ball(float radius,sf::Vector2i vec);

	Ball();

	sf::CircleShape createShape();

	void calcPhysics(sf::Time timeObj);

	void calcCollisions(PlayerBar& bar);

	void setPausedAppearance(bool check);

	int score();

	void giveVelocity(sf::Vector2f vel)
	{
		m_velocity = vel;
	}
	float getPosX() {return m_posX;}
	float getPosY() {return m_posY;}
	void setPosition(float x,float y) 
	{
		m_posX = x;
		m_posY = y;
	}
	void resetScore(){ m_score = 0;}
	sf::Vector2f getVelocity() {return m_velocity;}
	
private:
	sf::Vector2i m_windowSize{0,0};
	float m_posX{400.f};
	float m_posY{300.f};
	float m_radius{10.f};
	int m_score{0};
	sf::Vector2f m_velocity{0.f,0.f};
	float m_acceleration{0.f};
	sf::Color m_color{255,255,255,255};
	sf::Clock m_clock;
	bool m_isWaiting{false};
};
