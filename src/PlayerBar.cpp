#include "PlayerBar.hpp"


PlayerBar::PlayerBar(float width, float height, bool isOpponent)
:	m_width{width}, m_height{height}, m_computer{isOpponent}
{
}

PlayerBar::PlayerBar() = default;

sf::RectangleShape PlayerBar::createShape() const
{
	sf::RectangleShape bar({m_width,m_height});
	bar.setFillColor(m_color);
	bar.setPosition({m_posX,m_posY});
	bar.setOrigin({m_width/2,m_height/2});
	return bar;
}

void PlayerBar::chase(Ball ball,sf::Time deltaTime,float opponentSpeed)
{
	if(m_computer)
	{
		float moveDistance {opponentSpeed*deltaTime.asSeconds()};
		float deadZone{1.f};
		float gap{std::abs(ball.getPosY() - m_posY)};
		
		if(gap > deadZone)
		{
			if(moveDistance > gap)
			{
				moveDistance = gap;
			}
			if(ball.getPosY() < m_posY)
			{
				this->moveUp(moveDistance);
			}
			else if(ball.getPosY() > m_posY) 
			{
				this -> moveDown(moveDistance);
			}
		}
	}
}

void PlayerBar::moveToPositon(float x, float y)
{
	m_posX = x;
	m_posY = y;
}

void PlayerBar::setPausedAppearance(bool check)
{
	if(check == true)
		m_color.a = 100;
	else
		m_color.a = 255;
}
