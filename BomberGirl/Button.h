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

		void setSize(const sf::Vector2f&);

		void setTexture(const sf::Texture&);

		void setText(const std::string&, sf::Color color = sf::Color::Black, const int & sizeCharacter = 50);

		void setOutline(float thickness, sf::Color);

		void setPosition(const sf::Vector2f& position);

		void drawButton();
		

	};
}





