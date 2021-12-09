#pragma once
#include"base_state.h"
#include<vector>

namespace Bombergirl{
	class PickUpCharacterState :public BaseState
	{
    private:
        sf::Sprite m_backgroundSprite;
        sf::Text m_pickUpText;
        std::vector<sf::Sprite> m_characters;

        sf::Sprite m_borderSelect_1;
        sf::Sprite m_borderSelect_2;

        sf::RectangleShape m_lockBackground_1;
        sf::RectangleShape m_lockBackground_2;

        sf::String m_character_1;
        sf::String m_character_2;

        int m_select_1;
        int m_select_2;

    public:
        PickUpCharacterState(SharedContext* sharedContext);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;

        void lockSelect(int, sf::RectangleShape&, const sf::Vector2f& , const sf::Vector2f&);
	};
}


