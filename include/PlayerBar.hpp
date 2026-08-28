#pragma once
#include "SFML/Graphics.hpp"

class PlayerBar
{
public:

	PlayerBar(float width, float height);


	PlayerBar();

	sf::RectangleShape createShape() const;


	void moveToPositon(float x, float y);
	

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
