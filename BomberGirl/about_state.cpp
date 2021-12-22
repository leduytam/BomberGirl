#include "about_state.h"
#include "configs.h"

Bombergirl::AboutState::AboutState(Bombergirl::SharedContext* sharedContext)
    : BaseState(sharedContext), m_isTextEnd(false), m_pressEnterTextEffectSpeed(PRESS_ENTER_TEXT_AFFECT_SPEED),
    m_pressEnterTextEffectAlpha(0.f), m_animationImageAlpha(255.f), isThanksDisplayed(false) {}

void Bombergirl::AboutState::init()
{
    m_textImage.setTexture(m_sharedContext->m_resources->getTexture("about_text_image"));
    auto windowSize = m_sharedContext->m_window->getSize();
    m_whiteBackground.setSize(sf::Vector2f(windowSize.x*1.f, windowSize.y*1.f));
    m_whiteBackground.setFillColor(sf::Color::White);

    m_whiteRectUp.setSize(sf::Vector2f(windowSize.x * 1.f, windowSize.y* 0.15f));
    m_whiteRectUp.setFillColor(sf::Color::White);

    m_whiteRectDown.setSize(sf::Vector2f(windowSize.x * 1.f, windowSize.y * 0.15f));
    m_whiteRectDown.setFillColor(sf::Color::White);
    m_whiteRectDown.setPosition(0.f, windowSize.y - m_whiteRectDown.getSize().y);

    m_textImage.setPosition(windowSize.x - 960.f, m_whiteRectDown.getPosition().y);

    m_textEnd.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_textEnd.setString("THANKS FOR WATCHING");
    m_textEnd.setCharacterSize(125u);
    m_textEnd.setFillColor(sf::Color(0u, 0u, 0u));
    sf::FloatRect bounds = m_textEnd.getLocalBounds();
    m_textEnd.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    m_textEnd.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 150);

    m_textBackToMenu.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_textBackToMenu.setString("PRESS ENTER TO BACK TO MAIN MENU");
    m_textBackToMenu.setCharacterSize(75u);
    bounds = m_textBackToMenu.getLocalBounds();
    m_textBackToMenu.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    m_textBackToMenu.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 50);

    m_groupSprite.setTexture(m_sharedContext->m_resources->getTexture("group_about"));
    m_groupSprite.setPosition(287.f, 228.f);

    m_lightSprite.setTexture(m_sharedContext->m_resources->getTexture("light_about"));
    m_lightSprite.setPosition(612.f, 336.f);

    m_leftGearSprite.setTexture(m_sharedContext->m_resources->getTexture("left_gear_about"));
    m_leftGearSprite.setOrigin(m_leftGearSprite.getLocalBounds().width / 2.f, m_leftGearSprite.getLocalBounds().height / 2.f);
    m_leftGearSprite.setPosition(487.f, 396.f);

    m_rightGearSprite.setTexture(m_sharedContext->m_resources->getTexture("right_gear_about"));
    m_rightGearSprite.setOrigin(m_rightGearSprite.getLocalBounds().width / 2.f, m_rightGearSprite.getLocalBounds().height / 2.f);
    m_rightGearSprite.setPosition(690.f, 332.f);

}

void Bombergirl::AboutState::handleInput()
{
    sf::Event e;
    while (m_sharedContext->m_window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed) {
            m_sharedContext->m_window->close();
        }
        else if (e.key.code == sf::Keyboard::Escape) {
            m_sharedContext->m_window->close();
        }
        else if (e.key.code == sf::Keyboard::Enter) {
            m_sharedContext->m_stateManager->pop();
        }
    }
}

void Bombergirl::AboutState::update(const float&dt)
{
    if (!m_isTextEnd) {
        if (m_textImage.getPosition().y + m_textImage.getLocalBounds().height <= m_whiteRectUp.getSize().y) {
            m_isTextEnd = true;
        }
        else {
            m_textImage.move(0.f, -TEXT_MOVE_SPEED * dt);
        }

        m_leftGearSprite.rotate(-GEAR_ROTATE_SPEED * dt);
        m_rightGearSprite.rotate(GEAR_ROTATE_SPEED * dt);

        if (m_textImage.getPosition().y + m_textImage.getLocalBounds().height < m_groupSprite.getPosition().y + m_groupSprite.getLocalBounds().height / 2.f) {
            m_animationImageAlpha += -100.f * dt;

            if (m_animationImageAlpha < 0.f) {
                m_animationImageAlpha = 0.f;
            }

            m_groupSprite.setColor(sf::Color(255u, 255u, 255u, (unsigned int)m_animationImageAlpha));
            m_leftGearSprite.setColor(sf::Color(255u, 255u, 255u, (unsigned int)m_animationImageAlpha));
            m_rightGearSprite.setColor(sf::Color(255u, 255u, 255u, (unsigned int)m_animationImageAlpha));
            m_lightSprite.setColor(sf::Color(255u, 255u, 255u, (unsigned int)m_animationImageAlpha));
        }
    }
    else
    {
		m_pressEnterTextEffectAlpha += m_pressEnterTextEffectSpeed * dt;
		if (m_pressEnterTextEffectAlpha < 0)
		{
			m_pressEnterTextEffectAlpha = 0;
			m_pressEnterTextEffectSpeed = -m_pressEnterTextEffectSpeed;
		}
		else if (m_pressEnterTextEffectAlpha > 255)
		{
			m_pressEnterTextEffectAlpha = 255;
			m_pressEnterTextEffectSpeed = -m_pressEnterTextEffectSpeed;
            isThanksDisplayed = true;
        }

        if (!isThanksDisplayed) {
            m_textBackToMenu.setFillColor(sf::Color(0u, 0u, 0u, (unsigned int)m_pressEnterTextEffectAlpha));
        }

		m_textBackToMenu.setFillColor(sf::Color(0u, 0u, 0u, (unsigned int)m_pressEnterTextEffectAlpha));
    }
}

void Bombergirl::AboutState::render()
{
    m_sharedContext->m_window->draw(m_whiteBackground);

    if (!m_isTextEnd) {
        m_sharedContext->m_window->draw(m_textImage);
        m_sharedContext->m_window->draw(m_whiteRectUp);
        m_sharedContext->m_window->draw(m_whiteRectDown);
        m_sharedContext->m_window->draw(m_leftGearSprite);
        m_sharedContext->m_window->draw(m_rightGearSprite);
        m_sharedContext->m_window->draw(m_groupSprite);
        m_sharedContext->m_window->draw(m_lightSprite);
    }
    else {
        m_sharedContext->m_window->draw(m_textEnd);
        m_sharedContext->m_window->draw(m_textBackToMenu);
    }
}
