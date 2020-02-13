#include "App.hpp"
#include "States/MainMenuState.hpp"

App::App(unsigned int _width, unsigned int _height)
	: m_Window(sf::VideoMode(_width, _height), "Ping Pong", sf::Style::Titlebar | sf::Style::Close) {
	
	// Push main manu game state at the start of app
	m_States.push(std::make_unique<MainMenuState>(*this));
}

void App::Run() {
	sf::Clock dTimer;
	float	  dTime = 1 / 60.0f;

	while (m_Window.isOpen()) {
		// Calculating delat time, time between frames
		dTime = dTimer.restart().asSeconds();

		sf::Event ev;

		while (m_Window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed)
				m_Window.close();

			m_States.top()->HandleEvents(ev);
		}

		m_Window.clear();

		m_States.top()->HandleInput(dTime);
		m_States.top()->Update(dTime);
		m_States.top()->Render(m_Window);
	
		m_Window.display();
	}
}

void App::PushState(std::unique_ptr<BaseState>& _state) {
	m_States.push(std::move(_state));
}

void App::PushState(std::unique_ptr<BaseState>&& _state) {
	m_States.push(std::move(_state));
}

bool App::PopState() {
	if(m_States.empty())
		return false;

	m_States.pop();

	return true;
}

void App::ChangeState(std::unique_ptr<BaseState>& _state) {
	PopState();
	m_States.push(std::move(_state));
}

void App::ChangeState(std::unique_ptr<BaseState>&& _state) {
	PopState();
	m_States.push(std::move(_state));
}

sf::RenderWindow& App::GetWindow() {
	return m_Window;
}

void App::CloseWindow() {
	m_Window.close();
}
