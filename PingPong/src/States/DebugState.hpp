#pragma once

#include "BaseState.hpp"

class DebugState : public BaseState {
	private:
		sf::RectangleShape m_Shape;
		sf::Text		   m_Text;

	public:
		DebugState(App& _app);
		~DebugState() = default;

		void HandleEvents(sf::Event& ev)		 override;
		void HandleInput(float _dTime)			 override;
		void Update(float _dTime)				 override;
		void Render(sf::RenderTarget& _renderer) override;
};