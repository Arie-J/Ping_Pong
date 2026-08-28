#include "PlayerBar.hpp"


PlayerBar::PlayerBar(float width, float height)
:	m_width{width}, m_height{height}
{
}

PlayerBar::PlayerBar() = default;

sf::RectangleShape PlayerBar::createShape() const
{
	sf::RectangleShape bar({m_width,m_height});
	bar.setPosition({m_posX,m_posY});
	bar.setOrigin({m_width/2,m_height/2});
	return bar;
}

void PlayerBar::moveToPositon(float x, float y)
{
	m_posX = x;
	m_posY = y;
}


