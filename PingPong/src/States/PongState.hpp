#pragma once

#include "BaseState.hpp"
#include "../Entities/Pallette.hpp"
#include "../Entities/Ball.hpp"

// STATE defines the state of a current game
enum class STATE {
	PLAYING,
	PAUSE,
	WON
};

class PongState : public BaseState {
	private:
		// Palette, ball and STATE are pretty self-explanatory
		// m_P1/P2Score - texts that show current scores
		// m_Paused/Winner/SubWinnerText - texts that appear either on PAUSE state or WON state
		Palette	 m_Palette1;
		Palette	 m_Palette2;
		Ball	 m_Ball;
		sf::Text m_P1Score;
		sf::Text m_P2Score;
		sf::Text m_PausedText;
		sf::Text m_WinnerText;
		sf::Text m_SubWinnerText;
		STATE    m_State;

		// SFML text centering
		void CenterTextOrigin(sf::Text& _text);

	public:
		PongState(App& _app);
		~PongState() = default;

		void HandleEvents(sf::Event & ev)		  override;
		void HandleInput(float _dTime)			  override;
		void Update(float _dTime)				  override;
		void Render(sf::RenderTarget & _renderer) override;
};