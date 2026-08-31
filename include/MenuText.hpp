#include <SFML/Graphics.hpp>

class MenuText
{
public:
    MenuText(sf::Font& font, std::string_view str, int size, sf::Vector2f position);

    void createText();

    void setTextint(int value);
    
    sf::Vector2f getPosition() {return m_position;}
    sf::Text getText() {return m_menuText;}
    void setAlpha(uint8_t a) 
    {
        m_color.a = a;
        m_menuText.setFillColor(m_color);
    }

private:
   sf::Text m_menuText;
   int m_size;
   std::string m_string;
   sf::Vector2f m_position;
   sf::Color m_color{255,255,255,255};
};
