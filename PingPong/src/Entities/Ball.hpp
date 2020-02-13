#pragma once

#include "Pallette.hpp"

#include <SFML/Graphics.hpp>

// Direction variables put into words, these determine whether a ball is moving left/right and upwards/downwards
enum class DIRECTION : int {
	UP    = 1,
	DOWN  = -1,
	LEFT  = -1,
	RIGHT = 1
};

class Ball {
	private:
		sf::CircleShape m_Body;
		DIRECTION		m_xDir;
		DIRECTION		m_yDir;

	public:
		Ball(float _radius, const sf::Vector2f& _pos);

		bool CollidesWithCeilingOrFloor(const sf::RenderWindow& _window);
		bool CollidesWithPallete(const Palette& _palette);
		bool OutOfBoard(const sf::RenderWindow& _window, float _paletteWidth);
		Palette* FurtherFrom(Palette* _p1, Palette* _p2);

		void Draw(sf::RenderTarget& _renderer);
		void Restart(const sf::Vector2f& _pos);

		void ChangeXDirection();
		void ChangeYDirection();

		void Move(float _dTime);
};