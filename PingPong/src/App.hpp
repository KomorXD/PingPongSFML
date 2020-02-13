#pragma once

#include "States/BaseState.hpp"

#include <SFML/Graphics.hpp>
#include <stack>
#include <memory>

class App {
	private:
		sf::RenderWindow m_Window;
		std::stack<std::unique_ptr<BaseState>> m_States;

	public:
		App(unsigned int _width, unsigned int _height);

		// Game loop
		void Run();

		// m_States access methods
		void PushState(std::unique_ptr<BaseState>& _state);
		void PushState(std::unique_ptr<BaseState>&& _state);
		bool PopState();
		void ChangeState(std::unique_ptr<BaseState>& _state);
		void ChangeState(std::unique_ptr<BaseState>&& _state);

		sf::RenderWindow& GetWindow();
		void CloseWindow();
};