#include "PongState.hpp"
#include "../App.hpp"
#include "../ResourceManagers/ResourceHolder.hpp"

#include <string>

// SFML text centering
void PongState::CenterTextOrigin(sf::Text& _text) {
	sf::FloatRect textRect = _text.getLocalBounds();

	_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

// Initializing every class member
PongState::PongState(App& _app)
	: BaseState(_app)
	, m_Palette1(sf::Vector2f(5.0f, m_p_App->GetWindow().getSize().y / 2.0f), sf::Vector2f(10.0f, 100.0f))
	, m_Palette2(sf::Vector2f(m_p_App->GetWindow().getSize().x - 5.0f, m_p_App->GetWindow().getSize().y / 2.0f), sf::Vector2f(10.0f, 100.0f))
	, m_Ball(5.0f, sf::Vector2f(static_cast<sf::Vector2f>(m_p_App->GetWindow().getSize()) / 2.0f))
	, m_P1Score("0", ResourceHolder::Get().fonts.Get("OpenSans"))
	, m_P2Score("0", ResourceHolder::Get().fonts.Get("OpenSans"))
	, m_PausedText("PAUSE", ResourceHolder::Get().fonts.Get("OpenSans"))
	, m_WinnerText("", ResourceHolder::Get().fonts.Get("OpenSans"))
	, m_SubWinnerText("Press SPACE to play again or ESC to go back to the main menu", ResourceHolder::Get().fonts.Get("OpenSans"))
	, m_State(STATE::PLAYING) {

	// Setting up sf::Text objects
	m_P1Score.setCharacterSize(50U);
	m_P2Score.setCharacterSize(50U);
	m_PausedText.setCharacterSize(70U);
	m_WinnerText.setCharacterSize(40U);
	m_SubWinnerText.setCharacterSize(20U);

	CenterTextOrigin(m_P1Score);
	CenterTextOrigin(m_P2Score);
	CenterTextOrigin(m_PausedText);
	CenterTextOrigin(m_SubWinnerText);

	m_P1Score.setPosition(m_p_App->GetWindow().getSize().x / 3.0f, m_p_App->GetWindow().getSize().y / 6.0f);
	m_P2Score.setPosition(2 * m_p_App->GetWindow().getSize().x / 3.0f, m_p_App->GetWindow().getSize().y / 6.0f);
	m_PausedText.setPosition(static_cast<sf::Vector2f>(m_p_App->GetWindow().getSize()) / 2.0f);
	m_WinnerText.setPosition(static_cast<sf::Vector2f>(m_p_App->GetWindow().getSize()) / 2.0f);
	m_SubWinnerText.setPosition(m_p_App->GetWindow().getSize().x / 2.0f, m_WinnerText.getPosition().y + 100.0f);

	// Setting up palatte's keys
	m_Palette1.SetUpKey(sf::Keyboard::Key::W);
	m_Palette1.SetDownKey(sf::Keyboard::Key::S);

	m_Palette2.SetUpKey(sf::Keyboard::Key::Up);
	m_Palette2.SetDownKey(sf::Keyboard::Key::Down);
}

void PongState::HandleEvents(sf::Event& ev) {
	if (ev.type == sf::Event::KeyPressed) {
		// If one player has scored 11
		if (m_State == STATE::WON) {
			// Space will restart the game, hence reset the stats
			if (ev.key.code == sf::Keyboard::Key::Space) {
				m_P1Score.setString("0");
				m_P2Score.setString("0");
				m_Palette1.GetScore() = 0;
				m_Palette2.GetScore() = 0;
				m_Ball.Restart(static_cast<sf::Vector2f>(m_p_App->GetWindow().getSize()) / 2.0f);
				m_State = STATE::PLAYING;
			}
		}
		// If the game is still on, pressing P will un/pause it
		else if (ev.key.code == sf::Keyboard::Key::P)
			m_State = (m_State == STATE::PAUSE ? STATE::PLAYING : STATE::PAUSE);

		// Hitting ESC pops playing state and return a player to the main menu
		if (ev.key.code == sf::Keyboard::Key::Escape)
			m_p_App->PopState();
		
	}
}

void PongState::HandleInput(float _dTime) {
	// ONLY if the game is on
	if (m_State == STATE::PLAYING) {
		// If corresponding moving keys are pressed and palettes are not blocked by the screen, move them
		if (sf::Keyboard::isKeyPressed(m_Palette1.GetUpKey()) && !m_Palette1.CollidesWithCeiling(m_p_App->GetWindow()))
			m_Palette1.Move(sf::Vector2f(0.0f, -300.0f), _dTime);
		else if (sf::Keyboard::isKeyPressed(m_Palette1.GetDownKey()) && !m_Palette1.CollidesWithFloor(m_p_App->GetWindow()))
			m_Palette1.Move(sf::Vector2f(0.0f, 300.0f), _dTime);

		if (sf::Keyboard::isKeyPressed(m_Palette2.GetUpKey()) && !m_Palette2.CollidesWithCeiling(m_p_App->GetWindow()))
			m_Palette2.Move(sf::Vector2f(0.0f, -300.0f), _dTime);
		else if (sf::Keyboard::isKeyPressed(m_Palette2.GetDownKey()) && !m_Palette2.CollidesWithFloor(m_p_App->GetWindow()))
			m_Palette2.Move(sf::Vector2f(0.0f, 300.0f), _dTime);
	}
}

void PongState::Update(float _dTime) {
	if (m_State == STATE::PLAYING) {
		// Check if any player has won, if so change the state to WON
		if (m_Palette1.GetScore() == 11) {
			m_WinnerText.setString("Player on the left wins!");
			CenterTextOrigin(m_WinnerText);
			m_State = STATE::WON;

			return;
		}
		else if (m_Palette2.GetScore() == 11) {
			m_WinnerText.setString("Player on the right wins!");
			CenterTextOrigin(m_WinnerText);
			m_State = STATE::WON;

			return;
		}

		if (m_Ball.CollidesWithCeilingOrFloor(m_p_App->GetWindow()))
			m_Ball.ChangeYDirection();

		if (m_Ball.CollidesWithPallete(m_Palette1) || m_Ball.CollidesWithPallete(m_Palette2))
			m_Ball.ChangeXDirection();
		else if (m_Ball.OutOfBoard(m_p_App->GetWindow(), m_Palette1.GetPaletteBody().getSize().x)) {
			// If ball has gone out of board, check which palette was further from it and return a pointer to it, since this one will get a point
			Palette* winner = m_Ball.FurtherFrom(&m_Palette1, &m_Palette2);

			// Incerement the score and change text that shows one of two scores
			winner->IncrementScore();
			if (winner == &m_Palette1)
				m_P1Score.setString(std::to_string(winner->GetScore()));
			else if (winner == &m_Palette2)
				m_P2Score.setString(std::to_string(winner->GetScore()));

			// Reset the ball to the middle of the screen
			m_Ball.Restart(static_cast<sf::Vector2f>(m_p_App->GetWindow().getSize()) / 2.0f);
		}

		m_Ball.Move(_dTime);
	}
}

void PongState::Render(sf::RenderTarget& _renderer) {
	// Always draw
	_renderer.draw(m_P1Score);
	_renderer.draw(m_P2Score);

	m_Palette1.Draw(_renderer);
	m_Palette2.Draw(_renderer);

	// Only if the game is still on / paused
	if(m_State != STATE::WON)
		m_Ball.Draw(_renderer);

	// Only if the game is paused
	if (m_State == STATE::PAUSE)
		_renderer.draw(m_PausedText);

	// Only if the game has been finished
	if (m_State == STATE::WON) {
		_renderer.draw(m_WinnerText);
		_renderer.draw(m_SubWinnerText);
	}
}
