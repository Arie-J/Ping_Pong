#include "Ball.hpp"

Ball::Ball(float radius)
	:	m_radius{radius}
{
}

Ball::Ball() = default;

sf::CircleShape Ball::createShape()
{
	sf::CircleShape temp{m_radius,45};
	temp.setPosition({m_posX,m_posY});
	temp.setOrigin({m_radius,m_radius});
	return temp;
}


void Ball::calcPhysics(sf::Time timeObj)
{
	float dt = timeObj.asSeconds();
	m_posX = m_posX + (m_velocity.x * dt );
	m_posY = m_posY + (m_velocity.y * dt );
		
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
