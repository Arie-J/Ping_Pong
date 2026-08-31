#include "MenuText.hpp"

MenuText::MenuText(sf::Font& font, std::string_view str, int size, sf::Vector2f position)
:   m_menuText{sf::Text(font)},m_string{str},m_size{size},m_position{position}
{}

void MenuText::createText()
{
    m_menuText.setCharacterSize(m_size);
    m_menuText.setString(m_string);
    m_menuText.setFillColor(m_color);
    
    const auto bounds = m_menuText.getLocalBounds();
    float centerX = bounds.position.x + (bounds.size.x/2.f);
    float centerY = bounds.position.y + (bounds.size.y/2.f);
    m_menuText.setOrigin({centerX, centerY});
    
    m_menuText.setPosition(m_position);
}

void MenuText::setTextint(int value)
{
    std::string str {std::to_string(value)};
    m_menuText.setString(str);
}
