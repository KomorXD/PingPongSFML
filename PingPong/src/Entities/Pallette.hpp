#pragma once

#include <SFML/Graphics.hpp>

class Palette {
	private:
		sf::RectangleShape m_Body;
		sf::Keyboard::Key  m_UpKey;
		sf::Keyboard::Key  m_DownKey;
		unsigned int       m_Score;

	public:
		Palette(const sf::Vector2f& _pos, const sf::Vector2f& _size);

		void Move(const sf::Vector2f& _offset, float _dTime);
		bool CollidesWithCeiling(const sf::RenderWindow& _window);
		bool CollidesWithFloor(const sf::RenderWindow& _window);

		void Draw(sf::RenderTarget& _renderer);

		void SetUpKey(sf::Keyboard::Key&& _key);
		void SetDownKey(sf::Keyboard::Key&& _key);

		void IncrementScore();
		unsigned int& GetScore();
		
		const sf::Keyboard::Key& GetUpKey()		   const;
		const sf::Keyboard::Key& GetDownKey()	   const;
		const sf::RectangleShape& GetPaletteBody() const;
};