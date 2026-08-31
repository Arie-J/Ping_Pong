#pragma once
#include "SFML/Graphics.hpp"
#include "Ball.hpp"

class Ball;

class PlayerBar
{
public:

	PlayerBar(float width, float height, bool isOpponent = false,float windowWidth = 0.f);

	PlayerBar();

	sf::RectangleShape createShape() const;

	void moveToPositon(float x, float y);

	void setPausedAppearance(bool check);

	void chase(Ball ball, sf::Time deltaTime, float opponentSpeed);

	void moveUp(int speed)
	{
		m_posY -= speed;
	}

	void moveDown(int speed)
	{
		m_posY += speed;
	}

	sf::Vector2f getPos()
	{
		return sf::Vector2f {m_posX,m_posY};
	}

	sf::Vector2i getPosint()
	{
		return sf::Vector2i {static_cast<int>(m_posX), static_cast<int>(m_posY)};
	}

	sf::Vector2f getSize()
	{
		return sf::Vector2f {m_width, m_height};
	}

private:
	float m_windowWidth{0.f};
	float m_posX{100.f};
	float m_posY{100.f};
	float m_width{10.f};
	float m_height{150.f};
	bool m_computer{false};
	sf::Color m_color{255,255,255,255};
};
