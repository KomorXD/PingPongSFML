#include "ResourceHolder.hpp"

ResourceHolder& ResourceHolder::Get() {
	static ResourceHolder obj;

	return obj;
}

ResourceHolder::ResourceHolder()
	: textures("Textures", "png"), fonts("Fonts", "ttf"), sounds("SFX", "ogg") {

	// Here you can add resources
	textures.AddResource("test");
	fonts.AddResource("OpenSans");
}
