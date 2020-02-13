#include "Pallette.hpp"
#include "../Utilities/Random.hpp"

Palette::Palette(const sf::Vector2f& _pos, const sf::Vector2f& _size)
	: m_Body(_size), m_UpKey(sf::Keyboard::Up), m_DownKey(sf::Keyboard::Down), m_Score(0U) {

	// Randomize the color of a palette and set it up
	Random& rand = Random::Get();

	m_Body.setFillColor(sf::Color(rand.IntInRange(0, 255), rand.IntInRange(0, 255), rand.IntInRange(0, 255)));
	m_Body.setOrigin(m_Body.getSize() / 2.0f);
	m_Body.setPosition(_pos);
}

void Palette::Move(const sf::Vector2f& _offset, float _dTime) {
	m_Body.move(_offset * _dTime);
}

bool Palette::CollidesWithCeiling(const sf::RenderWindow& _window) {
	// Return true if a palette is touching the top of a screen
	return (m_Body.getPosition().y - m_Body.getSize().y / 2.0f <= 0.0f);
}

bool Palette::CollidesWithFloor(const sf::RenderWindow& _window) {
	// Return true if a palette is touching the bottom of a screen
	return (m_Body.getPosition().y + m_Body.getSize().y / 2.0f >= _window.getSize().y);
}

void Palette::Draw(sf::RenderTarget& _renderer) {
	_renderer.draw(m_Body);
}

void Palette::SetUpKey(sf::Keyboard::Key&& _key) {
	m_UpKey = _key;
}

void Palette::SetDownKey(sf::Keyboard::Key&& _key) {
	m_DownKey = _key;
}

void Palette::IncrementScore() {
	m_Score++;
}

unsigned int& Palette::GetScore() {
	return m_Score;
}

const sf::Keyboard::Key& Palette::GetUpKey() const {
	return m_UpKey;
}

const sf::Keyboard::Key& Palette::GetDownKey() const {
	return m_DownKey;
}

const sf::RectangleShape& Palette::GetPaletteBody() const {
	return m_Body;
}
