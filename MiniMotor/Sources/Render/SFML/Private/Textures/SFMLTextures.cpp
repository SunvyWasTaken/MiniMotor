#include "Textures/SFMLTextures.h"
#include <SFML/Graphics.hpp>

using MTextures = std::map<std::string, sf::Texture>;

namespace
{
	MTextures textures;
}

void SFMLTextures::LoadTexture(const std::string& filename)
{
	if (textures.find(filename) != textures.end())
	{
		return;
	}
	sf::Texture texture;
	texture.loadFromFile(filename);
	textures.emplace(filename, texture);
}

sf::Texture* SFMLTextures::GetTextures(const std::string& filename)
{
	return &textures.at(filename);
}
