// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Textures/Textures.h"

namespace sf
{
	class Texture;
}

class MM_EXPORT SFMLTextures : public TextureManager<SFMLTextures>
{
public:
	void LoadTexture(const std::string& filename);
	sf::Texture* GetTextures(const std::string& filename);
};