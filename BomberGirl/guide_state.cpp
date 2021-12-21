#include "guide_state.h"
#include "configs.h"

Bombergirl::GuideState::GuideState(SharedContext* sharedContext) : BaseState(sharedContext) {}

void Bombergirl::GuideState::init()
{
    m_backgroundGuide.setTexture(m_sharedContext->m_resources->getTexture("guide_background"));

    m_imageGuide.setTexture(m_sharedContext->m_resources->getTexture("guide_text_image"));
    
    m_textControls.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_textControls.setString("CONTROLS");
    m_textControls.setCharacterSize(100u);
    m_textControls.setFillColor(sf::Color::White);
    sf::FloatRect bounds = m_textControls.getLocalBounds();
    auto windowSize = m_sharedContext->m_window->getSize();
    m_textControls.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    m_textControls.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 470);

    m_textMoveCharacter.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_textMoveCharacter.setString("MOVE");
    m_textMoveCharacter.setCharacterSize(75u);
    m_textMoveCharacter.setFillColor(sf::Color::White);
    m_textMoveCharacter.setPosition(windowSize.x / 2.f - 100, windowSize.y / 2.f - 320);

    m_textBomb.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_textBomb.setString("BOMB");
    m_textBomb.setCharacterSize(75u);
    m_textBomb.setFillColor(sf::Color::White);
    m_textBomb.setPosition(windowSize.x / 2.f - 100, windowSize.y / 2.f - 220);

    m_textMovePickUp.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_textMovePickUp.setString("MOVE PICK UP");
    m_textMovePickUp.setCharacterSize(75u);
    m_textMovePickUp.setFillColor(sf::Color::White);
    m_textMovePickUp.setPosition(windowSize.x / 2.f - 230, windowSize.y / 2.f - 120);

    m_textPickUp.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_textPickUp.setString("PICK UP");
    m_textPickUp.setCharacterSize(75u);
    m_textPickUp.setFillColor(sf::Color::White);
    m_textPickUp.setPosition(windowSize.x / 2.f - 130, windowSize.y / 2.f - 20);

    m_textPotionsIncreaseSpeed.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_textPotionsIncreaseSpeed.setString("INCREASE SPEED");
    m_textPotionsIncreaseSpeed.setCharacterSize(75u);
    m_textPotionsIncreaseSpeed.setFillColor(sf::Color::White);
    m_textPotionsIncreaseSpeed.setPosition(windowSize.x / 2.f - 750, windowSize.y / 2.f + 140);

    m_textPotionsIncreaseRange.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_textPotionsIncreaseRange.setString("INCREASE RANGE");
    m_textPotionsIncreaseRange.setCharacterSize(75u);
    m_textPotionsIncreaseRange.setFillColor(sf::Color::White);
    m_textPotionsIncreaseRange.setPosition(windowSize.x / 2.f - 750, windowSize.y / 2.f + 270);
    
    m_textPotionsIncreaseTheNumberOfBombs.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_textPotionsIncreaseTheNumberOfBombs.setString("INCREASE THE NUMBER OF BOMBS");
    m_textPotionsIncreaseTheNumberOfBombs.setCharacterSize(75u);
    m_textPotionsIncreaseTheNumberOfBombs.setFillColor(sf::Color::White);
    m_textPotionsIncreaseTheNumberOfBombs.setPosition(windowSize.x / 2.f - 750, windowSize.y / 2.f + 410);
}

void Bombergirl::GuideState::handleInput()
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

void Bombergirl::GuideState::update(const float&)
{
}

void Bombergirl::GuideState::render()
{
    m_sharedContext->m_window->draw(m_backgroundGuide);
    m_sharedContext->m_window->draw(m_imageGuide);
    m_sharedContext->m_window->draw(m_textControls);
    m_sharedContext->m_window->draw(m_textMoveCharacter);
    m_sharedContext->m_window->draw(m_textBomb);
    m_sharedContext->m_window->draw(m_textMovePickUp);
    m_sharedContext->m_window->draw(m_textPickUp);
    m_sharedContext->m_window->draw(m_textPotionsIncreaseSpeed);
    m_sharedContext->m_window->draw(m_textPotionsIncreaseRange);
    m_sharedContext->m_window->draw(m_textPotionsIncreaseTheNumberOfBombs);
}
