#pragma once
#include<SFML/Graphics.hpp>



namespace Bombergirl {
	class SharedContext;
	class Button {
	private:
		sf::RectangleShape m_shape;
		sf::Text m_content;
		SharedContext* m_sharedContext;
	public:
		
		Button(SharedContext*);

		void setPadding(float padding) {
			m_shape.setSize(sf::Vector2f(m_shape.getSize().x + padding, m_shape.getSize().y + padding));
		}

		void setSize(const sf::Vector2f&);

		void setText(const std::string&, sf::Color color = sf::Color::White, const int & sizeCharacter = 50);

		void setOutline(float thickness, sf::Color color = sf::Color::Black);

		void setPosition(const sf::Vector2f& position);

		void setBackgroundColor(const sf::Color color = sf::Color::Transparent);

		
		sf::Vector2f getSize() {
			return m_shape.getSize();
		}

		sf::Vector2f getCenter() {
			return sf::Vector2f(m_shape.getSize().x / 2.f, m_shape.getSize().y / 2.f);
		}

		sf::Vector2f getPosition() {
			return m_shape.getPosition();
		}

		void drawButton();
	};
}





