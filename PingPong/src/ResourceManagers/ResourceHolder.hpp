#pragma once

#include "ResourceManager.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Interface to the ResourceManager, hold textures, fonts and sounds
struct ResourceHolder {
	public:
		ResourceManager<sf::Texture>	 textures;
		ResourceManager<sf::Font>		 fonts;
		ResourceManager<sf::SoundBuffer> sounds;

		static ResourceHolder& Get();

	private:
		ResourceHolder();
};