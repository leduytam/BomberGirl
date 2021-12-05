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

		void setPadding(float padding);

		void setSize(const sf::Vector2f&);

		void setText(const std::string&, sf::Color color = sf::Color::White, const int & sizeCharacter = 50);

		void setOutline(float thickness, sf::Color color = sf::Color::Black);

		void setPosition(const sf::Vector2f& position);

		void setBackgroundColor(const sf::Color color = sf::Color::Transparent);
		
		sf::Vector2f getSize();

		sf::Vector2f getCenter();

		sf::Vector2f getPosition();

		void drawButton();
	};
}





