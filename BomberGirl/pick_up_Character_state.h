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

        sf::Text m_character_text_1;
        sf::Text m_character_text_2;

        sf::Sprite m_frame_1;
        sf::Sprite m_frame_2;

        sf::Sprite m_character_select_1;
        sf::Sprite m_character_select_2;

        sf::String m_character_value_1;
        sf::String m_character_value_2;

        int m_select_1;
        int m_select_2;

        sf::Sound* m_backsound;
        sf::Sound* m_soundClick;
        sf::Sound* m_soundconfirm;

        float m_transition;
        bool m_donePickingUp;
    public:
        PickUpCharacterState(SharedContext* sharedContext, sf::Sound*backSound = NULL);
        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
        void lockSelect(int, sf::RectangleShape&, const sf::Vector2f& , const sf::Vector2f&);
        void setText(sf::Text &text, const int&, const sf::String&, float outlineThickness = 1.f);

        ~PickUpCharacterState() {
            delete m_soundClick;
            delete m_soundconfirm;
        }
	};
}
