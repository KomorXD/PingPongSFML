#pragma once

#include "BaseState.hpp"

class MainMenuState : public BaseState {
	private:
		// Text that appears in the main menu
		sf::Text  m_TitleText;
		sf::Text  m_PlayText;
		sf::Text  m_ExitText;

		// Pointer so we know which line to color and resize
		sf::Text* m_p_FocusedText;

		// SFML text centering
		void CenterTextOrigin(sf::Text& _text);

	public:
		MainMenuState(App& _app);
		~MainMenuState() = default;

		void HandleEvents(sf::Event & ev)		  override;
		void HandleInput(float _dTime)			  override;
		void Update(float _dTime)				  override;
		void Render(sf::RenderTarget & _renderer) override;
};