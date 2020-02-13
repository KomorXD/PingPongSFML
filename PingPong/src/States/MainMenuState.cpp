#include "MainMenuState.hpp"
#include "PongState.hpp"
#include "../ResourceManagers/ResourceHolder.hpp"
#include "../App.hpp"

// SFML text centering
void MainMenuState::CenterTextOrigin(sf::Text& _text) {
	sf::FloatRect textRect = _text.getLocalBounds();

	_text.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top  + textRect.height / 2.0f);
}

MainMenuState::MainMenuState(App& _app)
	: BaseState(_app), m_p_FocusedText(&m_PlayText) {

	// Setting up every sf::Text object
	sf::Font& font = ResourceHolder::Get().fonts.Get("OpenSans");

	m_p_FocusedText->setFillColor(sf::Color(255, 140, 0));
	m_p_FocusedText->setCharacterSize(35U);

	m_TitleText.setString("Ping Pong");
	m_TitleText.setFont(font);
	m_TitleText.setCharacterSize(70U);

	m_PlayText.setString("Play 1v1");
	m_PlayText.setFont(font);

	m_ExitText.setString("Exit");
	m_ExitText.setFont(font);

	CenterTextOrigin(m_TitleText);
	CenterTextOrigin(m_PlayText);
	CenterTextOrigin(m_ExitText);

	sf::Vector2f winSize = static_cast<sf::Vector2f>(m_p_App->GetWindow().getSize());

	m_TitleText.setPosition(winSize.x / 2.0f, winSize.y / 4.0f);
	m_PlayText.setPosition(winSize.x / 2.0f, 2 * winSize.y / 4.0f);
	m_ExitText.setPosition(winSize.x / 2.0f, 2.5f * winSize.y / 4.0f);
}

void MainMenuState::HandleEvents(sf::Event& ev) {
	if (ev.type == sf::Event::KeyPressed) {
		// If either W or S is pressed, change focused line and the pointer to it
		if (ev.key.code == sf::Keyboard::W || ev.key.code == sf::Keyboard::S) {

			// Since we changed highlighted line, bring previous one to the normal state
			// Because we change the font size of highlighted lines, we must center their origin again
			m_p_FocusedText->setFillColor(sf::Color(255, 255, 255));
			m_p_FocusedText->setCharacterSize(30U);
			CenterTextOrigin(*m_p_FocusedText);

			// Toggle focused text pointer
			m_p_FocusedText = (m_p_FocusedText == &m_PlayText ? &m_ExitText : &m_PlayText);
			
			// Highlight the new line
			m_p_FocusedText->setFillColor(sf::Color(255, 140, 0));
			m_p_FocusedText->setCharacterSize(35U);
			CenterTextOrigin(*m_p_FocusedText);
		}
		else if (ev.key.code == sf::Keyboard::Enter || ev.key.code == sf::Keyboard::Space) {
			// If we hit play text, push playing state (PongState) onto the stack
			if (m_p_FocusedText == &m_PlayText)
				m_p_App->PushState(std::make_unique<PongState>(*m_p_App));
			
			// If we hit exit text, close the window and thus close the app
			else if (m_p_FocusedText == &m_ExitText)
				m_p_App->CloseWindow();
		}
	}
}

void MainMenuState::HandleInput(float _dTime) {
	// Nothing do to here
	;
}

void MainMenuState::Update(float _dTime) {
	// Nothing to do here
	;
}

void MainMenuState::Render(sf::RenderTarget& _renderer) {
	// Render every text
	_renderer.draw(m_TitleText);
	_renderer.draw(m_PlayText);
	_renderer.draw(m_ExitText);
}
