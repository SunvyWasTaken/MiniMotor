#include "Textures/SFMLTextures.h"
#include <SFML/Graphics.hpp>

using MTextures = std::map<std::string, sf::Texture>;

namespace
{
	MTextures textures;
}

sf::Texture* SFMLTextures::GetTextures(const std::string& filename)
{
	if (textures.find(filename) == textures.end())
	{
		sf::Texture texture;
		texture.loadFromFile(filename);
		textures.emplace(filename, texture);
	}
	return &textures.at(filename);
}
