#pragma once

#include <SFML/Graphics.hpp>

class App;

class BaseState {
	protected:
		App *m_p_App;

	public:
		BaseState(App& _app);
		virtual ~BaseState() = default;

		virtual void HandleEvents(sf::Event& _ev)		 = 0;
		virtual void HandleInput(float _dTime)			 = 0;
		virtual void Update(float _dTime)				 = 0;
		virtual void Render(sf::RenderTarget& _renderer) = 0;
};