#include "DebugState.hpp"
#include "../App.hpp"
#include "../ResourceManagers/ResourceHolder.hpp"

DebugState::DebugState(App& _app)
	: BaseState(_app), m_Shape(sf::Vector2f(100.0f, 100.0f)), m_Text("Debug Text", ResourceHolder::Get().fonts.Get("OpenSans")) {
	
	m_Shape.setOrigin(50.0f, 50.0f);
	m_Shape.setPosition(200.0f, 200.0f);
	m_Shape.setTexture(&ResourceHolder::Get().textures.Get("test"));

	m_Text.setPosition(400.0f, 400.0f);
}

void DebugState::HandleEvents(sf::Event& ev) {
	if (ev.type == sf::Event::KeyPressed)
		if (ev.key.code == sf::Keyboard::Escape)
			m_p_App->PopState();
}

void DebugState::HandleInput(float _dTime) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_Shape.move(-200.0f * _dTime, 0.0f);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_Shape.move(200.0f * _dTime, 0.0f);
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_Shape.move(0.0f, 200.0f * _dTime);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_Shape.move(0.0f, -200.0f * _dTime);
}

void DebugState::Update(float _dTime) {
	;
}

void DebugState::Render(sf::RenderTarget& _renderer) {
	_renderer.draw(m_Text);
	_renderer.draw(m_Shape);
}
