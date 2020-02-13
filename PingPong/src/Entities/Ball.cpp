#include "Ball.hpp"
#include "../Utilities/Random.hpp"

Ball::Ball(float _radius, const sf::Vector2f& _pos)
	: m_Body(_radius) {

	// Ball gets a random color, also setting it up and randomizing it's direction
	Random& rand = Random::Get();

	m_Body.setFillColor(sf::Color(rand.IntInRange(0, 255), rand.IntInRange(0, 255), rand.IntInRange(0, 255)));
	m_Body.setOrigin(sf::Vector2f(_radius / 2.0f, _radius / 2.0f));
	m_Body.setPosition(_pos);
	
	m_xDir = (rand.IntInRange(0, 10) < 5 ? DIRECTION::LEFT : DIRECTION::RIGHT);
	m_yDir = (rand.IntInRange(0, 10) < 5 ? DIRECTION::UP : DIRECTION::DOWN);
}

bool Ball::CollidesWithCeilingOrFloor(const sf::RenderWindow& _window) {
	//Checks if the ball should bounce
	return (m_Body.getPosition().y - m_Body.getRadius() <= 0.0f || m_Body.getPosition().y + m_Body.getRadius() >= _window.getSize().y);
}

bool Ball::CollidesWithPallete(const Palette& _palette) {
	const sf::RectangleShape& paletteBody = _palette.GetPaletteBody();

	// If the ball is close enough on the x axis, we check if palette's y range contains ball's y position, if so it collides with it
	if (std::abs(m_Body.getPosition().x - paletteBody.getPosition().x) <= m_Body.getRadius() + paletteBody.getSize().x / 1.5f)
		return (m_Body.getPosition().y > paletteBody.getPosition().y - paletteBody.getSize().y / 2.0f && m_Body.getPosition().y < paletteBody.getPosition().y + paletteBody.getSize().y / 2.0f);

	return false;
}

bool Ball::OutOfBoard(const sf::RenderWindow& _window, float _paletteWidth) {
	// Return true if the ball is out of the board
	return (m_Body.getPosition().x <= _paletteWidth || m_Body.getPosition().x >= _window.getSize().x - _paletteWidth);
}

Palette* Ball::FurtherFrom(Palette* _p1, Palette* _p2) {
	// Checks what palette the ball is further away from and returns a pointer to that palette
	if (std::abs(_p1->GetPaletteBody().getPosition().x - m_Body.getPosition().x) > std::abs(_p2->GetPaletteBody().getPosition().x - m_Body.getPosition().x))
		return _p1;
	else
		return _p2;
}

void Ball::Draw(sf::RenderTarget& _renderer) {
	_renderer.draw(m_Body);
}

void Ball::Restart(const sf::Vector2f& _pos) {
	// Restarts ball's state
	m_Body.setPosition(_pos);

	m_xDir = (Random::Get().IntInRange(0, 10) < 5 ? DIRECTION::LEFT : DIRECTION::RIGHT);
	m_yDir = (Random::Get().IntInRange(0, 10) < 5 ? DIRECTION::UP : DIRECTION::DOWN);
}

void Ball::ChangeXDirection() {
	m_xDir = (m_xDir == DIRECTION::LEFT ? DIRECTION::RIGHT : DIRECTION::LEFT);
}

void Ball::ChangeYDirection() {
	m_yDir = (m_yDir == DIRECTION::UP ? DIRECTION::DOWN : DIRECTION::UP);
}

void Ball::Move(float _dTime) {
	m_Body.move(sf::Vector2f(350.0f * static_cast<int>(m_xDir), 350.0f * static_cast<int>(m_yDir)) * _dTime);
}
