#include "Ball.hpp"
#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>

Ball::Ball(float radius, sf::Vector2i vec)
	:	m_radius{radius}, m_windowSize{vec}
{
}

Ball::Ball() = default;

sf::CircleShape Ball::createShape()
{
	sf::CircleShape temp{m_radius,45};
	temp.setFillColor(m_color);
	temp.setPosition({m_posX,m_posY});
	temp.setOrigin({m_radius,m_radius});
	return temp;
}


void Ball::calcPhysics(sf::Time timeObj)
{
	if(!m_isWaiting)
	{
		float dt = timeObj.asSeconds();
		m_posX = m_posX + (m_velocity.x * dt );
		m_posY = m_posY + (m_velocity.y * dt );
	}	
}

void Ball::calcCollisions(PlayerBar& bar)
{
	//get the position of bar
	sf::Vector2f barPos = bar.getPos();

	//get the limits of the bar
	sf::Vector2f barSize = bar.getSize();
	float barRight = barPos.x + (barSize.x/2.f);
	float barLeft = barPos.x - (barSize.x/2.f);
	float barTop = barPos.y - (barSize.y/2.f);
	float barBottom = barPos.y + (barSize.y/2.f);

	//find closest point on the bar to the ball by clamping 
	sf::Vector2f closestPoint{0.f,0.f};
		
	closestPoint.x  = std::max(barLeft ,std::min(m_posX,barRight));
	closestPoint.y  = std::max(barTop ,std::min(m_posY,barBottom));

	//use that to calculate distance between two points 
	float distanceSq {};
	distanceSq = (m_posX - closestPoint.x)*(m_posX - closestPoint.x) + (m_posY - closestPoint.y)*(m_posY - closestPoint.y);

	//check if the distance between points is less than or equal to zero
	if (distanceSq <= (m_radius * m_radius))
	{
		if (closestPoint.x == barLeft || closestPoint.x == barRight)
		{
			m_velocity.x = -m_velocity.x ;
			if (m_posX < barPos.x)
				m_posX = barLeft - m_radius;
			else
				m_posX = barRight + m_radius;

		}
		if (closestPoint.y == barTop || closestPoint.y == barBottom)
		{
			m_velocity.y = -m_velocity.y ;
			if (m_posY < barPos.y)
				m_posY = barTop - m_radius;
			else
				m_posY = barBottom + m_radius;

		}
	}
}

int Ball::score()
{
	if(m_isWaiting)
	{
		if(m_clock.getElapsedTime().asSeconds() > 1.f)
		{
			m_isWaiting = false;
			int randCheckX = ((Random::get(-2,2) > 0 )?:1,-1);
			int randCheckY = ((Random::get(-2,2) > 0 )?:1,-1);
			int randintY = Random::get(100,300);
			int randintX = std::sqrt(500*500 - randintY*randintY);
			this -> giveVelocity({static_cast<float>(randCheckX*randintX),static_cast<float>(randCheckY*randintY)});
		}
	}
	if(m_posX < -m_radius)
	{
		m_score -= 1;
		m_posX = m_windowSize.x/2;
		m_posY = m_windowSize.y/2;
		this -> giveVelocity({0.f,0.f});
		m_isWaiting = true;
		m_clock.restart();
	}
	else if(m_posX > (m_radius + m_windowSize.x))
	{
		m_score += 1;
		m_posX = m_windowSize.x/2;
		m_posY = m_windowSize.y/2;
		this -> giveVelocity({0.f,0.f});
		m_isWaiting = true;
		m_clock.restart();
	}
	return m_score;
}

void Ball::setPausedAppearance(bool check)
{
	if (check == true)
		m_color.a = 100;
	else
		m_color.a = 255;
}
